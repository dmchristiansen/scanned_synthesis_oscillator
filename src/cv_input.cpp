/*
 *
 *
 */

#include "cv_input.h"

void CVInput::Init() {

	adcState = 0;

}

void CVInput::convert() {

	int32_t pinValue;
	// read completed conversion	
	pinValue = adc.readValue();
	if (pinValue != -1) {
		//if (pinValue < 5) {
			//pinValueBuffer[adcState] = 0;
		//} else {
			pinValueBuffer[adcState] = pinValue;
		//}
	}

	// there should be a generic map function...
	// Event queue should be able to pass floats...
	float newFreq = mapPitch(
		mapCV(pinValueBuffer[COARSE_PITCH], COARSE_PITCH)
		+ mapCV(pinValueBuffer[FINE_PITCH], FINE_PITCH)
		//+ mapValueToVolt(1));
		+ 0.0f);
	float newMass = mapCV(pinValueBuffer[MASS_POT], MASS_POT); 
	float newSpring = mapCV(pinValueBuffer[SPRING_POT], SPRING_POT);
	float newDamp = mapCV(pinValueBuffer[DAMP_POT], DAMP_POT);
	float newShape = mapCV(pinValueBuffer[SHAPE_POT], SHAPE_POT);

	digitalWrite(13, pinValueBuffer[DAMP_POT] < 2 ? HIGH : LOW);

	// queue update events
	eventManager.queueEvent(
		EventManager::kEventUpdateFreq,
		static_cast<int32_t>(newFreq),
		EventManager::kLowPriority);
	
	eventManager.queueEvent(
		EventManager::kEventUpdateMass,
		static_cast<int32_t>(newMass),
		EventManager::kLowPriority);
	
	eventManager.queueEvent(
		EventManager::kEventUpdateSpring,
		static_cast<int32_t>(newSpring),
		EventManager::kLowPriority);
	
	eventManager.queueEvent(
		EventManager::kEventUpdateDamp,
		static_cast<int32_t>(newDamp),
		EventManager::kLowPriority);
	
	eventManager.queueEvent(
		EventManager::kEventUpdateShape,
		static_cast<int32_t>(newShape),
		EventManager::kLowPriority);


	// start conversion on next pin
	adcState = (adcState + 1) % adcPinCount;
	adc.startSingleRead(adcPins[adcState].pinNumber);
}

// map CV input from ADC to meaningful value
float CVInput::mapCV(uint16_t input, uint8_t pin) {
	
	float result;

	switch (adcPins[pin].mapping) {
		case (LIN):
			result = 
				input * ((adcPins[pin].max - adcPins[pin].min)/4096) 
				+ adcPins[pin].min;
			if (result < adcPins[pin].min) result = adcPins[pin].min;
			else if (result < adcPins[pin].max) result = adcPins[pin].max;
			return result;
			break;
		case (EXP):
			result = powf(2.0f, ((float)input / adcPins[pin].scale));
			if (result > adcPins[pin].max) result = adcPins[pin].max;
			return result;
			break;
		default:
			return 0.0f;
			break;
	};
}

// map input value to voltage
// This just reverses the op-amp, it needs to map adc value to voltage,
// then reverse op-amp transform (two functions?)
float CVInput::mapValueToVolt(uint16_t input) {
	// map from ADC value back to 0V - 3.3V range
	float result = (float)input * (3.3/4096);	
	
	// CV input range: -5V to 5V
	// op-amp maps to 0V to 3.3V, through inverting input
	// so, Vout = (-0.33 * Vin) + 1.65V
	return (result - 1.65) * -3.03; 
}

// map values for coarse, fine, and v/oct pitch controls into target frequency
float CVInput::mapPitch(float volts) {
	/*
		This should be something like:
		base frequency (C4) x 
		2 ^ ((map(coarse) + map(fine)/10) + map(voct))
		Maybe?
		
	*/
	
	return baseFrequency * powf(2, (volts));
}




