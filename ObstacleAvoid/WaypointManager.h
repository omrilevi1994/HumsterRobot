/*
 * WaypointManager.h
 *
 *  Created on: Jun 4, 2016
 *      Author: colman
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_
#include "Map.h"
#include <set>
#include "Graph.h"
#include "math.h"
#include "Waypoint.h"
#include "Cell.h"

using namespace std;
#include <iostream>


class WaypointManager {
public:
	vector<Waypoint> waypoints;
	Waypoint currWaypoint;

	WaypointManager(vector<Cell> path, double gridResolution, double mapResolution);
	void buildWaypointVector(int numberOfCells);
	void setNextWaypoint(Waypoint Next);
	bool isInWaypoint(double x,double y, double yaw);
	bool isNearWaypoint(double x,double y, double yaw);
	virtual ~WaypointManager();

private:
	vector<Cell> astarPath;
	bool isVerticle = 0;
	Waypoint nextWaypoint;
	double gridResolution;
	double mapResolution;

	double calculateYaw(double m, Cell from, Cell to);
	double calculateIncline(Cell from, Cell to);
};

#endif /* WAYPOINTMANAGER_H_ */
