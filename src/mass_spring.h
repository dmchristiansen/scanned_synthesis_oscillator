/*
 * system.h
 * 11/16/2018
 *
 * Daniel Christiansen
 * 
 */


#ifndef MASS_SPRING_NETWORK_H
#define MASS_SPRING_NETWORK_H

#include <stdint.h>
#include "system.h"
#include <stdlib.h>

#define N_WEIGHTS 20

struct Weight_t
{
	volatile float mass;
	volatile float pos;
	volatile float velocity;
	volatile float accel;
	volatile float z;
	volatile float center;
};

class MassSystem 
{
	private:

		uint8_t n_weights = N_WEIGHTS;
		Weight_t weights[N_WEIGHTS] = {{0}};
		float spring_k[N_WEIGHTS] = {0}; 

		float updateFreq = 1;

		const float minMass = 0.01;

		float hammerTable[5][N_WEIGHTS] = {{0}};
		float hammerIndex = 0;

		float impulse[N_WEIGHTS] = {0};

	public:

    MassSystem();
		void excite(float[]);
		void pluck(float);
		float sample(float);
		void updateState(float, ModelState*);
		void generateTable(volatile uint16_t*, uint16_t, float, volatile float*);
		void setMass(float);
		void setSpring(float);
		void setZ(float);
		void setShape(float);
		void setCenter(float);
};

#endif
