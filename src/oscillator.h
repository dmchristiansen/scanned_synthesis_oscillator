/*
 * oscillator.h
 */

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <stdint.h>
#include "mass_spring.h"

class Oscillator {
	
	private:

		MassSystem model;
		
		volatile uint16_t* buffer;
		volatile float phase_step;
		volatile float phase_accumulator;

	public:

		Oscillator() {}
		~Oscillator() {};
		void Init(volatile uint16_t* buf, float freq);

		void generateTable(volatile uint16_t* table);
		void updateState(float time_step);		
		void setStep(float step) {phase_step = step;};	

};

void Oscillator::generateTable(volatile uint16_t* table) {

	model.generateTable(table, OUTPUT_BUFFER_SIZE / 2, phase_step, &phase_accumulator);

}

void Oscillator::Init(volatile uint16_t* buf, float freq) {
	buffer = buf;
	setStep(freq/(float)F_SAMPLE);
	phase_accumulator = 0;

	model.generateTable(buffer, OUTPUT_BUFFER_SIZE, phase_step, &phase_accumulator);
}

void Oscillator::updateState(float time_step) {
	model.updateState(time_step);
}

#endif

