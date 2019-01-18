/*
 * system.h
 * 11/16/2018
 *
 * Daniel Christiansen
 * 
 */

#include <stdint.h>

#ifndef MASS_SPRING_NETWORK_H
#define MASS_SPRING_NETWORK_H

#define N_WEIGHTS 20

struct Weight_t
{
	volatile float mass;
	volatile float pos;
	volatile float velocity;
	volatile float accel;
	volatile float z;
};

class MassSystem 
{
	private:

		uint8_t n_weights = N_WEIGHTS;
		Weight_t weights[N_WEIGHTS];
		float spring_k[N_WEIGHTS]; 

		uint32_t update_interval;
		uint32_t interval_counter;
    
	public:

    MassSystem();
		void excite(float[]);
		void pluck(float[]);
		float sample(float);
		void update_state(float);
		void generate_table(volatile uint16_t*, uint16_t, float, volatile float*);
};

#endif
