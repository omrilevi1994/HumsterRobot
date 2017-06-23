/*
 * Waypoint.h
 *
 *  Created on: Jun 7, 2016
 *      Author: colman
 */

#ifndef WAYPOINT_H_
#define WAYPOINT_H_
#include "limits.h"
#include "Map.h"
#include "Cell.h"

class Waypoint {
public:
	Cell point;
	int yaw;

	Waypoint();
	Waypoint(Cell point, int yaw);

	void operator()(Cell point, int yaw)
	{
		this->point = point;
		this->yaw = yaw;
	}
	bool operator<(const Waypoint& wp) const
	{
		return (this->point.row*INT_MAX + this->point.col< wp.point.row*INT_MAX + wp.point.col);
	}
	void operator=(const Waypoint& wp)
	{
		this->point = wp.point;
		this->yaw = wp.yaw;
	}
	bool operator==(const Waypoint& wp) const
	{
		return (this->point == wp.point);
	}
	bool operator!=(const Waypoint& wp) const
	{
		return (this->point != wp.point);
	}


	virtual ~Waypoint();
};

#endif /* WAYPOINT_H_ */
