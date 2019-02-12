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
	LOG
};

enum PinMapping {
	COARSE_PITCH = 0,
	FINE_PITCH,
	MASS_POT,
	SPRING_POT,
	DAMP_POT,
	SHAPE_POT
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

		static const uint8_t adcPinCount = 6;
		uint8_t adcState;
		
		MappingGuide adcPins[adcPinCount] = {
			{14,	LIN,	-4.0f,	4.0f,		1.0f},	// coarse pitch
			{15,	LIN,	-0.4f,	0.4f,		0.1f},	// fine pitch
			{4,		LIN,	0.01f,		50.0f,	10.0f},	// mass
			{5,		LOG,	0.0125f,		81.0f,	10.0f},	// spring k
			{6,		LOG,	0.0125f,		81.0f,	1.0f},	// damping
			{7,		LIN,	0.0f,		3.0f,		3.0f}		// hammer shape
		};

		volatile uint16_t pinValueBuffer[adcPinCount] = {0};
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

