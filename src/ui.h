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


class UserInterface {

	private:

		ButtonInterface buttons;
		CVInput cv_input;

		static const uint8_t buttonCount = 1;
	
	public:

		UserInterface() {};
		~UserInterface() {};

		void Init();
		void poll();
};

#endif


