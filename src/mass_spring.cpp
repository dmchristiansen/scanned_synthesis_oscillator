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
	for (int i = 0; i < nWeights; i++) {
		// sine
		hammerTable[0][i] = sinf((float)i * (6.238 / (float)nWeights));
		// triangle
		if (i < nWeights/4) hammerTable[1][i] = ((4.0 * i) / (float)nWeights);
		else if (i > (nWeights - (nWeights / 4))) 
			hammerTable[1][i] = ((4.0 * ((i + nWeights / 4) % nWeights)) / (float)nWeights) - 1.0;
		else hammerTable[1][i] = 1.0 - ((4.0 * (i - nWeights / 4)) / (float)nWeights);
		// saw
		hammerTable[2][i] = (2.0 * ((i + (nWeights / 2)) % nWeights) / (float)nWeights) - 1;
		// square
		hammerTable[3][i] = (i <= (nWeights / 2)) ? 1.0f : -1.0f;
	}
}

void MassSystem::excite(float excitation[]) {

 	for (int i=0; i < nWeights; i++) {
		weights[i].acceleration += excitation[i];
	}

}

void MassSystem::pluck(float shape_) {
	
	hammerIndex = shape_;
	
	float integral;
	float fractional = std::modf(hammerIndex, &integral);
	int32_t tableIndex = (int32_t)integral;	
	
	for (int32_t weightIndex = 0; weightIndex < nWeights; weightIndex++) {
	
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

		//weights[weightIndex].acceleration = 0;
		//weights[weightIndex].velocity = 0;
	}
	
	for (int i = 0; i < nWeights; i++) {
		weights[i].position = impulse[i];
		weights[i].velocity = 0;
		weights[i].acceleration = 0;
	}

}

// Samples mass system at location indicated by phase pointer
// phase should be in the range [0, 1)
float MassSystem::sample(float phase) {
	float integral;

	// translate from phase to fractional 'index'
	float phase_pointer = fmodf(phase, 1.0f) * nWeights;
	float fractional = std::modf(phase_pointer, &integral);
	int i = (int)integral;	

	return this->weights[i].position + 
		((weights[(i + 1) % nWeights].position - weights[i].position) * 
		fractional);
}

void MassSystem::updateState(float h, SystemState* state) {
	float fk, fc, fz;

	for (int32_t i = 0; i < nWeights; i++) {
		weights[i].mass = state->mass;
		weights[i].damp = state->damp;
		weights[i].center = state->center;
		spring[i] = state->spring;
	}

	// Update velocities from accelerations
	for (int i=0; i < nWeights; i++) {
		float impulseDelta = impulse[i] * h * 10.0f;
		weights[i].velocity += (h * weights[i].acceleration);
		//	+ (impulseDelta / weights[i].mass);
		impulse[i] -= impulseDelta;
	}

	// Update positions from velocities
	for (int i=0; i < nWeights; i++) {
		weights[i].position += (h * weights[i].velocity);
	}

	weights[0].position = 0;
	weights[nWeights].position = 0;

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
	float dampForce, centerForce, rightForce;
	float leftForce = (weights[nWeights-1].position - weights[0].position) * spring[nWeights-1];
	for (int i = 0; i < nWeights; i++) {
		rightForce = (weights[(i+1)%nWeights].position - weights[i].position) * spring[i];
		dampForce = weights[i].velocity * damp[i];
		centerForce = -1.0f * weights[i].position * center[i];
		weights[i].acceleration = (leftForce + rightForce + dampForce + centerForce) / weights[i].mass;
		leftForce = rightForce;
	}
	*/
	
	
	// Update accelerations from positions (for next update)
	for (int i = 0; i < nWeights; i++) {
		int prev_i = (i - 1 + nWeights) % nWeights;
		int next_i = (i + 1) % nWeights;
		
		// force from centering springs
		fc = (weights[i].position * weights[i].center * -1.0f);
		// force from springs between weights
		fk = fc + ((weights[prev_i].position - weights[i].position) +
			(weights[next_i].position - weights[i].position)) * spring[i];
		// opposing damping force
		fz = weights[i].damp * weights[i].velocity;
		// limit damping force
		if (((fk > 0) && (fz > fk)) || ((fk < 0) && (fz < fk))) fz = fk;
		// total acceleration
		weights[i].acceleration = (fk - fz) / weights[i].mass;
	}

}

// Fills table with a number of samples from system
void MassSystem::generateTable(volatile uint16_t* table, uint16_t sample_count, float phase_step, volatile float* phase_offset) {
	for (uint16_t i=0; i < sample_count; i++) {
		int32_t sample_ = (int32_t)(sample(*phase_offset) * 512) + 2048;
		if (sample_ > 4095)
			table[i] = (uint16_t)4095;
		else if (sample_ < 0)
			table[i] = (uint16_t)0;
		else
			table[i] = (uint16_t)sample_;

		//table[i] = (int16_t)(this->sample(*phase_offset) * 512) + 2048;
		*phase_offset = fmodf((*phase_offset + phase_step), 1.0f);
	}
}


