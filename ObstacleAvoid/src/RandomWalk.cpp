/*
 * RandomWalk.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: user
 */

#include "RandomWalk.h"

RandomWalk::RandomWalk(Hamster *hamster): hamster(hamster) {}


void RandomWalk::getScansBetween(double min, double max, std::vector<double> & distances) {
	HamsterAPI::LidarScan scan = hamster->getLidarScan();

	for (size_t i = 0; i < scan.getScanSize(); i++) {
		double degree = scan.getScanAngleIncrement() * i;
		if (degree >= min && degree <= max)
			distances.push_back(scan.getDistance(i));
	}
}


bool RandomWalk::willCollide(std::vector<double> distances, int angle_from_center) {
	HamsterAPI::LidarScan scan = hamster->getLidarScan();

	int collisions = 0;

	for (size_t i = distances.size() / 2 - angle_from_center / 2;
			i < distances.size() / 2 + angle_from_center / 2; i++)
		if (distances[i] < scan.getMaxRange() / 4.0)
			collisions++;

	return collisions >= angle_from_center / 4.0;
}


bool RandomWalk::isFrontFree() {
	// Degrees : [90, 270]

	std::vector<double> distances;

	getScansBetween(90, 270, distances);

	return !willCollide(distances, 40);
}


bool RandomWalk::isLeftFree() {
	// Degrees : [180,360]

	std::vector<double> distances;

	getScansBetween(180, 360, distances);

	return !willCollide(distances, 40);
}


bool RandomWalk::isRightFree() {
	// Degrees : [0, 180]

	std::vector<double> distances;

	getScansBetween(0, 180, distances);

	return !willCollide(distances, 40);
}


bool RandomWalk::isBackFree() {
	// Degrees : [270,360], [0, 90]

	std::vector<double> distances;

	getScansBetween(270, 360, distances);
	getScansBetween(0, 90, distances);

	return !willCollide(distances, 40);
}


void RandomWalk::moveForward() {
	HamsterAPI::Log::i("Client", "Moving Forward");
	hamster->sendSpeed(0.4, 0.0);
}

void RandomWalk::turnLeft() {
	HamsterAPI::Log::i("Client", "Turning Left");
	while (!isFrontFree())
		hamster->sendSpeed(0.1, 45);
}

void RandomWalk::turnRight() {
	HamsterAPI::Log::i("Client", "Turning Right");
	while (!isFrontFree())
		hamster->sendSpeed(0.1, -45);
}

void RandomWalk::turnLeft(int angle) {
	HamsterAPI::Log::i("Client", "Turning Left");
	int angleToMove = angle - 180;
	while (!isFrontFree())
		hamster->sendSpeed(0.1, angleToMove);
}

void RandomWalk::turnRight(int angle) {
	HamsterAPI::Log::i("Client", "Turning Right");
	int angleToMove = angle - 180;
	while (!isFrontFree())
		hamster->sendSpeed(0.1, angleToMove);
}

void RandomWalk::moveBackwards() {
	HamsterAPI::Log::i("Client", "Moving Backwards");
	while (!isLeftFree() && !isRightFree() && isBackFree())
		hamster->sendSpeed(-0.4, 0.0);
	if (isLeftFree())
		turnLeft();
	else
		turnRight();
}

void RandomWalk::stopMoving() {
	hamster->sendSpeed(0.0, 0.0);
}


int RandomWalk::closestAngle(int maxAngle){
	HamsterAPI::LidarScan scan = hamster->getLidarScan();
	int defaultAngle = 180;
	if(maxAngle < defaultAngle){
		for(int i=defaultAngle; i>=maxAngle;i--){
			double distance = scan.getDistance(i);
			if(fabs(distance-scan.getMaxRange())<0.01){
				return i;
			}
		}
	}else{
		for(int i=defaultAngle; i<=maxAngle;i++){
			double distance = scan.getDistance(i);
			if(fabs(distance-scan.getMaxRange())<0.01){
				return i;
			}
		}
	}
	return -1;
}

RandomWalk::~RandomWalk() {
	// TODO Auto-generated destructor stub
}
