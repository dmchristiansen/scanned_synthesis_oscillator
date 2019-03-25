/*
 * Author: Daniel Christiansen
 *
 */

#ifndef ADC_H
#define ADC_H

#include "system.h"

#define ADC_OFFSET (ADC1_SC1A - ADC0_SC1A)

// ADC module register structure
struct __attribute__((packed)) ADC_t {
	int32_t SC1A;
	int32_t SC1B;
	int32_t CFG1;
	int32_t CFG2;
	int32_t RA;
	int32_t RB;
	int32_t CV1;
	int32_t CV2;
	int32_t SC2;
	int32_t SC3;
	int32_t OFS;
	int32_t PG;
	int32_t MG;
	int32_t CLPD;
	int32_t CLPS;
	int32_t CLP4;
	int32_t CLP3;
	int32_t CLP2;
	int32_t CLP1;
	int32_t CLP0;
	int32_t CLMD;
	int32_t CLMS;
	int32_t CLM4;
	int32_t CLM3;
	int32_t CLM2;
	int32_t CLM1;
	int32_t CLM0;
};

class ADCInterface {

	private:

		static uint32_t moduleUseMask; // available ADC modules
		int32_t moduleNumber;
		int32_t moduleOffset;
		ADC_t* module = 0;

	public:

		ADCInterface();
		ADCInterface(int32_t);
		~ADCInterface() {};

		void Init();

		int32_t startSingleRead(uint8_t);
		int32_t readValue();

};

#endif

