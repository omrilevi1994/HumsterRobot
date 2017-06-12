/*
 * main.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: user
 */

#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
#include "Robot.h"
#include "LocalizationManager.h"
#include "Map.h"
#include "RandomWalk.h"

using namespace std;
using namespace HamsterAPI;
HamsterAPI::Hamster * hamster;


int main(int argc, char ** argv){
	try {
			sleep(2);
			hamster = new HamsterAPI::Hamster(1);
			sleep(1);

			RandomWalk randomWalk(hamster);
			OccupancyGrid ogrid = hamster->getSLAMMap();
			Map map(ogrid);
			Robot robot(hamster);
			LocalizationManager locManager(ogrid, hamster,map);

			locManager.initParticles();
			while (hamster->isConnected()) {
				try {
					map.showMap();

					if (randomWalk.isFrontFree())
						randomWalk.moveForward();
					else {
						randomWalk.stopMoving();
						int closeToRight = randomWalk.closestAngle(0);
						int closeToLeft = randomWalk.closestAngle(360);
						if((closeToRight != -1) && (closeToLeft != -1)){
							if((180 - closeToRight) <= (closeToLeft - 180)){
								if (randomWalk.isRightFree())
									randomWalk.turnRight(closeToRight);
							}else if (randomWalk.isLeftFree())
								randomWalk.turnLeft(closeToLeft);
						}else if (randomWalk.isBackFree()){
							randomWalk.moveBackwards();
						}else
							HamsterAPI::Log::i("Client", "I am stuck!");
					}
					robot.updatePose();
					//locManager.updateParticles(robot.getDeltaX(), robot.getDeltaY(), robot.getDeltaYaw());
					//locManager.printParticles();
					//map.drawParticles(locManager.getParticles());
					sleep(1);
				} catch (const HamsterAPI::HamsterError & message_error) {
						HamsterAPI::Log::i("Client", message_error.what());
				}
			}
		} catch (const HamsterAPI::HamsterError & connection_error) {
			HamsterAPI::Log::i("Client", connection_error.what());
		}
		return 0;
}

