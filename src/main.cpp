/*
 * TODO:
 * - Improve state update algorithm 
 * - Omptimize?  Can't generate samples at 44.1kHz
 * - Add input to excite system
 * - Add add parameter control pots
 */



#include "system.h"
#include "oscillator.h"
#include "Arduino.h"
#include "kinetis.h"

void dac_setup();
void dma_setup(volatile uint16_t source[]);
void tpm_setup();

volatile uint16_t sample_buffer_0[128] __attribute__((aligned (256)));
volatile uint16_t sample_buffer_1[128] __attribute__((aligned (256)));

// These shouldn't be global variables, but I'm not sure where they go yet...
volatile uint8_t buffer_tracker = 0;
volatile uint8_t buffer_flag = 0;
volatile uint8_t buffer_0_ready = 0;
volatile uint8_t buffer_1_ready = 0;

volatile uint8_t state_flag = 0;

volatile uint8_t led_val = 0;

uint32_t F_SAMPLE = 22050;
uint16_t SAMPLE_TIMER = F_BUS / F_SAMPLE;

uint16_t F_UPDATE = 100;
uint16_t UPDATE_PS = 16;
uint16_t UPDATE_TIMER = F_BUS / (F_UPDATE * UPDATE_PS);
extern "C" int main(void) {
	float i = 0.0;
	MassSystem massSystem{};
	Oscillator osc{};
	uint16_t table_size = 128;
	float sample_freq = 441000;
	
	// phase_step = audio frequency / sample frequency
	osc.phase_step = (220.0/(float)F_SAMPLE);

	// Fill sample buffers
	massSystem.generate_table(sample_buffer_0, table_size, osc.phase_step, &osc.phase_accumulator); 
	buffer_0_ready = 1;
	massSystem.generate_table(sample_buffer_1, table_size, osc.phase_step, &osc.phase_accumulator); 
	buffer_1_ready = 1;

	dac_setup();	
	dma_setup(sample_buffer_0);
	
	pinMode(13, OUTPUT);
	tpm_setup();


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
	DMA_DSR_BCR0 &= DMA_DSR_BCR_DONE; // Clear done bit in DMA status register
	if (buffer_tracker && buffer_0_ready) {
		buffer_1_ready = 0;
		DMA_SAR0 = sample_buffer_0;
		buffer_tracker = 0;
	} else if (!buffer_tracker && buffer_1_ready) {
		buffer_1_ready = 0;
		DMA_SAR0 = sample_buffer_1;
		buffer_tracker = 1;
	} else {
		digitalWrite(13, HIGH);
	}
	buffer_flag = 1;
	DMA_DSR_BCR0 |= 256;  // Reset transfer byte count
}

// Interrupt routine to time state updates
void ftm0_isr(void) {
	FTM0_SC |= FTM_SC_TOF;
	
	state_flag = 1;
}	
