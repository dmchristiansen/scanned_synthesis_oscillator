/*
 * TODO:
 *
 * Functionality:
 * - Implement event queue
 * - Improve state update algorithm 
 * - Add input to excite system
 * - Set up switch polling
 * - Set up ADC polling
 * - Add add parameter control pots
 *
 * Structure:
 * - Abstract from hardware slightly (module interfaces)
 * - Split DAC setup into DMAMUX/eDMA & DAC/PDB setups
 *
 */





#include "oscillator.h"
#include "Arduino.h"
#include "dac.h"
#include "kinetis.h"
#include "system.h"
#include "arm_math.h"

void tpm_setup(uint8_t, uint16_t);

volatile uint16_t output_buffer[OUTPUT_BUFFER_SIZE] __attribute__((aligned (OUTPUT_BUFFER_SIZE*2)));
volatile uint16_t* output_buffer_0 = output_buffer;
volatile uint16_t* output_buffer_1 = &output_buffer[OUTPUT_BUFFER_SIZE / 2];

// These shouldn't be global variables, but I'm not sure where they go yet...
volatile uint8_t buffer_tracker = 0;
volatile uint8_t buffer_flag = 0;
volatile uint8_t buffer_0_ready = 0;
volatile uint8_t buffer_1_ready = 0;

volatile uint8_t state_flag = 0;

volatile uint8_t led_val = 0;

volatile uint16_t led_count = 0;

uint16_t F_UPDATE = 1;
uint16_t UPDATE_PS = 16;
uint16_t UPDATE_TIMER = F_BUS / (F_UPDATE * UPDATE_PS);

DACInterface dac0;

extern "C" int main(void) {
	Oscillator osc;
	osc.Init(output_buffer, 60.0);
	
	buffer_0_ready = 1;	
	buffer_1_ready = 1;
	
	pinMode(13, OUTPUT);

	dac0.Init(output_buffer_0);
	tpm_setup(UPDATE_PS, UPDATE_TIMER);

	//digitalWrite(13, HIGH);	
	
	// Main task loop
	while(1) {
		// Sample buffer population
		if (buffer_flag) {
			if (buffer_tracker) {
				osc.generateTable(output_buffer_0);
				buffer_0_ready = 1;
			} else {
				osc.generateTable(output_buffer_1);
				buffer_1_ready = 1;
			}
			buffer_flag = 0;
		}
		
		// Mass system state update
		if (state_flag) {
			osc.updateState(0.01);
			state_flag = 0;
		}
	}

}

void tpm_setup(uint8_t prescaler, uint16_t update_timer) {

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
	
	// Enable PTM interrupts
	//NVIC_CLEAR_PENDING(IRQ_FTM0);
}

// Interrupt routine to track output buffer use & start buffer fill
void dma_ch0_isr(void) {
	DMA_CINT = 0; // Clear interrupt bit

	if (buffer_tracker && buffer_0_ready) {
		buffer_0_ready = 0;
		buffer_tracker = 0;
	} else if (!buffer_tracker && buffer_1_ready) {
		buffer_1_ready = 0;
		buffer_tracker = 1;
	} else {
		//digitalWrite(13, HIGH);
	}
	buffer_flag = 1;

}

void systick_isr(void) {
	// increment millisecond counter
	// poll system
	systick_millis_count++;
	digitalWrite(13, ((systick_millis_count & 0x200) ? HIGH : LOW));
}

//void systick_isr(void) {}

// Interrupt routine to time state updates
void ftm0_isr(void) {
	FTM0_SC &= ~FTM_SC_TOF;
	state_flag = 1;
}	
