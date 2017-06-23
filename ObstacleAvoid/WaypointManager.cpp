/*
 * WaypointManager.cpp
 *
 *  Created on: Jun 4, 2016
 *      Author: colman
 */

#include "WaypointManager.h"
#include "Waypoint.h"
#include "Cell.h"
#include "Map.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
WaypointManager::WaypointManager(vector<Cell> path, double gridResolution, double mapResolution)
{
	int oldyaw = -999;
	int counter = 0;
	waypoints.resize(path.size());
	for (int i = 0; i < path.size(); i++)
	{
		Cell point;
		Waypoint waypoint;

		point.col = path[i].col;
		point.row = path[i].row;

		waypoint.point = point;

			if (i == path.size())
			{
				waypoint.yaw = -1;
			}
			else
				{
				if (path[i + 1].col == waypoint.point.col ||
					path[i + 1].row == waypoint.point.row)
				{
					if (path[i + 1].col == waypoint.point.col &&
							path[i + 1].row == waypoint.point.row + 1)
					{
						waypoint.yaw = 270;
					}
					else if (path[i + 1].col == waypoint.point.col &&
							path[i + 1].row == waypoint.point.row - 1)
					{
						waypoint.yaw = 90;
					}
					else if (path[i + 1].col == waypoint.point.col + 1 &&
							path[i + 1].row == waypoint.point.row)
					{
						waypoint.yaw = 0;
					}
					else
					{
						waypoint.yaw = 180;
					}
				}
				else if (path[i + 1].col == waypoint.point.col + 1 &&
						path[i + 1].row == waypoint.point.row + 1 )
				{
					waypoint.yaw = 315;
				}
				else if (path[i + 1].col == waypoint.point.col + 1 &&
						path[i + 1].row == waypoint.point.row - 1 )
				{
					waypoint.yaw = 45;
				}
				else if (path[i + 1].col == waypoint.point.col - 1 &&
						path[i + 1].row == waypoint.point.row + 1 )
				{
					waypoint.yaw = 225;
				}
				else
				{
					waypoint.yaw = 135;
				}
			}

			if (waypoint.yaw != oldyaw)
			{
				waypoints[counter++] = waypoint;
				oldyaw = waypoint.yaw;
			}
		}

		Waypoint first = waypoints[0];
		currWaypoint.point = first.point;
		currWaypoint.yaw = first.yaw;
		nextWaypoint.point = first.point;
		nextWaypoint.yaw = first.yaw;
		waypoints.resize(counter);

	this->gridResolution = gridResolution;
	this->mapResolution = mapResolution;
}

// Creating way point every "num_of_cells" item on the path
//void WaypointManager::buildWaypointVector(int numberOfCells)
//{
//	Waypoint waypoint;
//	int oldyaw = -999;

//	for (int i = 0; i < astarPath.size(); i++)
//	{
//		}
//}

void WaypointManager::setNextWaypoint(Waypoint next)
{
	currWaypoint.point = nextWaypoint.point;
	currWaypoint.yaw = nextWaypoint.yaw;

	nextWaypoint.point = next.point;
	nextWaypoint.yaw = next.yaw;
}


bool WaypointManager::isInWaypoint(double x,double y, double yaw)
{
	double dx = nextWaypoint.point.col - x;
	double dy = nextWaypoint.point.row - y;
	double distance = sqrt(pow(dx, 2) + pow(dy, 2));

	// Checking if the robot hit the way point, considering tolerance
	if (distance <= 0.8)
	{
		return true;
	}

	return false;
}

bool WaypointManager::isNearWaypoint(double x,double y, double yaw)
{
	double dx = nextWaypoint.point.col - x;
	double dy = nextWaypoint.point.row - y;
	double distance = sqrt(pow(dx, 2) + pow(dy, 2));

	// Checking if the robot hit the way point, considering tolerance
	if (distance <= 1.5)
	{
		return true;
	}

	return false;
}

WaypointManager::~WaypointManager() {}
