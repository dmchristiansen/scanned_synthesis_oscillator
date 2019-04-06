/*
 *
 */

#ifndef CV_ADC_H
#define CV_ADC_H

#include "system.h"
#include "adc.h"

enum ControlVoltages {
	CV_PITCH = 0,
	CV_SHAPE,
	CV_STRENGTH,
	CV_RATE,
	CV_MASS,
	CV_DAMP,
	CV_SPRING,
	CV_CENTER,
	CV_LAST
};

class CVADC {

	private:

		ADCInterface adc_ = ADCInterface(1);
		static uint8_t channels[CV_LAST];
		uint16_t values[CV_LAST] = {};
		uint8_t index = 0;
		uint8_t last_read_ = 0;

	public:

		CVADC(){};
		~CVADC(){};
		void Init();

		void scan();
		uint8_t last_read() {return last_read_;};
		uint16_t value(uint8_t index_) {return values[index_];};
};

#endif

