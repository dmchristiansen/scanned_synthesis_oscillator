/*
 *
 *
 */

#include "cv_input.h"
#include "Arduino.h"

MappingGuide CVInput::potMap[POT_LAST] = {
	{LIN,	-4.0f,		4.0f,		1.0f},	// POT_COARSE 
	{LIN,	-0.4f,		0.4f,		0.1f},	// POT_FINE
	{LIN,	0.0f,			3.0f,		3.0f},	// POT_SHAPE
	{LIN, 0.0f,			1.0f,		1.0f},	// POT_STRENGTH
	{LOG, 0.01f,	50.0f, 1000.0f},	// POT_RATE
	{LIN, -1.0f,		1.0f,		1.0f},	// POT_ATTEN
	{LIN,	0.01f,		50.0f,	10.0f},	// POT_MASS
	{LOG,	0.0125f,	81.0f,	1.0f},	// POT_DAMP
	{LOG,	0.0125f,	81.0f,	10.0f},	// POT_SPRING
	{LOG,	0.0125f,	81.0f,	10.0f}	// POT_CENTER
};

void CVInput::init(SystemState* state_) {

	pots.Init();	
	cv.Init();
	state = state_;
	note = baseFrequency;
}

void CVInput::convert() {
	uint8_t index;

	// update pot readings
	pots.scan();
	index = pots.last_read();
	pots_raw[index] = pots.value(index);
	pots_mapped[index] = mapCV(pots_raw[index], index);
	
	// low-pass filter mapped values
	// these should be a per-value lpf rate
	for (int32_t i = 0; i < POT_LAST; i++) {
		pots_lp[i] += 0.01f * (pots_mapped[i] - pots_lp[i]);
	}
	
	// update cv readings
	cv.scan();
	index = cv.last_read();
	cv_raw[index] = cv.value(index);
	cv_mapped[index] = mapValueToVolt(cv_raw[index]);

	// update state values
	
	note += 0.5f * (mapPitch(pots_lp[POT_COARSE] + pots_lp[POT_FINE] + cv_mapped[CV_PITCH]) - note);
	state->note = note;
	state->shape = pots_lp[POT_SHAPE];
	state->strength = pots_lp[POT_STRENGTH];
	state->mass = pots_lp[POT_MASS];
	state->damp = pots_lp[POT_DAMP];
	state->spring = pots_lp[POT_SPRING];
	state->center = pots_lp[POT_CENTER];
}

// map CV input from ADC to meaningful value
float CVInput::mapCV(uint16_t input, int32_t pin) {
	
	float result;
	float min = potMap[pin].min;
	float max = potMap[pin].max;
	float scale = potMap[pin].scale;

	switch (potMap[pin].mapping) {
		case (LIN):
			result = 
				(float)input * ((max - min)/ADC_MAX) 
				+ min;
			if (result < min) result = min;
			else if (result > max) result = max;
			break;
		case (EXP):
			result = powf(2.0f, ((float)input / scale));
			if (result > max) result = max;
			break;
		case (LOG):
			result = scale * 
				(min * powf(max, (float)input/ADC_MAX) - min);
			break;
		case (INV):
			result = ((float)input * ((min - max)/ADC_MAX)) 
				+ max + max;
			break;
		default:
			result = 0.0f;
			break;
	};

	return result;
}

// map input value to voltage
// This just reverses the op-amp, it needs to map adc value to voltage,
// then reverse op-amp transform (two functions?)
float CVInput::mapValueToVolt(uint16_t input) {
	// map from ADC value back to 0V - 3.3V range
	float result = (float)input * (3.3/ADC_MAX);	
	
	// CV input range: -5V to 5V
	// op-amp maps to 0V to 3.3V, through inverting input
	// so, Vout = (-0.33 * Vin) + 1.65V
	return (result - 1.65) * -3.03; 
}

// map values for coarse, fine, and v/oct pitch controls into target frequency
float CVInput::mapPitch(float volts) { return baseFrequency * powf(2, (volts)); }




