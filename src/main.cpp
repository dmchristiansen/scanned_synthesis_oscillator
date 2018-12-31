/*
 * TODO:
 *
 * Functionality:
 * - Port to teensy 3.6
 * - Improve state update algorithm 
 * - Add input to excite system
 * - Add add parameter control pots
 *
 * Structure:
 * - Abstract from hardware slightly (module interfaces)
 *
 */





#include "mass_spring.h"
#include "oscillator.h"
#include "Arduino.h"
#include "dac.h"
#include "kinetis.h"
#include "system.h"
#include "arm_math.h"

void tpm_setup();

volatile uint16_t sample_buffer_0[OUTPUT_BUFFER_SIZE] __attribute__((aligned (OUTPUT_BUFFER_SIZE*2)));
volatile uint16_t sample_buffer_1[OUTPUT_BUFFER_SIZE] __attribute__((aligned (OUTPUT_BUFFER_SIZE*2)));

// These shouldn't be global variables, but I'm not sure where they go yet...
volatile uint8_t buffer_tracker = 0;
volatile uint8_t buffer_flag = 0;
volatile uint8_t buffer_0_ready = 0;
volatile uint8_t buffer_1_ready = 0;

volatile uint8_t state_flag = 0;

volatile uint8_t led_val = 0;

uint16_t F_UPDATE = 100;
uint16_t UPDATE_PS = 16;
uint16_t UPDATE_TIMER = F_BUS / (F_UPDATE * UPDATE_PS);

DACInterface dac0;

extern "C" int main(void) {
	MassSystem massSystem{};
	Oscillator osc{};
	uint16_t table_size = 128;
	
	// phase_step = audio frequency / sample frequency
	osc.phase_step = (220.0/(float)22050);

	// Fill sample buffers
	//massSystem.generate_table(sample_buffer_0, table_size, osc.phase_step, &osc.phase_accumulator); 
	for (int i = 0; i<OUTPUT_BUFFER_SIZE; i++) {
		sample_buffer_0[i] = 2048+(int16_t)(2047*sin(((float)i)*6.28319/((float)OUTPUT_BUFFER_SIZE)));
		//sample_buffer_0[i] = (int16_t)(4096/OUTPUT_BUFFER_SIZE)*i;
	}
	
	buffer_0_ready = 1;
	massSystem.generate_table(sample_buffer_1, table_size, osc.phase_step, &osc.phase_accumulator); 
	buffer_1_ready = 1;
	
	pinMode(13, OUTPUT);

	dac0.Init(sample_buffer_0);
	//digitalWrite(13, HIGH);

	//tpm_setup();


	// Main task loop
	while(1) {
		// Sample buffer population
		if (buffer_flag) {
			if (buffer_tracker) {
				massSystem.generate_table(sample_buffer_0, table_size, osc.phase_step, &osc.phase_accumulator);
				buffer_0_ready = 1;
			} else {
				massSystem.generate_table(sample_buffer_1, table_size, osc.phase_step, &osc.phase_accumulator);
				buffer_1_ready = 1;
			}
			buffer_flag = 0;
		}
		
		// Mass system state update
		else if (state_flag) {
			massSystem.update_state(0.01);
			state_flag = 0;
		}
	}

}


void tpm_setup() {
	FTM0_SC = 0;	// Disable TPM0
	FTM0_CNT = 0;	// Clear counter
	//FTM0_MOD = 0x3A98; // Set mod to 15,000
	FTM0_MOD = (0x3A98) >> 2;

	FTM0_SC |=
		(FTM_SC_TOF			// Clear overflow flag
		|FTM_SC_TOIE		// Enable overflow interrupt
		|FTM_SC_CLKS(1)	// Enable timer, count on internal clock
		|FTM_SC_PS(4));	// Set timer prescaler to 16	
	
	// Enable PTM interrupts
	NVIC_SET_PRIORITY(IRQ_FTM0, 64);
	NVIC_ENABLE_IRQ(IRQ_FTM0);
}

// Interrupt routine to set next sample buffer as DMA source
void dma_ch0_isr(void) {
	//DMA_DSR_BCR0 &= DMA_DSR_BCR_DONE; // Clear done bit in DMA status register
	if (buffer_tracker && buffer_0_ready) {
		buffer_1_ready = 0;
		DMA_TCD0_SADDR = sample_buffer_0;
		buffer_tracker = 0;
	} else if (!buffer_tracker && buffer_1_ready) {
		buffer_1_ready = 0;
		DMA_TCD0_SADDR = sample_buffer_1;
		buffer_tracker = 1;
	} else {
		digitalWrite(13, HIGH);
	}
	buffer_flag = 1;
	//DMA_DSR_BCR0 |= 256;  // Reset transfer byte count
	digitalWrite(13, HIGH);
}

// Interrupt routine to time state updates
void ftm0_isr(void) {
	FTM0_SC |= FTM_SC_TOF;
	
	state_flag = 1;
}	
