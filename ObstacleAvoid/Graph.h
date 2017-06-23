/*
 * Graph.h
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Map.h"
#include "set"
#include "Cell.h"

typedef struct node
{
	bool occupied;
	double fValue;
	double gValue;
	double hValue;
	Cell parrent;
}
Node;

class Graph {
private:
	double	graphResolutionInCM;
	double	resolutionRelation;
public:
	vector<vector<Node> > nodes;
	void buildGraphFromMap(const Map map);
	Graph(double graphResolutionInCM);
	virtual ~Graph();
	Cell getCellFromPoint(Point point);
	Point getPointFromCell(Cell cell);
	void paintPathOnMap(Map *map, vector<Cell> path, int r, int g, int b);
	void paintPathOnMap(Map *map, Cell cell, int r, int g, int b);
};

#endif /* GRAPH_H_ */
