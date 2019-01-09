/*
 *
 *
 */


#include "dac.h"
#include "Arduino.h"

void DACInterface::Init(volatile uint16_t source[]) {

	// Enable DMA interrupts
	NVIC_SET_PRIORITY(IRQ_DMA_CH0, 0);
	NVIC_ENABLE_IRQ(IRQ_DMA_CH0);

	SIM_SCGC2 |= SIM_SCGC2_DAC0; // enable DAC clock
	
	DAC0_C0 = 
		(DAC_C0_DACEN			// enable DAC
		|DAC_C0_DACRFS		// use DACREF_2 as ref voltage (3.3V)
		);

	// Ramp up DAC output to central value to avoid sharp edge
	for (int i=1; i < 2048; i+=4) {
		*(uint16_t*)&(DAC0_DAT0L) = i;
		delayMicroseconds(1000);
	}

	// Fill DAC buffer with center value
	for (int i=1; i < 16; i++) {
		*(int16_t*)(&DAC0_DAT0L + 2*i) = 2048;
	}

	SIM_SCGC6 |= SIM_SCGC6_DMAMUX; // enable DMAMUX clock
	SIM_SCGC7 |= SIM_SCGC7_DMA; // enable DMA clock

	DMAMUX0_CHCFG0 |= DMAMUX_SOURCE_DAC0; // set DAC0 as request source
	DMAMUX0_CHCFG0 |= DMAMUX_ENABLE;	 		// Enable DMA channel 0
	
	DMA_ERQ = DMA_ERQ_ERQ0;	// Enable requests on channel 0
	
	// Set up Transfer Control Descriptor
	DMA_TCD0_SADDR = source; // DMA source address (wavetable)
	DMA_TCD0_DADDR = &DAC0_DAT0L; // DMA destination address (DAC0)

	DMA_TCD0_SOFF = 4;	// Advance 16 bytes per read
	DMA_TCD0_DOFF = 4;	// Advance 16 bytes per write

	DMA_TCD0_ATTR =
		(DMA_TCD_ATTR_SSIZE(DMA_TCD_ATTR_SIZE_32BIT)	// 16B read size
		|DMA_TCD_ATTR_DSIZE(DMA_TCD_ATTR_SIZE_32BIT)	// 16B write size
 		//|DMA_TCD_ATTR_SMOD(0)		// No saddr modulo
		|DMA_TCD_ATTR_DMOD(31 - __builtin_clz(32))	// Restrict daddr to 32 byte range
		);

	// Set number of bytes to be transferred per minor loop
	DMA_TCD0_NBYTES_MLNO = 16;

	// Set minor loop per major loop count
	DMA_TCD0_CITER_ELINKNO = DMA_TCD_CITER_ELINKYES_CITER(OUTPUT_BUFFER_SIZE / 8);
	DMA_TCD0_BITER_ELINKNO = DMA_TCD_BITER_ELINKYES_BITER(OUTPUT_BUFFER_SIZE / 8);
	DMA_TCD0_CITER_ELINKNO = (OUTPUT_BUFFER_SIZE / 8)	& 0x7FFF;
	DMA_TCD0_BITER_ELINKNO = (OUTPUT_BUFFER_SIZE / 8) & 0x7FFF;

	DMA_TCD0_SLAST = -((int16_t)OUTPUT_BUFFER_SIZE *2); // *
	DMA_TCD0_DLASTSGA = 0; // *

	// Enable end-of-loop interrupt
	DMA_TCD0_CSR = DMA_TCD_CSR_INTMAJOR | DMA_TCD_CSR_INTHALF;
	//DMA_TCD0_CSR = 0; // *

	DAC0_C0 |=
		(DAC_C0_DACBTIEN	// Buffer top interrupt enable
		|DAC_C0_DACBWIEN	// Buffer watermark interrupt enable
		);

	DAC0_C1 |=
		(DAC_C1_DMAEN			// Enable DMA requests
		|DAC_C1_DACBFWM(3)// Set buffer watermark
		|DAC_C1_DACBFEN		// Enable buffer use
		);

	DAC0_C2 |= DAC_C2_DACBFRP(15);	// Reset buffer pointer
	//DAC0_SR = 0;									// Clear pointer flags

	// PDB setup
	
	SIM_SCGC6 |= SIM_SCGC6_PDB;		// Turn on PDB clock
	PDB0_SC |= PDB_SC_PDBEN;			// Enable PDB
	PDB0_SC	|= PDB_SC_TRGSEL(15);	// Select software trigger
	PDB0_SC	|= PDB_SC_CONT;				// Run in continuous mode

	// Set PDB to count to F_BUS / F_SAMPLE
	PDB0_MOD = (((SAMPLE_TIMER * 8) - 1) & 0xFFFF); 
	//PDB0_MOD = 500-1; // *
	
	// Set DAC trigger interval
	PDB0_DACINT0 = (uint16_t)((SAMPLE_TIMER - 1) & 0xFFFF);
	//PDB0_DACINT0 = (uint16_t)(500-1); // *

	// Enable interval trigger
	PDB0_DACINTC0 |= 0x1;

	// Latch in values to PDB control registers
	PDB0_SC |= PDB_SC_LDOK;

	// Trigger PDB to begin counting
	PDB0_SC |= PDB_SC_SWTRIG;

	// It might be possible to use the PDB to trigger DMA
	// transfers by setting PDB_MOD to 8 * DAC_INT

	//TCD_0.SADDR = 
	//TCD_0.SOFF = 	

}


