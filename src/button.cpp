/*
 * Author: Daniel Christiansen
 *
 *
 */


#include "button.h"

ButtonInterface::ButtonInterface() {

	
	// Initialize GPIO pin (PD2)
	SIM_SCGC5 |= SIM_SCGC5_PORTD; // Turn on PORTD clock
	//GPIOD_PDDR &= (1 << 2); // Set pin to input (default)
	PORTD_PCR2 |= 
		(PORT_PCR_PS 			// Enable internal pull resistor
		|PORT_PCR_PE 			// Set resistor to pullup
		|PORT_PCR_MUX(1)	// Set pin mode to GPIO
	);	

	//pinMode(7, INPUT);	

	// Initialize button state
	//std::fill(&button_state[0], &button_state[buttonCount], 0xFF);
	for (int i = 0; i < buttonCount; i++) {
		button_state[i] = 0xFFFF;
	}
}

void ButtonInterface::updateState() {

	for (int i = 0; i < buttonCount; i++) {
		button_state[i] = (button_state[i] << 1) | digitalRead(pins[i]);
	}
}



