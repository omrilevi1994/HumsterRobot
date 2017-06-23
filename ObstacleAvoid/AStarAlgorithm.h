/*
 * AStarAlgorithm.h
 *
 *  Created on: May 27, 2016
 *      Author: colman
 */

#ifndef ASTARALGORITHM_H_
#define ASTARALGORITHM_H_

#include "set"
#include "vector"
#include "Graph.h"
#include "math.h"

class AStarAlgorithm {

private:
	vector<vector<Node> > graph;
	Cell start;
	Cell goal;
	set<Cell> openSet;
	set<Cell> closedSet;
	vector<Cell> totalPath;

public:
	AStarAlgorithm(vector<vector<Node> > graph, Cell start, Cell goal);
	virtual ~AStarAlgorithm();
	vector<Cell> StartAlgorithm();
	double getGValue(Cell from, Cell to);
	bool setContains(set<Cell> nodeSet, Cell current);
	Cell getLowestFValue();
	double estimatedHeuristicCost(Cell from, Cell to);
	void reconstructPath();
	void fillHeuristic();
	void fillGAndFValues(Cell from);
};

#endif /* ASTARALGORITHM_H_ */
