/*
 * dac.h
 *
 * 
 *
 */

#include "kinetis.h" 
#include <stdint.h>
#include "util/delay.h"
#include "system.h"

#ifndef DAC_H
#define DAC_H

class DACInterface {

	private:
		
		// Config parameters
	
	public:

		DACInterface () {};
		~DACInterface () {};

		void Init (volatile uint16_t source[]);

};








#endif

