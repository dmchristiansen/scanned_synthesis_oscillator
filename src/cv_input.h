/*
 *
 * Author: Daniel Christiansen
 *
 */

#ifndef CV_INPUT_H
#define CV_INPUT_H

#include "system.h"
#include "adc.h"
#include "pots_adc.h"
#include "cv_adc.h"

// information for mapping from ADC input to channel specific value 
enum MapType {
	LIN = 0,
	EXP,
	LOG,
	INV
};

struct MappingGuide {
	MapType mapping;
	float min;
	float max;
	float scale;
};

class CVInput {

	private:

		PotsADC pots;		
		CVADC cv;
		SystemState* state;

		uint32_t adc_state;
		float note;

		static MappingGuide potMap[POT_LAST];

		volatile uint16_t pots_raw[POT_LAST] = {0};
		float pots_mapped[POT_LAST] = {0};
		float pots_lp[POT_LAST] = {0};
		float cv_raw[CV_LAST] = {0};
		float cv_mapped[CV_LAST] = {0};

		const float baseFrequency = 261.6256; // according to vcv-rack docs
		const float ADC_MAX = (float)((1 << 16) - 1);
	public:

		CVInput() {};
		~CVInput() {};

		void init(SystemState*);
		void convert();
		float mapCV(uint16_t, int32_t);
		float mapValueToVolt(uint16_t);
		float mapPitch(float);

};

#endif

