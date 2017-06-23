/*
 * Cell.h
 *
 *  Created on: Jun 3, 2016
 *      Author: colman
 */

#ifndef POINT_H_
#define POINT_H_
#include "limits.h"

class Cell {
public:
	int row;
	int col;

	Cell();
	Cell(int row, int col);

	void operator()(int col, int row)
	{
		this->col = col;
		this->row = row;
	}
	bool operator<(const Cell& point) const
	{
		return (row*INT_MAX + col < point.row*INT_MAX + point.col);
	}
	void operator=(const Cell& point)
	{
		this->col = point.col;
		this->row = point.row;
	}
	bool operator==(const Cell& point) const
	{
		return (this->col == point.col && this->row == point.row);
	}
	bool operator!=(const Cell& point) const
	{
		return (this->col != point.col || this->row != point.row);
	}

	virtual ~Cell();
};

#endif /* POINT_H_ */
