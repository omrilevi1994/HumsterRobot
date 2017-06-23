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
	int height=ogrid.getHeight();
	int width=ogrid.getWidth();

	Map(OccupancyGrid &ogrid, int mapResolutionCM,int robotHeight1, int robotWidth1){
		resolustion = mapResolutionCM;
		robotHeight = robotHeight1;
		robotWidth = robotWidth1;
	}
	void initializeMap();
	void initMap();
	void drawParticles(vector<Particle *> particles);
	void showMap();
	void inflateMatrix(int i, int j) ;
	virtual ~Map();
};

#endif /* MAP_H_ */
