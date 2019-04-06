/*
 *
 */

#include "pots_adc.h"

uint8_t PotsADC::channels[POT_LAST] = {	
	17,	// POT_COARSE
	18,	// POT_FINE
	5,	// POT_SHAPE
	14,	// POT_STRENGTH
	13,	// POT_RATE
	12,	// POT_ATTEN
	6,	// POT_MASS
	7,	// POT_DAMP
	15,	// POT_SPRING
	4		// POT_CENTER
};

void PotsADC::Init() {

	adc_.Init();

}

void PotsADC::scan() {
	
	// get adc result
	int32_t pin_value = adc_.readValue();
	
	// if conversion was complete...
	if (pin_value != -1) {
		values[index] = static_cast<uint16_t>(pin_value & 0xFFFF);
		last_read_ = index;
		index++;
		if (index >= POT_LAST) index = 0;
		adc_.startSingleRead(channels[index]);
	}

}
