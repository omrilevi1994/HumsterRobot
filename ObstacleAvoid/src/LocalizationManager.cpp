/*
 * LocalizationManager.cpp
 *
 */

#include "LocalizationManager.h"
#include <iostream>


using namespace std;
#define PARTICLES_NUM 500
#define CHILD_PARTICLES 50
#define AMOUNT_TO_CREATE 100
#define AMOUNT_TO_KEEP 400



LocalizationManager::LocalizationManager(const OccupancyGrid &ogrid, Hamster *hamster, Map &map) : ogrid(ogrid), hamster(hamster), map(map) {}
/*
 * Params:Particle *particle
 * Description:gets a random particle in the map range
 */
void LocalizationManager::getRandomLocation(Particle *particle) {
	do {

		particle->loc.setJ(rand() % ogrid.getWidth());
		particle->loc.setI(rand() % ogrid.getHeight());

	}while (ogrid.getCell(particle->loc.getJ(), particle->loc.getI()) != CELL_FREE);

	particle->loc.setX((particle->loc.getJ() - (double)ogrid.getWidth() / 2) * ogrid.getResolution());
	particle->loc.setY(((double)ogrid.getHeight() / 2 - particle->loc.getI()) * ogrid.getResolution());

	particle->loc.setYaw(rand() % 360);
}
/*
 * Params:none
 * Description: randomize the position of all the particles when we start the program
 */
void LocalizationManager::initParticles() {
	particles.resize(PARTICLES_NUM);

	for (int i = 0; i < particles.size(); i++) {
		particles[i] = new Particle();
		getRandomLocation(particles[i]);
	}
}
/*
 * Params:Particle *particle
 * Description: gets the belief of the particle
 */
double LocalizationManager::computeBelief(Particle *particle) {
	LidarScan scan = hamster->getLidarScan();

	int hits = 0;
	int misses = 0;

	for (int i = 0; i < scan.getScanSize(); i++) {
		double angle = scan.getScanAngleIncrement() * i * DEG2RAD;

		Location currLocation = particle->loc;

		if (scan.getDistance(i) < scan.getMaxRange() - 0.001) {
			double obsX = currLocation.getX() + scan.getDistance(i) * cos(angle + currLocation.getYaw() * DEG2RAD - 180 * DEG2RAD);
			double obsY = currLocation.getY() + scan.getDistance(i) * sin(angle + currLocation.getYaw() * DEG2RAD - 180 * DEG2RAD);


			int pixelsX = obsX / ogrid.getResolution()+ ogrid.getWidth() / 2;
			int pixelsY = obsY / ogrid.getResolution()+ ogrid.getHeight() / 2;

			if (ogrid.getCell(pixelsX, pixelsY) == CELL_OCCUPIED) {
				hits++;
			} else {
				misses++;
			}
		}
	}
	return ((double)hits / (hits + misses))*1.2;
}
/*
 * Params:double deltaX, double deltaY, double deltaYaw - the change from the robot position
 * Description:calculate the x,y,i,j and yaw and send to computeBelief for each Particles in the map
 */
void LocalizationManager::updateParticles(double deltaX, double deltaY, double deltaYaw) {

	for (int i = 0; i < particles.size(); i++) {
		Particle *particle = particles[i];

		particle->loc.setX(particle->loc.getX() + deltaX);
		particle->loc.setY(particle->loc.getY() + deltaY);
		particle->loc.setYaw(particle->loc.getYaw() + deltaYaw);

		particle->loc.setI(particle->loc.getY() / ogrid.getResolution() + ogrid.getHeight() / 2);
		particle->loc.setJ(particle->loc.getYaw() / ogrid.getResolution() + ogrid.getWidth() / 2);

		if(particle->loc.getI() == 401 || particle->loc.getJ() == 419) createChildParticle(particle);

		particle->belief = computeBelief(particle);
	}

	sort(particles.begin(),particles.end(),wayToSort);

	int newIndex = AMOUNT_TO_KEEP;
	for(int i = 0; i<AMOUNT_TO_CREATE; i++){

		createChildParticle(particles[newIndex]);
		newIndex++;
	}
	//cout << "after add particles.size(): "<<particles.size() << endl;
}

