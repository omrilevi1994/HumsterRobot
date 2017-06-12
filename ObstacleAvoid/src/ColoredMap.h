/*
 * Map.h
 *
 *  Created on: Jan 24, 2017
 *      Author: user
 */

#ifndef MAP_H_
#define MAP_H_
#include "Particle.h"
#include "HamsterAPIClientCPP/Hamster.h"
#include <iostream>

using namespace std;
using namespace HamsterAPI;

class ColoredMap {
private:
	OccupancyGrid* og;
	cv::Mat* mat;
	int rows,cols;
	double resolution;

public:
	ColoredMap(OccupancyGrid* og);

	int xToCol(double x);
	int yToRow(double y);
	double colTox(int col);
	double rowToy(int row);
	void paintBasicMap();
	void paintOneParticle(Particle* particle);
	void paintLocationRed(int col,int row);
	void paintLocationBlue(int col,int row);


	virtual ~ColoredMap();

	int getCols()  {
		return cols;
	}

	void setCols(int cols) {
		this->cols = cols;
	}

	 cv::Mat* getMat()  {
		return mat;
	}

	void setMat( cv::Mat*& mat) {
		this->mat = mat;
	}

	 OccupancyGrid* getOg()  {
		return og;
	}

	void setOg( OccupancyGrid*& og) {
		this->og = og;
	}

	double getResolution()  {
		return resolution;
	}

	void setResolution(double resolution) {
		this->resolution = resolution;
	}

	int getRows() const {
		return rows;
	}

	void setRows(int rows) {
		this->rows = rows;
	}
};

#endif /* MAP_H_ */
