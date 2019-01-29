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
	
	adcState = 0;

}

void UserInterface::poll() {

	int32_t pinValue;

	// scan current button values & debounce
	buttons.updateState();



	// digitalWrite(13, digitalRead(7));
	digitalWrite(13, (GPIOD_PDIR & (1 << 2)) ? HIGH : LOW);

	for (int i = 0; i < 1; i++) {
		if (buttons.justPressed(i)) {
			eventManager.queueEvent(
				EventManager::kEventButtonPress,
				i,
				EventManager::kLowPriority);
		}
	}

	
	pinValue = adc.readValue();
	if (pinValue != -1) {
		eventManager.queueEvent(
			EventManager::kEventPot0 + adcState,
			pinValue,
			EventManager::kLowPriority);

	adcState = (adcState + 1) % adcPinCount;
	adc.startSingleRead(adcPins[adcState]);
	}

}


