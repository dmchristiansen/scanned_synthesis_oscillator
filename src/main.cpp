/*
 * TODO:
 * - Set up DAC
 * - Set up sample buffer
 * - Sample multiple values at a time
 * - Set up DMA
 * - Set up PIT to trigger DMA at sample rate
 */

#include "system.h"
#include "Arduino.h"
#include "kinetis.h"

#define DAC_PIN A12

void dac_setup();
void dma_setup(volatile uint16_t source[]);

volatile uint16_t sample_buffer_0[128] __attribute__((aligned (256)));
volatile uint16_t sample_buffer_1[128] __attribute__((aligned (256)));
uint8_t buffer_tracker = 0;

extern "C" int main(void) {
	float i = 0.0;
	MassSystem osc{};
	uint16_t table_size = 128;
	float sample_freq = 441000;
	float phase_step = (1.0f/128.0f);

	// Fill sample buffers
	osc.generate_table(sample_buffer_0, table_size, phase_step, 0.0f); 
	for (int i = 0; i < 128; i++) {
		sample_buffer_1[i] = i * (2048 / 128);
	}

	dac_setup();	
	dma_setup(sample_buffer_0);

	pinMode(13, OUTPUT);
	delay(200);
	if ((DMA_DSR_BCR0 & DMA_DSR_BCR_BES) || (DMA_DSR_BCR0 & DMA_DSR_BCR_BED))
		digitalWrite(13, HIGH);
	/*
	while(1) {
		for (uint8_t i = 0; i < table_size; i++) {
			*(uint16_t*)&(DAC0_DAT0L) = wavetable[i];
			delay(1);
		}
	}
	*/

}

void dac_setup () {

	SIM_SCGC6 |= SIM_SCGC6_DAC0; // enable DAC clock
	DAC0_C0 = 
		(DAC_C0_DACEN			// enable DAC
		|DAC_C0_DACRFS		// use DACREF_2 as ref voltage (3.3V)
		|DAC_C0_DACBTIEN);
		//|DAC_C0_DACBBIEN);
		//|DAC_C0_DACSWTRG);// software trigger 

	// Ramp up DAC output to central value to avoid sound artifacts
	for (int i=1; i < 2048; i+=4) {
		*(uint16_t *)&(DAC0_DAT0L) = i;
		delay(1);

	*(uint16_t *)&(DAC0_DAT1L) = 3200;
	}

	DAC0_C1 = 
		(DAC_C1_DMAEN			// Enable DMA requests
		|DAC_C1_DACBFEN);	// DAC buffer enable
}

void dma_setup(volatile uint16_t source[]) {
	
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX; // enable DMAMUX clock
	SIM_SCGC7 |= SIM_SCGC7_DMA; // enable DMA clock

	DMAMUX0_CHCFG0 = 0x0; // Disable DMAMUX Channel 0		
	
	DMA_DCR0 |= 
		(DMA_DCR_EINT			// Enable interrupt on completion
		|DMA_DCR_ERQ			// Enable peripheral requests
		|DMA_DCR_CS				// Cycle-steal mode
		|DMA_DCR_SINC			// Enable source increment after read
		//|DMA_DCR_SSIZE(2) // Set source read size to 16b
		//|DMA_DCR_DSIZE(2) // Set dest write size to 16b
		|DMA_DCR_SMOD(5));// Set source address mod to 256B

	DMA_DSR_BCR0 |= (256);

	DMA_SAR0 = source; // DMA source address (wavetable)
	DMA_DAR0 = &DAC0_DAT0L; // DMA destination address (DAC0)

	SIM_SCGC6 |= SIM_SCGC6_PIT; // enable PIT clock (SIM gate)
	PIT_LDVAL0 = 50000;	// Set timer count
	PIT_TCTRL0 |= 
		(PIT_TCTRL_TIE	// Enable Timer interrupts 
		|PIT_TCTRL_TEN); // Enable timer
	PIT_MCR = 0x0; // Re-enable PIT clock

	NVIC_SET_PRIORITY(IRQ_DMA_CH0, 64);
	NVIC_ENABLE_IRQ(IRQ_DMA_CH0);

	DMAMUX0_CHCFG0 = 
		(DMAMUX_SOURCE_DAC0 // set DAC0 as request source
		|DMAMUX_ENABLE	 		// Enable DMA channel 0
		|DMAMUX_TRIG);			// Set trigger mode
}

void dma_ch0_isr(void) {
	DMA_DSR_BCR0 &= DMA_DSR_BCR_DONE; // Clear done bit in DMA status register
	if (buffer_tracker) {
		DMA_SAR0 = sample_buffer_0;
		buffer_tracker = 0;
	} else {
		DMA_SAR0 = sample_buffer_1;
		buffer_tracker = 1;
	}
	DMA_DSR_BCR0 |= 256;  // Reset transfer byte count
}

