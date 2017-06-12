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

	Map(OccupancyGrid &ogrid);
	void initializeMap();
	void initMap();
	void drawParticles(vector<Particle *> particles);
	void showMap();

	virtual ~Map();
};

#endif /* MAP_H_ */
