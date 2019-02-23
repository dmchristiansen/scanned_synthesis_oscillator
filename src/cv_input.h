/*
 *
 * Author: Daniel Christiansen
 *
 */

#ifndef CV_INPUT_H
#define CV_INPUT_H

#include "system.h"
#include "adc.h"

// information for mapping from ADC input to channel specific value 
enum MapType {
	LIN = 0,
	EXP,
	LOG,
	INV
};

enum PinMapping {
	COARSE_PITCH = 0,
	FINE_PITCH,
	MASS_POT,
	SPRING_POT,
	DAMP_POT,
	SHAPE_POT,
	CENTER_POT
};

struct MappingGuide {
	uint8_t pinNumber;
	MapType mapping;
	float min;
	float max;
	float scale;
};

class CVInput {

	private:

		ADCInterface adc;

		static const uint8_t adcPinCount = 7;
		uint32_t adc_state;
		float note;

		MappingGuide adcPins[adcPinCount] = {
			{14,	LIN,	-4.0f,	4.0f,		1.0f},	// coarse pitch
			{15,	LIN,	-0.4f,	0.4f,		0.1f},	// fine pitch
			{4,		LIN,	0.01f,		50.0f,	10.0f},	// mass
			{17,		LOG,	0.0125f,		81.0f,	10.0f},	// spring k
			{6,		LOG,	0.0125f,		81.0f,	1.0f},	// damping
			{5,	LIN,	0.0f,		3.0f,		3.0f},		// hammer shape
			{7,		LOG,	0.0125f,		81.0f,	10.0f}	// centering spring k
		};

		volatile uint16_t pots_raw[adcPinCount] = {0};
		float pots_mapped[adcPinCount] = {0};
		float pots_lp[adcPinCount] = {0};

		const float baseFrequency = 261.6256; // according to vcv-rack docs
		const float adcMax = (float)((1 << 16) - 1);
	public:

		CVInput() {};
		~CVInput() {};

		void Init();
		void convert();
		float mapCV(uint16_t, int32_t);
		float mapValueToVolt(uint16_t);
		float mapPitch(float);

};

#endif

