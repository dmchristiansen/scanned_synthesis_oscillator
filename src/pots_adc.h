/*
 *
 *
 */

#ifndef POTS_ADC_H
#define POTS_ADC_H

#include "system.h"
#include "adc.h"

enum Potentiometers {
	POT_COARSE = 0,
	POT_FINE,
	POT_SHAPE,
	POT_STRENGTH,
	POT_RATE,
	POT_ATTEN,
	POT_MASS,
	POT_DAMP,
	POT_SPRING,
	POT_CENTER,
	POT_LAST
};

class PotsADC {

	private:

		ADCInterface adc_ = ADCInterface(0);

		static uint8_t channels[POT_LAST];
		uint8_t last_read_ = 0;
		uint8_t index = 0;
		uint16_t values[POT_LAST] = {};

	public:

		PotsADC(){};
		~PotsADC(){};
		void Init();

		void scan();

		inline uint8_t last_read() const {return last_read_;}
		inline uint16_t value(uint32_t index) const {return values[index];}

};


#endif

