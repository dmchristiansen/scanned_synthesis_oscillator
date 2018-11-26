/*
 * system.h
 * 11/16/2018
 *
 * Daniel Christiansen
 * 
 */

#include <stdint.h>

#ifndef system_h_
#define system_h_

#define N_WEIGHTS 10

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

		int n_weights = N_WEIGHTS;
		Weight_t weights[N_WEIGHTS];
		float spring_k[N_WEIGHTS]; 

    
	public:

    MassSystem();
		void excite(float[]);
		void pluck(float[]);
		float sample(float);
		void update_state(float);
		void generate_table(volatile uint16_t*, uint16_t, float, volatile float*);
};

#endif
