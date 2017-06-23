/*
 * Particle.h
 *
 *  Created on: Jan 11, 2017
 *      Author: user
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Location.h"

class Particle {
public:
	Location* loc = new Location();
	double belief;

	Location* getLocation()
	{
		return loc;
	}
};

#endif /* PARTICLE_H_ */
