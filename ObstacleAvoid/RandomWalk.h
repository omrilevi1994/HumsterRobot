/*
 * RandomWalk.h
 *
 *  Created on: Jan 28, 2017
 *      Author: user
 */

#ifndef RANDOMWALK_H_
#define RANDOMWALK_H_
#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
using namespace HamsterAPI;
using namespace std;
class RandomWalk {
private:
	Hamster* hamster;
	WaypointManager* wpManager;
public:
	RandomWalk(Hamster *hamster ,WaypointManager *wpManager);
	void getScansBetween(double min, double max, std::vector<double> & distances);
	bool willCollide(std::vector<double> distances, int angle_from_center);
	bool isFrontFree();
	bool isLeftFree();
	bool isRightFree();
	bool isBackFree();
	void moveForward();
	void turnLeft();
	void turnRight();
	void turnLeft(int angle);
	void turnRight(int angle);
	void moveBackwards();
	void stopMoving();
	int closestAngle(int maxAngle);
	virtual ~RandomWalk();
};

#endif /* RANDOMWALK_H_ */
