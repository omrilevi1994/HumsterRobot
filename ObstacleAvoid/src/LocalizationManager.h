/*
 * LocalizationManager.h
 *
 *  Created on: Jan 24, 2017
 *      Author: user
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_
#include "Particle.h"
#include "HamsterAPIClientCPP/Hamster.h"
#include <iostream>

#include "ColoredMap.h"
#define COPY_TH 0.16
#define REMOVE_TH 0.15
#define NEW_TH 0.2
#define NORMAL 1.2
using namespace std;
using namespace HamsterAPI;


class LocalizationManager {
private:
	ColoredMap* map;
	vector<Particle*> particleVector;
	vector<Particle*> mergeVector;
	double avg=0.0;

public:
	LocalizationManager(ColoredMap* map);

	void initParticles(int amount);

	void deleteParticle(int index);

	void filterParticles();

	void dupeParticle(Particle* particle);

	void mergeDupes();

	void createRandomParticle();

	void createParticle(double x,double y,int yaw,double bel);

	void getTop(int howmuch);
	void calcAvg();
	//bool comparePtrToNode(Particle* a, Particle* b) ;

	void updateParticles(HamsterAPI::LidarScan scan);

	double computeBelief(HamsterAPI::LidarScan scan,Particle* particle);
	void printParticles();

	void paintParticleVector();
	virtual ~LocalizationManager();
};

#endif /* LOCALIZATIONMANAGER_H_ */
