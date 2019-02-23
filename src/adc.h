/*
 * Author: Daniel Christiansen
 *
 */

#ifndef ADC_H
#define ADC_H

#include "system.h"

class ADCInterface {

	private:

		static uint32_t moduleUseMask; // available ADC modules
		int32_t moduleNumber;


	public:

		ADCInterface();
		ADCInterface(int32_t);
		~ADCInterface() {};

		void Init();

		int32_t startSingleRead(uint8_t pin);
		int32_t readValue();

};

#endif

