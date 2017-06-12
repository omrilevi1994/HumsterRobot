/*
 * LocalizationManager.h
 *
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#include "Particle.h"
#include <vector>
#include <HamsterAPIClientCPP/Hamster.h>
#include "Map.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace HamsterAPI;

class LocalizationManager {
private:
	const OccupancyGrid &ogrid;
	Hamster *hamster;
	Map &map;
	void getRandomLocation(Particle *particle);
	double computeBelief(Particle *particle);

public:
	vector<Particle *> particles;
	LocalizationManager(const OccupancyGrid &ogrid, Hamster *hamster, Map &map);
	void initParticles();
	void updateParticles(double deltaX, double deltaY, double deltaYaw);
	void createChildParticle(Particle* oneParticle);
	double sumOfBelief(int amount);
	Particle* rouletteWheelAlgorithm(int particles_num);
	void printParticles() const;

	vector<Particle *> getParticles() const;

	virtual ~LocalizationManager();

	struct wayToSort {
		bool operator()(Particle* i,Particle* j) { return i->belief > j->belief; }
	}wayToSort;
};

#endif /* LOCALIZATIONMANAGER_H_ */
