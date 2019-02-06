/*
 * oscillator.h
 */

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <stdint.h>
#include "mass_spring.h"
#include <Arduino.h>

class Oscillator {
	
	private:

		MassSystem model;
		
		volatile uint16_t** buffer_list;
		volatile float phase_step;
		volatile float phase_accumulator;

	public:

		Oscillator() {}
		~Oscillator() {};
		void Init(volatile uint16_t** buf, float freq);

		void generateTable(int, int);
		void updateState(int, int);		
		void pluck(int, int);
		void setParam(int, int);

		void setStep(float step) {phase_step = step;};	
		
		float mapValue(int32_t, float);

};


void Oscillator::Init(volatile uint16_t** buf, float freq) {
	buffer_list = buf;
	setStep(freq/(float)F_SAMPLE);
	phase_accumulator = 0;

	model.generateTable(buffer_list[0], OUTPUT_BUFFER_SIZE, phase_step, &phase_accumulator);
}

void Oscillator::generateTable(int code, int param) {

	// this should be rewritten to work with a larger number of buffers

	//model.generateTable(buffer_list[param], OUTPUT_BUFFER_SIZE, phase_step, &phase_accumulator);

	if (param == 0)
		model.generateTable(buffer_list[0], OUTPUT_BUFFER_SIZE, phase_step, &phase_accumulator);

	if (param == 1)
		model.generateTable(buffer_list[1], OUTPUT_BUFFER_SIZE, phase_step, &phase_accumulator);
}

void Oscillator::updateState(int code, int param) {
	model.updateState(1/(float)param);
}

void Oscillator::pluck(int code, int param) {
	model.pluck();
}

void Oscillator::setParam(int code, int param) {
	
	switch (code) {
		case (EventManager::kEventUpdateFreq):
			setStep((float)param/(float)F_SAMPLE);
			break;
		case (EventManager::kEventUpdateMass):
			model.setMass(mapValue(param, 10.0f));
			break;
		case (EventManager::kEventUpdateSpring):
			model.setSpring(mapValue(param, 30.0f));
			break;
		case (EventManager::kEventUpdateDamp):
			model.setZ(mapValue(param, 50.0f));
			break;
		default:
			break;
	}
}

float Oscillator::mapValue(int32_t param, float scale) {
	
	return ((float)param * scale) / 4096.0;

}

#endif

