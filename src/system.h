/*
 * System wide configuration and parameters
 */

#include "arm_math.h"
#include "kinetis.h"
#include <Arduino.h>

#ifndef SYSTEM_H
#define SYSTEM_H

//namespace SSO {
	
	#include "ext/EventManager/EventManager.h"

const uint32_t F_SAMPLE = 48000;
const uint16_t SAMPLE_TIMER = F_BUS / F_SAMPLE;
const uint16_t OUTPUT_BUFFER_SIZE = 64;
const uint16_t OUTPUT_BUFFER_COUNT = 2;

const uint16_t ADC_MAX = (1 << 16) - 1;

const uint16_t F_UPDATE = 100;
const uint16_t UPDATE_PS = 16;
const uint16_t UPDATE_TIMER = F_BUS / (F_UPDATE * UPDATE_PS);

extern EventManager eventManager;

struct SystemState {
	volatile float note;
	volatile float shape;
	volatile float strength;
	volatile float rate;
	volatile float mass;
	volatile float damp;
	volatile float spring;
	volatile float center;
};

//}

#endif

