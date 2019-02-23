/*
 * Author: Daniel Christiansen
 *
 * This file contains the implementation of the UserInterface class,
 * which manages the polling of inputs (switches, pots, and cv inputs).
 * The 'poll' function should be called by the systick_isr.
 *
 */

#include "ui.h"

void UserInterface::Init() {

	cv_input.Init();	

}

void UserInterface::poll() {


	// scan current button values & debounce
	buttons.updateState();

	for (int i = 0; i < buttonCount; i++) {
		if (buttons.justPressed(i)) {
			eventManager.queueEvent(
				EventManager::kEventButtonPress,
				i,
				EventManager::kLowPriority);
		}
	}

	digitalWrite(13, buttons.immediateVal(0) ? LOW : HIGH);

	// process cv/pot input buffer
	cv_input.convert();
	

}


