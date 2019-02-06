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

	for (int i = 0; i < buttonCount; i++) {
		if (buttons.justPressed(i)) {
			eventManager.queueEvent(
				EventManager::kEventButtonPress,
				i,
				EventManager::kLowPriority);
		}
	}

	/* This should all be pushed down into a CV-Input class */

	// read completed conversion	
	pinValue = adc.readValue();
	if (pinValue != -1)
		pinValueBuffer[adcState] = pinValue;

	// there should be a generic map function...
	// Event queue should be able to pass floats...
	int32_t newFreq = pinValueBuffer[COARSE_PITCH]
		+ pinValueBuffer[FINE_PITCH] / 10;
	int32_t newMass = pinValueBuffer[MASS_POT]; 
	int32_t newSpring = pinValueBuffer[SPRING_POT];
	int32_t newDamp = pinValueBuffer[DAMP_POT];
	int32_t newShape = pinValueBuffer[SHAPE_POT];

	// queue update events
	eventManager.queueEvent(
		EventManager::kEventUpdateFreq,
		newFreq,
		EventManager::kLowPriority);
	
	eventManager.queueEvent(
		EventManager::kEventUpdateMass,
		newMass,
		EventManager::kLowPriority);
	
	eventManager.queueEvent(
		EventManager::kEventUpdateSpring,
		newSpring,
		EventManager::kLowPriority);
	
	eventManager.queueEvent(
		EventManager::kEventUpdateDamp,
		newDamp,
		EventManager::kLowPriority);
	
	eventManager.queueEvent(
		EventManager::kEventUpdateShape,
		newShape,
		EventManager::kLowPriority);


	// start conversion on next pin
	adcState = (adcState + 1) % adcPinCount;
	adc.startSingleRead(adcPins[adcState].pinNumber);
	

}


