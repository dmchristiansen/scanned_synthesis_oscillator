/*
 * System wide configuration and parameters
 */

#include "arm_math.h"
#include "kinetis.h"
#include <Arduino.h>

#ifndef SYSTEM_H
#define SYSTEM_H

const uint32_t F_SAMPLE = 22050;
const uint16_t SAMPLE_TIMER = F_BUS / F_SAMPLE;
const uint16_t OUTPUT_BUFFER_SIZE = 128;
const uint16_t OUTPUT_BUFFER_COUNT = 2;



#endif

