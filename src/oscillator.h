/*
 * oscillator.h
 */

#include <stdint.h>

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

class Oscillator {
	public:
		volatile float phase_step;
		volatile float phase_accumulator;

		Oscillator() {
			phase_step = 0;
			phase_accumulator = 0;
		}
		
};

#endif

