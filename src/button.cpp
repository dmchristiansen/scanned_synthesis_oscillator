/*
 * Author: Daniel Christiansen
 *
 *
 */


#include "button.h"

ButtonInterface::ButtonInterface() {

	// Initialize GPIO pin (PD2)
	SIM_SCGC5 |= SIM_SCGC5_PORTD; // Turn on PORTD clock
	GPIOD_PDDR &= (1 << 2); // Set pin to input (default)
	PORTD_PCR2 = PORT_PCR_PS | PORT_PCR_PE;	// Enable internat pullup resistor

	// Initialize button state
	std::fill(&button_state[0], &button_state[buttonCount], 0xFF);
}

void ButtonInterface::updateState() {
	uint32_t pins[buttonCount] = {7};

	for (int i = 0; i < buttonCount; i++) {
		button_state[i] = (button_state[i] << 1) | digitalRead(pins[i]);
	}
}



