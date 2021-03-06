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
#include "cv_input.h"
#include "system.h"

class UserInterface {

	private:

		ButtonInterface buttons;
		CVInput* cv;
		SystemState* state;

		static const uint8_t buttonCount = 1;

		int32_t updateCounter = 0;

	public:

		UserInterface() {};
		~UserInterface() {};

		void init(CVInput*, SystemState*);
		void poll();
};

#endif


