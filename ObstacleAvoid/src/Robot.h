/*
 * Robot.h
 *
 *  Created on: Jan 18, 2017
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <HamsterAPIClientCPP/Hamster.h>

#include "Location.h"

using namespace HamsterAPI;
using namespace std;

class Robot {
private:
	Location currLocation;
	Location prevLocation;
	Hamster *hamster;

public:
	Robot(Hamster *hamster);
	double getDeltaX() const;
	double getDeltaY() const;
	double getDeltaYaw() const;
	void updatePose();
	void printRobotPosition();
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
