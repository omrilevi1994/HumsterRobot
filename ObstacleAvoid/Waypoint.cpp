/*
 * Waypoint.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: colman
 */

#include "Waypoint.h"

Waypoint::Waypoint() {
	// TODO Auto-generated constructor stub
	this->point.col = -999;
	this->point.row = -999;
	this->yaw = -999;
}

Waypoint::Waypoint(Cell point, int yaw)
{
	this->point = point;
	this->yaw = yaw;
}

Waypoint::~Waypoint() {
	// TODO Auto-generated destructor stub
}

