/*
 * Author: Daniel Christiansen
 *
 * This file contains the implementation of the UserInterface class,
 * which manages the polling of inputs (switches, pots, and cv inputs).
 * The 'poll' function should be called by the systick_isr.
 *
 */

#include "ui.h"

void UserInterface::init(CVInput* cv_, SystemState* state_) {

	cv = cv_;	
	state = state_;
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

	digitalWrite(13, (buttons.pressed(0)) ? HIGH : LOW);


	// process cv/pot input buffer
	if(cv) 
		cv->convert();
	else {
		digitalWrite(13, HIGH);
	}

	updateCounter++;
	if (updateCounter >= static_cast<int32_t>(1000.0f / state->rate)) {
		updateCounter = 0;
		eventManager.queueEvent(
			EventManager::kEventState,
			static_cast<int32_t>(state->rate),
			EventManager::kLowPriority);
	}

}


