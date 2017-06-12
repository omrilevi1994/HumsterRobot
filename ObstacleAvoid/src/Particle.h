/*
 * Particle.h
 *
 *  Created on: Jan 24, 2017
 *      Author: user
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Calculations.h"
class Particle {
private:
	double x,y;
	int yaw;

	Calculations * calc;

	double belif;
public:
	Particle();

	Particle(Particle* particle);

	Particle(double x, double y ,int yaw ,double  bel);

	void setPos(double x,double y,int yaw);
//col=x, row=y
	void setOGPos(int col,int row );


	bool operator<( Particle &other)  {
		return (belif <  other.getBel()) ;
	}

	virtual ~Particle();


	double getX()  {
		return x;
	}

	void setX(double x) {
		this->x = x;
	}

	double getY()  {
		return y;
	}

	void setY(double y) {
		this->y = y;
	}

	int getYaw()  {
		return yaw;
	}

	void setYaw(int yaw) {
		this->yaw = yaw;
	}

	double getBel()  {
		return belif;
	}

	void setBel(double bel) {
		this->belif = bel;
	}
};

#endif /* PARTICLE_H_ */
