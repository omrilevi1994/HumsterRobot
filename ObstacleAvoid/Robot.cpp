/*
 * Robot.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(Hamster *hamster,WaypointManager *wpManager) :hamster(hamster), prevLocation(0,0,0), currLocation(0,0,0) {
	// TODO Auto-generated constructor stub
	this->wpManager = wpManager;
	updatePose();
}
/*
 * Params:
 * Description:
 */
double Robot::getDeltaX() const {
	return currLocation.getX() - prevLocation.getX();
}
/*
 * Params:
 * Description:
 */
double Robot::getDeltaY() const {
	return currLocation.getY() - prevLocation.getY();
}
/*
 * Params:
 * Description:
 */
double Robot::getDeltaYaw() const {
	return currLocation.getYaw() - prevLocation.getYaw();
}
/*
 * Params:
 * Description:
 */
void Robot::updatePose() {
	Pose pose = hamster->getPose();

	prevLocation.setX(currLocation.getX());
	prevLocation.setY(currLocation.getY());
	prevLocation.setYaw(currLocation.getYaw());

	currLocation.setX(pose.getX());
	currLocation.setY(pose.getY());
	currLocation.setYaw(pose.getHeading());
}
/*
 * Params:
 * Description:
 */
void Robot::printRobotPosition(){
	cout << "Robot X: " << currLocation.getX() << "Robot Y: " << currLocation.getY() << "Robot YAW: " << currLocation.getYaw() << endl;
}

void Robot::goToWayPoint(int yaw){
	while (!wpManager->isNearWaypoint(currLocation.x,currLocation.y,yaw)){
		hamster->sendSpeed(0.1,0);
	}

	while (!wpManager->isInWaypoint(currLocation.x,currLocation.y,yaw)){
			hamster->sendSpeed(0.05,0);
	}

	hamster->sendSpeed(0,0);

}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}
