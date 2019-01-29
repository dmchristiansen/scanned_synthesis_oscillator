/*
 *
 */

#include "adc.h"


void ADCInterface::Init() {

	// SIM_SOPT7 (ADC trigger selection)

	SIM_SCGC6 |= SIM_SCGC6_ADC0; // ADC0 clock gate
	//SIM_SCGC3 |= SIM_SCGC3_ADC1; // ADC1 clock gate

	ADC1_SC1A = ADC_SC1_ADCH(14); // Select ADC input channel
	
	ADC1_CFG1 =
		(ADC_CFG1_ADIV(0)		// Set clock division
		|ADC_CFG1_MODE(3)		// Conversion mode (3 = 16 bit)
		|ADC_CFG1_ADICLK(0)	// Select input clock (0 = bus clock)
	);

	ADC1_CFG2 |= ADC_CFG2_MUXSEL;	// select ADCxxb channels

	ADC1_SC3 =
		(ADC_SC3_AVGE			// Enable hardware averaging
		|ADC_SC3_AVGS(0)	// # of samples to average (0 = 4)
	);

	// calibration sequence
	while (1) {
		ADC1_SC3 |= ADC_SC3_CAL;	// start calibration
		while (ADC1_SC3 & ADC_SC3_CAL) {}; // wait for completion
		if (!(ADC1_SC3 & ADC_SC3_CALF)) break; // if sucessful, end sequence
	}

	
}

// starts a read on specified pin
int32_t ADCInterface::startSingleRead(uint8_t pin) {

	// check for active conversion
	if (ADC1_SC2 & ADC_SC2_ADACT)
		return -1;

	// set input channel to correct pin & start conversion
	ADC1_SC1A = (ADC1_SC1A & 0xFFFFFFE0) | (pin & 0x1F);

	return 0;

}

int32_t ADCInterface::readValue() {

	// check for completed conversion
	if (!(ADC1_SC1A & ADC_SC1_COCO))
		return -1;

	// return result
	return ADC1_RA;

}


