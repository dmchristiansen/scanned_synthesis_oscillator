/*
 *
 *
 */

#include "cv_input.h"
#include "Arduino.h"

void CVInput::Init() {

	adc_state = 0;
	adc.Init();
	note = baseFrequency;
}

void CVInput::convert() {

	int32_t pin_value;
	// read completed conversion	
	pin_value = (int32_t)adc.readValue();
	if (pin_value != -1) {
		pots_raw[adc_state] = (uint16_t)(pin_value & 0xFFFF);
		pots_mapped[adc_state] = mapCV(pots_raw[adc_state], adc_state);
	}

	for (int32_t i = 0; i < adcPinCount; i++) {
		pots_lp[i] += 0.5f * (pots_mapped[i] - pots_lp[i]);
	}

	// Event queue should be able to pass floats...
	note += 0.9f * (mapPitch(pots_lp[COARSE_PITCH] + pots_lp[FINE_PITCH]) - note);

	// queue update events
	eventManager.queueEvent(
		EventManager::kEventUpdateFreq,
		*reinterpret_cast<int32_t*>(&note),
		EventManager::kLowPriority);

	eventManager.queueEvent(
		EventManager::kEventUpdateMass,
		*reinterpret_cast<int32_t*>(&pots_lp[MASS_POT]),
		EventManager::kLowPriority);
	
	eventManager.queueEvent(
		EventManager::kEventUpdateSpring,
		*reinterpret_cast<int32_t*>(&pots_lp[SPRING_POT]),
		EventManager::kLowPriority);
	
	eventManager.queueEvent(
		EventManager::kEventUpdateDamp,
		*reinterpret_cast<int32_t*>(&pots_lp[DAMP_POT]),
		EventManager::kLowPriority);
	
	eventManager.queueEvent(
		EventManager::kEventUpdateCenter,
		*reinterpret_cast<int32_t*>(&pots_lp[CENTER_POT]),
		EventManager::kLowPriority);
	
	eventManager.queueEvent(
		EventManager::kEventUpdateShape,
		*reinterpret_cast<int32_t*>(&pots_lp[SHAPE_POT]),
		EventManager::kLowPriority);


	// start conversion on next pin
	adc_state = (adc_state + 1) % adcPinCount;
	adc.startSingleRead(adcPins[adc_state].pinNumber);
}

// map CV input from ADC to meaningful value
float CVInput::mapCV(uint16_t input, int32_t pin) {
	
	float result;

	switch (adcPins[pin].mapping) {
		case (LIN):
			result = 
				(float)input * ((adcPins[pin].max - adcPins[pin].min)/adcMax) 
				+ adcPins[pin].min;
			if (result < adcPins[pin].min) result = adcPins[pin].min;
			else if (result > adcPins[pin].max) result = adcPins[pin].max;
			break;
		case (EXP):
			result = powf(2.0f, ((float)input / adcPins[pin].scale));
			if (result > adcPins[pin].max) result = adcPins[pin].max;
			break;
		case (LOG):
			result = adcPins[pin].scale * 
				(adcPins[pin].min * powf(adcPins[pin].max, (float)input/adcMax) - adcPins[pin].min);
			break;
		case (INV):
			result = ((float)input * ((adcPins[pin].min - adcPins[pin].max)/adcMax)) 
				+ adcPins[pin].max + adcPins[pin].max;
			break;
		default:
			result = 0.0f;
			break;
	};

	return result;
}

// map input value to voltage
// This just reverses the op-amp, it needs to map adc value to voltage,
// then reverse op-amp transform (two functions?)
float CVInput::mapValueToVolt(uint16_t input) {
	// map from ADC value back to 0V - 3.3V range
	float result = (float)input * (3.3/adcMax);	
	
	// CV input range: -5V to 5V
	// op-amp maps to 0V to 3.3V, through inverting input
	// so, Vout = (-0.33 * Vin) + 1.65V
	return (result - 1.65) * -3.03; 
}

// map values for coarse, fine, and v/oct pitch controls into target frequency
float CVInput::mapPitch(float volts) { return baseFrequency * powf(2, (volts)); }




