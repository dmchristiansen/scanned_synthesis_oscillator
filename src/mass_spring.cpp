/*
 * system.cpp
 * 11/16/2018
 *
 * Daniel Christiansen
 *
 */

#include "mass_spring.h"
#include <cmath>
#include "kinetis.h"

MassSystem::MassSystem()
{

	// initialize values in hammer table
	for (int i = 0; i < n_weights; i++) {
		// sine
		hammerTable[0][i] = sinf((float)i * (6.238 / (float)n_weights));
		// triangle
		if (i < n_weights/4) hammerTable[1][i] = ((4.0 * i) / (float)n_weights);
		else if (i > (n_weights - (n_weights / 4))) 
			hammerTable[1][i] = ((4.0 * ((i + n_weights / 4) % n_weights)) / (float)n_weights) - 1.0;
		else hammerTable[1][i] = 1.0 - ((4.0 * (i - n_weights / 4)) / (float)n_weights);
		// saw
		hammerTable[2][i] = (2.0 * ((i + (n_weights / 2)) % n_weights) / (float)n_weights) - 1;
		// square
		hammerTable[3][i] = (i <= (n_weights / 2)) ? 1.0f : -1.0f;
	}
}

void MassSystem::excite(float excitation[]) {
	for (int i=0; i < N_WEIGHTS; i++) {
		weights[i].accel += excitation[i];
	}
}

void MassSystem::pluck(float shape_) {
	
	hammerIndex = shape_;
	
	float integral;
	float fractional = std::modf(hammerIndex, &integral);
	int32_t tableIndex = (int32_t)integral;	
	
	for (int32_t weightIndex = 0; weightIndex < n_weights; weightIndex++) {
	
		// generate new noise values each time...
		/*
		if (tableIndex == 3) {
			hammerTable[3][weightIndex] = (float)((rand() % 100 - 50) / 50.0f);
		}
		*/

		// interpolate between hammer shapes
		impulse[weightIndex] = 
			(hammerTable[tableIndex][weightIndex] * (1.0f - fractional)) + 
			(hammerTable[(tableIndex + 1) % 4][weightIndex] * fractional);

		//weights[weightIndex].accel = 0;
		//weights[weightIndex].velocity = 0;
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

void MassSystem::updateState(float h, ModelState* state) {
	float fk, fc, fz;

	for (int32_t i = 0; i < n_weights; i++) {
		weights[i].mass = state->mass;
		weights[i].z = state->z;
		weights[i].center = state->center;
		spring_k[i] = state->k;
	}

	// Update velocities from accelerations
	for (int i=0; i < N_WEIGHTS; i++) {
		float impulseDelta = impulse[i] * h * 10.0f;
		weights[i].velocity += (h * weights[i].accel)
			+ (impulseDelta / weights[i].mass);
		impulse[i] -= impulseDelta;
	}

	// Update positions from velocities
	for (int i=0; i < N_WEIGHTS; i++) {
		weights[i].pos += (h * weights[i].velocity);
	}

	weights[0].pos = 0;
	weights[n_weights].pos = 0;

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
/*
	float dist = weights[n_weights - 1].pos - weights[0].pos;
	for (int i=0; i < N_WEIGHTS; i++) {
		float prev_dist = dist;
		dist = weights[(i + 1) % n_weights].pos - weights[i].pos;
		weights[i].accel = 
			(((dist - prev_dist) * spring_k[i]) - 
			(weights[i].z * weights[i].velocity)) / weights[i].mass; 
	}
*/
	
	
	// Update accelerations from positions (for next update)
	for (int i=0; i < N_WEIGHTS; i++) {
		int prev_i = (i - 1 + N_WEIGHTS) % N_WEIGHTS;
		int next_i = (i + 1) % N_WEIGHTS;
		
		// force from centering springs
		fc = (weights[i].pos * weights[i].center * -1.0f);
		// force from springs between weights
		fk = fc + ((weights[prev_i].pos - weights[i].pos) +
			(weights[next_i].pos - weights[i].pos)) * spring_k[i];
		// opposing damping force
		fz = weights[i].z * weights[i].velocity;
		// limit damping force
		if (((fk > 0) && (fz > fk)) || ((fk < 0) && (fz < fk))) fz = fk;
		// total acceleration
		weights[i].accel = (fk - fz) / weights[i].mass;
	}

}

// Fills table with a number of samples from system
void MassSystem::generateTable(volatile uint16_t* table, uint16_t sample_count, float phase_step, volatile float* phase_offset) {
	for (uint16_t i=0; i < sample_count; i++) {
		int32_t sample_ = (int32_t)(sample(*phase_offset) * 512) + 2048;
		if (sample_ > 4096)
			table[i] = (uint16_t)4096;
		else if (sample_ < 0)
			table[i] = (uint16_t)0;
		else
			table[i] = (uint16_t)sample_;

		//table[i] = (int16_t)(this->sample(*phase_offset) * 512) + 2048;
		*phase_offset = fmodf((*phase_offset + phase_step), 1.0f);
	}
}

void MassSystem::setMass(float newMass) {

	if (newMass < minMass) (newMass = minMass); 

	for (int i = 0; i < n_weights; i++) {
		weights[i].mass = newMass;
	}

}

void MassSystem::setSpring(float newSpring) {
	
	// a = 0.0667, b = 16

	for (int i = 0; i < n_weights; i++) {
		spring_k[i] = newSpring;
		//spring_k[i] = 0.0667f * powf(16.0f, (newSpring * ((float)i / (float)n_weights))) - 0.0667f;
	}
}

void MassSystem::setZ(float newDamp) {

	for (int i = 0; i < n_weights; i++) {
		weights[i].z = newDamp;
	}
}	

void MassSystem::setShape(float newShape) {
	hammerIndex = newShape;
}

void MassSystem::setCenter(float newCenter) {
	for (int i = 0; i < n_weights; i++) {
		weights[i].center = newCenter;
	}
}


