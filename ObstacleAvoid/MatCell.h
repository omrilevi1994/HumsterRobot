/*
 * MatCell.h
 *
 *  Created on: Jun 3, 2016
 *      Author: colman
 */

#ifndef POINT_H_
#define POINT_H_
#include "limits.h"

class MatCell {
public:
	int row;
	int col;

	MatCell();
	MatCell(int row, int col);

	void operator()(int col, int row)
	{
		this->col = col;
		this->row = row;
	}
	bool operator<(const MatCell& point) const
	{
		return (row*INT_MAX + col < point.row*INT_MAX + point.col);
	}
	void operator=(const MatCell& point)
	{
		this->col = point.col;
		this->row = point.row;
	}
	bool operator==(const MatCell& point) const
	{
		return (this->col == point.col && this->row == point.row);
	}
	bool operator!=(const MatCell& point) const
	{
		return (this->col != point.col || this->row != point.row);
	}

	virtual ~MatCell();
};

#endif /* POINT_H_ */