/*
 * Params:Particle* oneParticle - the Particle we want to switch
 * Description:gets the Particle with a high belief and create a child and switch with a Particle that have a low belief
 */
void LocalizationManager::createChildParticle(Particle* oneParticle){
	Particle* goodParticle = this->rouletteWheelAlgorithm(CHILD_PARTICLES);
		/*double randNum = ((double)rand() / (double)RAND_MAX) - 0.5;
		oneParticle->x = goodParticle->x+randNum;
		double randNum2 = ((double)rand() / (double)RAND_MAX) - 0.5;
		oneParticle->y = goodParticle->y+randNum2;
		double randNum3 = ((double)rand() / (double)RAND_MAX) - 10;
		oneParticle->yaw = goodParticle->yaw+randNum3;

		oneParticle->iy = (double)ogrid.getHeight() / 2 - oneParticle->y / ogrid.getResolution() ;
		oneParticle->jx = oneParticle->x / ogrid.getResolution() + ogrid.getWidth() / 2;*/

	do {
		oneParticle->loc.setI(((rand() % 30) - 15 + goodParticle->loc.getI()) % ogrid.getHeight());
		oneParticle->loc.setJ(((rand() % 30) - 15 + goodParticle->loc.getJ()) % ogrid.getWidth());
		//cout << "in do while: new: " << oneParticle->iy << " , " << oneParticle->jx << "old: " << goodParticle->iy << " , " << goodParticle->jx << " , "<<goodParticle->belief<< endl;
	} while (ogrid.getCell(oneParticle->loc.getJ(),oneParticle->loc.getI()) != CELL_FREE);

	oneParticle->loc.setX((oneParticle->loc.getJ() - (double)ogrid.getWidth() / 2) * ogrid.getResolution());
	oneParticle->loc.setY(((double)ogrid.getHeight() / 2 - oneParticle->loc.getI()) * ogrid.getResolution());

	int y = (rand() % 10) - 5 + goodParticle->loc.getYaw();
	if(y < 0) y += 360;

	oneParticle->loc.setYaw(y % 360);
}
/*
 * Params:none
 * Description:print the Particles vector
 */
void LocalizationManager::printParticles() const {
	for (int i = 0; i < particles.size(); i++) {
		Particle *particle = particles[i];
		cout << "Particle " << i << ": " << particle->loc.getI() << "," << particle->loc.getJ() << "," << particle->loc.getYaw() << ", belief: " << particle->belief << endl;
	}
}
/*
 * Params:int amount the number of particles we want to sum
 * Description:sum the particles belief
 */
double LocalizationManager::sumOfBelief(int amount){
	double sum = 0;
	for(int i = 0; i < amount; i++){
		if(particles[i]->belief > 0.3)
			sum += particles[i]->belief;
	}
	return sum;
}
/*
 * Params:int particles_num - amount of good particles
 * Description: get a random number between 0 to the sum, and sum again the particles belief until
 * we get to the random number we return the particle we stop at
 */
Particle* LocalizationManager::rouletteWheelAlgorithm(int particles_num){
	double total_weight = this->sumOfBelief(particles_num);
	double randNum = ((double)rand() / (double)RAND_MAX);
	randNum = randNum * total_weight;
	int index = 0;
	double temp_sum = 0;//particles[index]->belief;
	for(int i = 0; i < particles_num; i++) {
		temp_sum += particles[i]->belief;
		if(particles[i]->belief > 0.3){
			if(temp_sum >= randNum) {
			//	cout << "rouletteWheelAlgorithm index: " << i << " : " << particles[i]->iy << ", "<<particles[i]->jx<<" , "<<particles[i]->yaw<<endl;
				return particles[i];
			}
		}
	}
	return particles[0];
}
/*
 * Params:
 * Description: return the particles vector
 */
vector<Particle *> LocalizationManager::getParticles() const {
	return particles;
}

LocalizationManager::~LocalizationManager() {}
