/*
 * system.cpp
 * 11/16/2018
 *
 * Daniel Christiansen
 *
 */

#include "system.h"
#include <cmath>
#include "kinetis.h"

MassSystem::MassSystem()
{
	for (int i=0; i < N_WEIGHTS; i++) {
		weights[i].mass = 0.05;
		weights[i].pos = 0;
		weights[i].velocity = 0;
		weights[i].accel = 0;
		weights[i].z = 0.25;
	}
	for (int i=0; i < n_weights; i++) {
		weights[i].pos = sinf((float)i * (6.238 / (float)n_weights));
			//+ sinf((float)i * 2 * (6.238 / (float)n_weights));
	}

	for (int i=0; i < n_weights; i++) {
		spring_k[i] = 2.0;
	}
}

void MassSystem::excite(float excitation[]) {
	for (int i=0; i < N_WEIGHTS; i++) {
		weights[i].accel += excitation[i];
	}
}

void MassSystem::pluck(float pluck[]) {
	for (int i=0; i < n_weights; i++) {
		weights[i].pos += pluck[i];
	}
}

// Samples mass system at location indicated by phase pointer
// phase should be in the range [0, 1)
float MassSystem::sample(float phase) {
	float integral;

	// translate from phase to fractional 'index'
	float phase_pointer = fmodf(phase, 1.0f) * n_weights;
	float fractional = std::modf(phase_pointer, &integral);
	int i = (int)integral;	

	return this->weights[i].pos + 
		((weights[(i + 1) % n_weights].pos - weights[i].pos) * 
		fractional);
}

void MassSystem::update_state(float h) {
	// Update velocities from accelerations
	for (int i=0; i < N_WEIGHTS; i++) {
		weights[i].velocity += h * weights[i].accel;
	}

	// Update positions from velocities
	for (int i=0; i < N_WEIGHTS; i++) {
		weights[i].pos += h * weights[i].velocity;
	}

	/*
	 * The acceleration needs to be altered in the following ways:
	 * The force should be proportional to the sine of the angle
	 * 	made by the horizontal and the spring between two weights.
	 * The distance between two weights is being calculated twice now
	 * 	(each weight calcs left and right distances, then it's done
	 * 	again for the next weight, so one weight's right calculation
	 * 	is repeated for the next weights left calculation).
	 * 	Save the values to minimize calculations.
	 */

	
	// Update accelerations from positions (for next update)
	float dist = weights[0].pos - weights[0].pos;
	for (int i=0; i < N_WEIGHTS; i++) {
		float prev_dist = dist;
		dist = weights[(i + 1) % n_weights].pos - weights[i].pos;
		weights[i].accel = 
			(((dist - prev_dist) * spring_k[i]) - 
			(weights[i].z * weights[i].velocity)) / weights[i].mass; 
	}
	
	
/*	
	// Update accelerations from positions (for next update)
	for (int i=0; i < N_WEIGHTS; i++) {
		int prev_i = (i - 1 + N_WEIGHTS) % N_WEIGHTS;
		int next_i = (i + 1) % N_WEIGHTS;
		// This uses a simplified version of the calculation...
		weights[i].accel = 
			((((weights[prev_i].pos - weights[i].pos) +
			(weights[next_i].pos - weights[i].pos)) * spring_k[i]) -
			(weights[i].z * weights[i].velocity)) / weights[i].mass; 
	}
*/

}

// Fills table with a number of samples from system
void MassSystem::generate_table(volatile uint16_t* table, uint16_t sample_count, float phase_step, volatile float* phase_offset) {
	for (uint16_t i=0; i < sample_count; i++) {
		table[i] = (uint16_t)(this->sample(*phase_offset) * 512) + 2048;
		*phase_offset = fmodf((*phase_offset + phase_step), 1.0f);
	}
}



