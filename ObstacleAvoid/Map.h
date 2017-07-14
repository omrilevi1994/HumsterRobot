/*
 * Map.h
 */

#ifndef MAP_H_
#define MAP_H_
#include "Particle.h"
#include <vector>
#include <HamsterAPIClientCPP/Hamster.h>
#include <algorithm>

using namespace std;
using namespace cv;
using namespace HamsterAPI;

class Map {
public:
	OccupancyGrid &ogrid;
	Mat mat;
	Mat inflateMat;
	int resolustion;
	int robotHeight;
	int robotWidth;
	int height;
	int width;

	Map(OccupancyGrid &ogrid, int mapResolutionCM,int robotHeight1, int robotWidth1){
		this->ogrid = ogrid;
		resolustion = mapResolutionCM;
		robotHeight = robotHeight1;
		robotWidth = robotWidth1;
		height = ogrid.getHeight();
		width = ogrid.getWidth();
	}
	void initializeMap();
	void initMap();
	void drawParticles(vector<Particle *> particles);
	void showMap();
	void inflateMatrix(int i, int j) ;
	bool InflateMatCellIsOccupied(Point point);
	virtual ~Map();
};

#endif /* MAP_H_ */
