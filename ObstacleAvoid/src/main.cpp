/*
 * HamsterAPIClientSimpleBehaviourExample.cpp
 *
 *  Created on: Aug 10, 2016
 *      Author: ofir
 */

#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>

#include "ColoredMap.h"
#include "Particle.h"
#include "LocalizationManager.h"
#include "RandomWalk.h"
using namespace std;
using namespace HamsterAPI;
HamsterAPI::Hamster * hamster;

/*
int Oldmain(int argc, char ** argv) {
	try {
		hamster = new HamsterAPI::Hamster(1);
		while (hamster->isConnected()) {
			try {
				if (isFrontFree())
					moveForward();
				else {
					stopMoving();
					if (isLeftFree())
						turnLeft();
					else if (isRightFree())
						turnRight();
					else if (isBackFree())
						moveBackwards();
					else
						HamsterAPI::Log::i("Client", "I am stuck!");
				}

				// Speed Getter
				// HamsterAPI::Speed speed = hamster.getSpeed();
			} catch (const HamsterAPI::HamsterError & message_error) {
				HamsterAPI::Log::i("Client", message_error.what());
			}

		}
	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}
	return 0;
}

int Oldmain2(int argc, char ** argv) {
	try {
		hamster = new HamsterAPI::Hamster(1);
		OccupancyGrid ogrid = hamster->getSLAMMap();
		 cout<< "resolution: "<< ogrid.getResolution()<<endl;
		 cout<< "Width: "<< ogrid.getWidth()<<endl;
		 cout<< "height: "<< ogrid.getHeight()<<endl;

		while (hamster->isConnected()) {
			try {
				HamsterAPI::LidarScan ld = hamster->getLidarScan();
				if (ld.getDistance(180) < 0.4) {
					hamster->sendSpeed(-0.5, 0);
					cout << "Front: " << ld.getDistance(180) << endl;
				} else if (ld.getDistance(180) < 0.8) {
					hamster->sendSpeed(0.5, 45);
					cout << "Front: " << ld.getDistance(180) << endl;
				}

				else
					hamster->sendSpeed(1.0, 0);
				//cout<<"Front: "<<ld.getDistance(180)<<endl;
				//cout<<"Left: "<<ld.getDistance(90)<<endl;
				//cout<<"Right: "<<ld.getDistance(270)<<endl;
			} catch (const HamsterAPI::HamsterError & message_error) {
				HamsterAPI::Log::i("Client", message_error.what());
			}

		}
	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}
	return 0;
}


void testYaw(HamsterAPI::Hamster * hamster){
	double yaw =hamster->getPose().getHeading();

	HamsterAPI::LidarScan scan = hamster->getLidarScan();
	cout << " ROBOT HEADING Angle:" << yaw*RAD2DEG<< endl;
	for(int i =0 ; i< scan.getScanSize();i++){
	cout << "Angle:" << i << " distance:"<< scan.getDistance(i)<< endl;
	}

}
*/

int main() {

	try {
		hamster = new HamsterAPI::Hamster(1);
		sleep(1);
		OccupancyGrid ogrid = hamster->getSLAMMap();
		ColoredMap *map=new ColoredMap(&(ogrid));
		LocalizationManager* manager=new LocalizationManager(map);
		manager->initParticles(100);
		HamsterAPI::LidarScan scan ;
		cv::Mat* mapMat;

		map->paintBasicMap();

		RandomWalk rw(hamster);

		while (hamster->isConnected()) {
			try {
				scan = hamster->getLidarScan();
				//manager->updateParticles(scan);
				//manager->filterParticles();
				mapMat=map->getMat();
			    	cv::imshow("View",*(mapMat));


				map->paintBasicMap();
				manager->paintParticleVector();

				manager->getTop(20);

				rw.obstacleAvoidence(hamster);


			} catch (const HamsterAPI::HamsterError & message_error) {
				HamsterAPI::Log::i("Client", message_error.what());
			}

		}
	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}
	return 0;

}

