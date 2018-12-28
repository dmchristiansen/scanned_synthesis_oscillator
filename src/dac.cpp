/*
 *
 *
 */


#include "dac.h"
#include "Arduino.h"

void DACInterface::Init(volatile uint16_t source[]) {

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
		delayMicroseconds(1000);
	}

	DAC0_C1 = 
		(DAC_C1_DMAEN			// Enable DMA requests
		|DAC_C1_DACBFEN);	// DAC buffer enable


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
	PIT_LDVAL0 = SAMPLE_TIMER;	// Set timer count
	PIT_TCTRL0 |= 
		(PIT_TCTRL_TIE	// Enable Timer interrupts 
		|PIT_TCTRL_TEN); // Enable timer
	PIT_MCR = 0x0; // Re-enable PIT clock

	// Enable DMA interrupts
	NVIC_SET_PRIORITY(IRQ_DMA_CH0, 0);
	NVIC_ENABLE_IRQ(IRQ_DMA_CH0);

	DMAMUX0_CHCFG0 = 
		(DMAMUX_SOURCE_DAC0 // set DAC0 as request source
		|DMAMUX_ENABLE	 		// Enable DMA channel 0
		|DMAMUX_TRIG);			// Set trigger mode
}
