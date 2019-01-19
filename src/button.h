/*
 * Author: Daniel Christiansen
 *
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include "system.h"
#include <algorithm>
#include "Arduino.h"

const uint8_t buttonCount = 1;

class ButtonInterface {

	private:

		uint8_t button_state[buttonCount];

	public:

		ButtonInterface();
		~ButtonInterface() {};

		void updateState();

		inline bool pressed(int32_t index) {
			return (button_state[index] == 0x00);
		}

		inline bool released(int32_t index) {
			return (button_state[index] == 0xFF);
		}
};

#endif


