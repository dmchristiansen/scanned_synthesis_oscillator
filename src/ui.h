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

class UserInterface {

	private:

		ButtonInterface buttons;
		ADCInterface adc;

		static const uint8_t adcPinCount = 1;
		uint8_t adcPins[adcPinCount] = {14};
		uint8_t adcState;
		

	public:

		UserInterface() {};
		~UserInterface() {};

		void Init();
		void poll();
};

#endif


