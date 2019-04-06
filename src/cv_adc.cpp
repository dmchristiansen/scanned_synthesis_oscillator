/*
 *
 */

#include "cv_adc.h"

uint8_t CVADC::channels[CV_LAST] = {	
	4,	// CV_PITCH
	5,	// CV_SHAPE
	6,	// CV_STRENGTH
	7,	// CV_RATE
	17,	// CV_MASS
	8,	// CV_DAMP
	9,	// CV_SPRING
	32	// CV_CENTER
};

void CVADC::Init() {

	adc_.Init();

}

void CVADC::scan() {
	
	// get adc result
	int32_t pin_value = adc_.readValue();
	
	// if conversion was complete...
	if (pin_value != -1) {
		values[index] = static_cast<uint16_t>(pin_value & 0xFFFF);
		last_read_ = index;
		index++;
		if (index >= CV_LAST) index = 0;
		adc_.startSingleRead(channels[index]);
	}

}

