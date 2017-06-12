/*
 * Map.cpp
 *
 */

#include "Map.h"
#define HIGH_BELIEF 0.25
Map::Map(OccupancyGrid &ogrid) : ogrid(ogrid),mat(ogrid.getWidth(), ogrid.getHeight(), CV_8UC3, cv::Scalar(255, 255, 255)){
	namedWindow("Map");
}
/*
 * Params:
 * Description:paint the map
 */
void Map::initializeMap() {

	for (int i = 0; i < ogrid.getHeight(); i++) {
			for (int j = 0; j < ogrid.getWidth(); j++) {

				Cell c = ogrid.getCell(j, i);
				if (c == CELL_FREE) {
					mat.at<cv::Vec3b>(i, j)[0] = 255;
					mat.at<cv::Vec3b>(i, j)[1] = 255;
					mat.at<cv::Vec3b>(i, j)[2] = 255;
				}
				else if (c == CELL_OCCUPIED)
				{
					mat.at<cv::Vec3b>(i, j)[0] = 0;
					mat.at<cv::Vec3b>(i, j)[1] = 0;
					mat.at<cv::Vec3b>(i, j)[2] = 0;
				}
				else
				{
					mat.at<cv::Vec3b>(i, j)[0] = 128;
					mat.at<cv::Vec3b>(i, j)[1] = 128;
					mat.at<cv::Vec3b>(i, j)[2] = 128;

				}
			}
		}
}
/*
 * Params:vector<Particle *> particles
 * Description:draw the Particles in the map
 */
void Map::drawParticles(vector<Particle *> particles) {
	initializeMap();
	for(int i = 0; i < 5; i++){
		Location* loc = particles[i]->loc;
		mat.at<Vec3b>(loc->getI(), loc->getJ())[0] = 0;
		mat.at<Vec3b>(loc->getI(), loc->getJ())[1] = 128;
		mat.at<Vec3b>(loc->getI(), loc->getJ())[2] = 0;
	}
	for (int i = 5; i < particles.size(); i++) {
		Location* loc = particles[i]->loc;
		if(particles[i]->belief > HIGH_BELIEF){
			mat.at<Vec3b>(loc->getI(), loc->getJ())[0] = 255;
			mat.at<Vec3b>(loc->getI(), loc->getJ())[1] = 0;
			mat.at<Vec3b>(loc->getI(), loc->getJ())[2] = 0;
		}else{
			mat.at<Vec3b>(loc->getI(), loc->getJ())[0] = 0;
			mat.at<Vec3b>(loc->getI(), loc->getJ())[1] = 0;
			mat.at<Vec3b>(loc->getI(), loc->getJ())[2] = 255;
		}
	}
}
/*
 * Params:
 * Description:
 */
void Map::showMap() {
	// Show the matrix on the window
	cv::imshow("Map", mat);

	// Delay for 1 millisecond to allow the window to process
	// incoming events
	cv::waitKey(1);
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

