/*
 * dac.h
 *
 * 
 *
 */

#include "kinetis.h" 
#include <stdint.h>
#include "util/delay.h"

#ifndef DAC_H_
#define DAC_H_

class DACInterface {

	private:
		
		// Config parameters
		uint32_t F_SAMPLE = 22050;
		uint16_t SAMPLE_TIMER = F_BUS / F_SAMPLE;
	
	public:

		DACInterface () {};
		~DACInterface () {};

		void Init (volatile uint16_t source[]);

};








#endif

