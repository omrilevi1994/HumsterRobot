/*
 * RandomWalk.h
 *
 *  Created on: Mar 9, 2017
 *      Author: user
 */

#ifndef RANDOMWALK_H_
#define RANDOMWALK_H_

#include <stdio.h>
#include <stdlib.h>
#include "HamsterAPIClientCPP/Hamster.h"
#include <time.h>

using namespace std;

class RandomWalk {

private:
	HamsterAPI::Hamster * hamster;

public:
	RandomWalk(HamsterAPI::Hamster * hamster);
	double getNearestObstacleDistanceForword(HamsterAPI::LidarScan scan, int span);
	double getNearestObstacleDistanceLeft(HamsterAPI::LidarScan scan, int span);
	double getNearestObstacleDistanceRight(HamsterAPI::LidarScan scan, int span);
	void obstacleAvoidence(HamsterAPI::Hamster* hamster);
	void getScansBetween(double min, double max, std::vector<double> & distances);
	bool willCollide(std::vector<double> distances, int angle_from_center);
	bool isFrontFree();
	bool isLeftFree();
	bool isRightFree();
	bool isBackFree();
	void moveForward();
	void turnLeft() ;
	void turnRight();
	void moveBackwards();
	void stopMoving() ;
	virtual ~RandomWalk();
};

#endif /* RANDOMWALK_H_ */
