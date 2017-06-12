/*
 * RandomWalk.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: user
 */

#include "RandomWalk.h"

#define SPAN 100

RandomWalk::RandomWalk(HamsterAPI::Hamster * hamster) {
	this->hamster = hamster ;

}


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

	for (size_t i = distances.size() / 2 - angle_from_center / 2;i < distances.size() / 2 + angle_from_center / 2; i++)
		if (distances[i] < scan.getMaxRange() / 6.0)
			collisions++;

	return collisions >= angle_from_center / 6.0;
}

bool RandomWalk::isFrontFree() {
	// Degrees : [90, 270]

	std::vector<double> distances;

	getScansBetween(130, 230, distances);

	return !willCollide(distances, 40);
}

bool RandomWalk::isLeftFree() {
	// Degrees : [180,360]

	std::vector<double> distances;

	getScansBetween(180, 270, distances);

	return !willCollide(distances, 40);
}

bool RandomWalk::isRightFree() {
	// Degrees : [0, 180]

	std::vector<double> distances;

	getScansBetween(90, 180, distances);

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
	for (int i = 0; i < 5000; i++)
	{
		if(!isLeftFree()) break ;
		hamster->sendSpeed(0.2, 45.0);
	}
}

void RandomWalk::turnRight() {
	HamsterAPI::Log::i("Client", "Turning Right");
	for (int i = 0; i < 5000; i++)
	{
		if(!isRightFree()) break ;
		hamster->sendSpeed(0.2, -45.0);
	}
}

void RandomWalk::moveBackwards() {
	HamsterAPI::Log::i("Client", "Moving Backwards");
	while(  !isRightFree() && !isLeftFree())
		hamster->sendSpeed(-0.4, 0.0);
	if (isLeftFree())
		turnLeft();
	else
		turnRight();
}

void RandomWalk::stopMoving() {
	hamster->sendSpeed(0.0, 0.0);
}



double RandomWalk::getNearestObstacleDistanceForword(HamsterAPI::LidarScan scan, int span) {
	if(span > 180)
		return -1;

	double min_dist = 10;

	for(int i = 180 - span/2; i < 180 + span/2 + 1; i++) {
		if(scan.getDistance(i) < min_dist)
			min_dist = scan.getDistance(i);
	}

	return min_dist;
}

double RandomWalk::getNearestObstacleDistanceLeft(HamsterAPI::LidarScan scan, int span) {
	if(span > 180)
		return -1;

	double min_dist = 10;

	for(int i = 180 ; i < 180 + span ; i++) {
		if(scan.getDistance(i) < min_dist)
			min_dist = scan.getDistance(i);
	}

	return min_dist;
}

double RandomWalk::getNearestObstacleDistanceRight(HamsterAPI::LidarScan scan, int span) {
	if(span > 180)
		return -1;

	double min_dist = 10;

	for(int i = 180 - span; i < 180 ; i++) {
		if(scan.getDistance(i) < min_dist)
			min_dist = scan.getDistance(i);
	}

	return min_dist;
}
/*
void RandomWalk::obstacleAvoidence(HamsterAPI::Hamster* hamster) {
	int angels[2] = {45, -45};
	double nearestObs = this->getNearestObstacleDistanceForword(hamster->getLidarScan(), SPAN);

	srand(time(NULL));

	if(nearestObs > 0.7)
		hamster->sendSpeed(0.5, 0);
	else
	{
		double obsR = (int)getNearestObstacleDistanceRight(hamster->getLidarScan(),SPAN);
		double obsL = (int)getNearestObstacleDistanceLeft(hamster->getLidarScan(),SPAN);
		int index ;
		int r = rand() % 8 ;
		if(obsL<obsR)
		{
			if(r<5)
				index = 0;
			else
				index = 1;
		}
		else
		{
			if(r<5)
				index = 1;
			else
				index = 0;
		}


		if(nearestObs > 0.3)
			hamster->sendSpeed(0.2 ,angels[index]);
		else
			hamster->sendSpeed(-0.2, angels[index]);
	}

}
*/

void RandomWalk::obstacleAvoidence(HamsterAPI::Hamster* hamster) {

	if(isFrontFree())
		moveForward();
	else{
		bool r = isRightFree();
		bool l = isLeftFree();
		if(r && l)
		{
			if(rand()%2==0)
				turnRight();
			else
				turnLeft();
		}
		else if(r)
			turnRight();
		else if(l)
			turnLeft();
		else
			moveBackwards();
	}

}
RandomWalk::~RandomWalk() {
	// TODO Auto-generated destructor stub
}

