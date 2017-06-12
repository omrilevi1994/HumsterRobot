/*
 * Particle.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: user
 */

#include "Particle.h"

Particle::Particle() {
	this->calc=new Calculations();
}

Particle::Particle(Particle* particle)
{
	this->x=particle->getX();
	this->y=particle->getY();
	this->yaw=particle->getYaw();
	this->belif=particle->getBel();
	this->calc=new Calculations();

}

//TODO: check if needed
Particle::Particle(double x,double y,int yaw,double bel)
{
	this->x=x;
	this->y=y;
	this->yaw=yaw;
	this->belif=bel;
	this->calc=new Calculations();
}

void Particle::setPos(double x,double y,int yaw)
{
	this->x=x;
	this->y=y;
	this->yaw=yaw;
}
Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

