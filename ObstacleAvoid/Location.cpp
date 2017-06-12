/*
 * Location.cpp
 *
 *  Created on: Jan 16, 2017
 *      Author: user
 */

#include "Location.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


Location::Location(double x,double y,int yaw) : i(0), j(0)
{
	this->x=x;
	this->y=y;
	this->yaw=yaw;
}

Location::Location() : x(0), y(0), yaw(0), i(0), j(0)
{
}

 void Location::changeLocation(double x,double y,int yaw)
{
	this->x=x;
	this->y=y;
	this->yaw=yaw;
}


 Location::Location(Location* otherLocation) : i(0), j(0)
{
	this->x=otherLocation->x;
	this->y=otherLocation->y;
	this->yaw=otherLocation->yaw;
}

 Location::~Location() {
	// TODO Auto-generated destructor stub
}

void Location::print()
	{
		cout<<"X: "<<x<<"Y: "<<y<<"Yaw: "<<yaw<<endl;
	}
