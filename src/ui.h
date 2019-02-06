/*
 * Author: Daniel Christiansen
 *
 * This file contains the definition of the UserInterface class,
 * which manages the polling of inputs (switches, pots, and cv inputs).
 * 
 * It also contains system-specific definitions of pin mappings,
 * to make the module interface classes more generic.
 * This might be moved to 'system.h' at some point.
 *
 */

#ifndef UI_H
#define UI_H

#include "button.h"
#include "adc.h"

// information for mapping from ADC input to channel specific value 
enum MapType {
	LINEAR = 0,
	EXPONENTIAL,
	LOG,
	INVERSE,
	INV_EXP
};

enum PinMapping {
	COARSE_PITCH,
	FINE_PITCH,
	MASS_POT,
	SPRING_POT,
	DAMP_POT,
	SHAPE_POT
};

struct MappingGuide {
	uint8_t pinNumber;
	MapType mapping;
	float scale;
};

class UserInterface {

	private:

		ButtonInterface buttons;
		ADCInterface adc;

		static const uint8_t buttonCount = 1;
		static const uint8_t adcPinCount = 6;
		uint8_t adcState;
		
		MappingGuide adcPins[adcPinCount] = {
			{14,	INVERSE,	1.0f},	// coarse pitch
			{15,	INVERSE,	0.1f,},	// fine pitch
			{4,		LINEAR,		10.0f},	// mass
			{5,		LINEAR, 	10.0f},	// spring k
			{6,		LINEAR,		10.0f},	// damping
			{7,		LINEAR,		1.0f}		// impulse quality
		};

		volatile uint16_t pinValueBuffer[adcPinCount] = {0};

	public:

		UserInterface() {};
		~UserInterface() {};

		void Init();
		void poll();
};

#endif


