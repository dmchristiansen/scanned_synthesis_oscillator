/*
 * Author: Daniel Christiansen
 *
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include "system.h"
//#include <algorithm>
#include "Arduino.h"


class ButtonInterface {

	private:

		static const uint8_t buttonCount = 1;
		uint16_t button_state[buttonCount];
		uint32_t pins[buttonCount] = {7};
	
	public:

		ButtonInterface();
		~ButtonInterface() {};

		void updateState();

		inline bool justPressed(int32_t index) {
			return (button_state[index] == 0x8000);
		}

		inline bool pressed(int32_t index) {
			return (button_state[index] == 0x0000);
		}

		inline bool justReleased(int32_t index) {
			return (button_state[index] == 0x7FFF);
		}
		
		inline bool released(int32_t index) {
			return (button_state[index] == 0xFFFF);
		}

		inline bool immediateVal(int32_t index) {
			return (digitalRead(pins[index]));
		}
};

#endif


