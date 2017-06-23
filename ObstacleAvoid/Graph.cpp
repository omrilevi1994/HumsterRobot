/*
 * Graph.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: colman
 */

#include "Graph.h"

Graph::Graph(double graphResolutionInCM) {
	this->graphResolutionInCM = graphResolutionInCM;
	this->resolutionRelation = 0;
}

Graph::~Graph() {

}

void Graph::buildGraphFromMap(const Map map)
{
	this->resolutionRelation = graphResolutionInCM / map.resolustion();
	int graphRows = map.height() * map.resolustion() / graphResolutionInCM;
	int graphColumns = map.width() * map.resolustion() / graphResolutionInCM;
	bool isCellOcupied;

	this->nodes.resize(graphRows);

	for (int index = 0; index <graphRows; index++)
	{
		this->nodes[index].resize(graphColumns);
	}

	Point current;

	for (int row = 0; row < graphRows; row ++)
	{
		for (int col = 0; col < graphColumns; col ++)
		{
			isCellOcupied = false;
			for (int i = (row * resolutionRelation) ; (i < (row * resolutionRelation) + resolutionRelation) && (!isCellOcupied); i++)
			{
				for (int j = (col * resolutionRelation); (j < (col * resolutionRelation) + resolutionRelation) && (!isCellOcupied); j++)
				{
					current.y = i;
					current.x = j;
					isCellOcupied = map.checkIfInflotedMapCellIsOccupied(current);
				}
			}

			this->nodes[row][col].occupied = isCellOcupied;
		}
	}
}

Cell Graph::getCellFromPoint(Point point)
{
	int row = point.y / resolutionRelation;
	int col = point.x / resolutionRelation;
	Cell cell(row,col);
	return cell;
}

void Graph::paintPathOnMap(Map *map, vector<Cell> path, int r, int g, int b)
{
	for (int pathIndex = 0; pathIndex < path.size(); pathIndex++)
	{
		paintPathOnMap(map, path[pathIndex],r,g,b);
	}
}

void Graph::paintPathOnMap(Map *map, Cell point, int r, int g, int b)
{
	Point current;

	for (int y = point.row * resolutionRelation; y < (point.row * resolutionRelation) + resolutionRelation; y++)
	{
		for (int x = point.col * resolutionRelation; x < (point.col * resolutionRelation) + resolutionRelation; x++)
		{
			current.y = y;
			current.x = x;
			map->paintCell(current,r,g,b);
		}
	}
}

Point Graph::getPointFromCell(Cell cell)
{
	Point point;
	point.y = (cell.row * resolutionRelation) + (resolutionRelation / 2);
	point.x = (cell.col * resolutionRelation) + (resolutionRelation / 2);

	return (point);
}
