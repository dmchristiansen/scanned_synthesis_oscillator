/*
 * Author: Daniel Christiansen
 *
 */

#ifndef ADC_H
#define ADC_H

#include "system.h"

class ADCInterface {

	private:

		uint8_t moduleNumber;


	public:

		ADCInterface() {};
		~ADCInterface() {};

		void Init();

		int32_t startSingleRead(uint8_t pin);
		int32_t readValue();

};

#endif

