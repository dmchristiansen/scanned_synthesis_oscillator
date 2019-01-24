/*
 * TODO:
 *
 * Functionality:
 * - Implement event queue
 * 	- Move buffer update handling to queue
 * 	- Move state update handling to queue
 * 	- Move state update trigger to systick isr
 *
 * - Improve state update algorithm 
 * - Add input to excite system
 * 	- Set up button polling / debounce
 * 	- Add button press event queueing / handler
 *
 * - Set up switch polling
 * - Set up ADC polling
 * - Add add parameter control pots
 *
 * Structure:
 * - Abstract from hardware slightly (module interfaces)
 * - Split DAC setup into DMAMUX/eDMA & DAC/PDB setups
 *
 */





#include <functional>
#include "oscillator.h"
#include "Arduino.h"
#include "dac.h"
#include "kinetis.h"
#include "system.h"
#include "arm_math.h"
#include "EventManager.h"

void ftm_setup(uint8_t, uint16_t);

volatile uint16_t output_buffer[OUTPUT_BUFFER_SIZE*OUTPUT_BUFFER_COUNT] 
	__attribute__((aligned (OUTPUT_BUFFER_SIZE*OUTPUT_BUFFER_COUNT*2)));

uint16_t F_UPDATE = 100;
uint16_t UPDATE_PS = 16;
uint16_t UPDATE_TIMER = F_BUS / (F_UPDATE * UPDATE_PS);

EventManager eventManager;

extern "C" int main(void) {
	
	volatile uint16_t* output_buffer_list[OUTPUT_BUFFER_COUNT] = {
		&output_buffer[0],
		&output_buffer[OUTPUT_BUFFER_SIZE] 
	};

	DACInterface dac0;
	dac0.Init(output_buffer);

	Oscillator osc;
	osc.Init(output_buffer_list, 400.0);

	MemberFunctionCallable<Oscillator> genTableCallback(&osc, &Oscillator::generateTable);
	MemberFunctionCallable<Oscillator> updateStateCallback(&osc, &Oscillator::updateState);

	eventManager.addListener(EventManager::kEventOutBuffer, &genTableCallback);
	eventManager.addListener(EventManager::kEventState, &updateStateCallback);

  eventManager.enableListener(EventManager::kEventOutBuffer, &genTableCallback, true);
	eventManager.enableListener(EventManager::kEventState, &updateStateCallback, true);

	pinMode(13, OUTPUT);

	ftm_setup(UPDATE_PS, UPDATE_TIMER);

	
	// Main task loop
	while(1) {
		eventManager.processEvent();
	}

}

// FTM timer setup for mass system state update
void ftm_setup(uint8_t prescaler, uint16_t update_timer) {

	SIM_SCGC6 |= SIM_SCGC6_FTM0; // Enable FTM0 clock
	
	NVIC_ENABLE_IRQ(IRQ_FTM0);

	FTM0_MODE |= FTM_MODE_WPDIS; // Disable write protection
	FTM0_SC = 0x0;	// Disable TPM0
	FTM0_CNT = 0x0;	// Clear counter
	FTM0_MOD = (update_timer);

	
	FTM0_SC |=
		(FTM_SC_TOF			// Clear overflow flag
		|FTM_SC_TOIE		// Enable overflow interrupt
		|FTM_SC_CLKS(1)	// Enable timer, count on internal clock
		|FTM_SC_PS(__builtin_clz(prescaler)));	
	
}

// Interrupt routine to track output buffer use & start buffer fill
void dma_ch0_isr(void) {
	
	static uint8_t buffer_tracker = 0;

	eventManager.queueEvent(
		EventManager::kEventOutBuffer, 
		buffer_tracker ? 1 : 0,
		EventManager::kHighPriority);

	buffer_tracker = (buffer_tracker + 1) & 0x1;
	DMA_CINT = 0; // Clear interrupt bit
}

void systick_isr(void) {
	systick_millis_count++;

	// poll system
}

// Interrupt routine to time state updates
void ftm0_isr(void) {
	FTM0_SC &= ~FTM_SC_TOF;

	eventManager.queueEvent(
		EventManager::kEventState,
		F_UPDATE,
		EventManager::kLowPriority);
}	
