
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
	bool isMatCellOcupied;

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
			isMatCellOcupied = false;
			for (int i = (row * resolutionRelation) ; (i < (row * resolutionRelation) + resolutionRelation) && (!isMatCellOcupied); i++)
			{
				for (int j = (col * resolutionRelation); (j < (col * resolutionRelation) + resolutionRelation) && (!isMatCellOcupied); j++)
				{
					current.y = i;
					current.x = j;
					isMatCellOcupied = map.InflateMatCellIsOccupied(current);
				}
			}

			this->nodes[row][col].occupied = isMatCellOcupied;
		}
	}
}

MatCell Graph::getCellFromPoint(Point point)
{
	int row = point.y / resolutionRelation;
	int col = point.x / resolutionRelation;
	MatCell MatCell(row,col);
	return MatCell;
}

void Graph::paintPathOnMap(Map *map, vector<MatCell> path, int r, int g, int b)
{
	for (int pathIndex = 0; pathIndex < path.size(); pathIndex++)
	{
		paintPathOnMap(map, path[pathIndex],r,g,b);
	}
}

void Graph::paintPathOnMap(Map *map, MatCell point, int r, int g, int b)
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

Point Graph::getPointFromCell(MatCell MatCell)
{
	Point point;
	point.y = (MatCell.row * resolutionRelation) + (resolutionRelation / 2);
	point.x = (MatCell.col * resolutionRelation) + (resolutionRelation / 2);

	return (point);
}
