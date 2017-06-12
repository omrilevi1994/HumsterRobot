/*
 * LocalizationManager.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: user
 */

#include "LocalizationManager.h"
#include <algorithm>    // std::sort

LocalizationManager::LocalizationManager(ColoredMap* map)
{
	this->map=map;
}


void LocalizationManager::calcAvg(){
	std::vector<Particle*>::iterator begin = this->particleVector.begin();
	std::vector<Particle*>::iterator end = this->particleVector.end();
	double sum=0;

	int size= particleVector.size();
	for(int i=0 ; i<size ;i++){
		sum+= particleVector[i]->getBel();
	}
	avg=sum/size;
}


void LocalizationManager::getTop(int howmuch){
	std::vector<Particle*>::iterator begin = this->particleVector.begin();
	std::vector<Particle*>::iterator end = this->particleVector.end();
	double sum=0;
	double avg=0;
	int size= particleVector.size();
	calcAvg();

	cout<<"FOR AVG:"<<avg<<endl;
	for(int i=0 ; i<howmuch ;i++){
			if(particleVector[i]->getBel()>avg)
				cout<<"#"<<i+1<<"BEL:"<<particleVector[i]->getBel()<<endl;
		}


}

void LocalizationManager::printParticles(){
for (int i = 0;i < particleVector.size(); ++i) {
	Particle* particle = particleVector[i];
	/*if(particle->getBel()>0.3)
	cout << "Particle " << i << ": " << particle->getX()<< "," << particle->getY()<< ", Belief: " << particle->getBel()<< endl;
*/
}
}

	void LocalizationManager::initParticles(int amount)
	{
		for(int i=0;i<amount;i++)
		{
			this->createRandomParticle();
		}
		this->mergeDupes();

	}

	void LocalizationManager::deleteParticle(int index)
	{
		std::vector<Particle*>::iterator begin = this->particleVector.begin();
		if(index<this->particleVector.size())
		{
			this->particleVector.erase(begin+index);
		}
	}

	void LocalizationManager::filterParticles()
	{
		calcAvg();
		for(int i=0;i<this->particleVector.size();i++)
		{
			if(this->particleVector[i]->getBel()<avg)
			{
				this->deleteParticle(i);
			}
			else
			{
				this->dupeParticle(this->particleVector[i]);
			}
		}
		if(this->particleVector.empty() && this->mergeVector.empty())
		{
			;//this->initParticles(200);
		}
		else
		{
			this->mergeDupes();

		}
	}

	void LocalizationManager::dupeParticle(Particle* particle)
	{
		calcAvg();
		if(particle->getBel()>avg*1.5)
		{

			double x,y,bel;
			int yaw;
			bel=particle->getBel();
			x=particle->getX();
			y=particle->getY();
			yaw=particle->getYaw();

			this->createParticle(x+2,y-5,(yaw+20)%360,bel);
			this->createParticle(x-5,y+5,(yaw-20)%360,bel);
			this->createParticle(x+2,y+2,(yaw+45)%360,bel);
			this->createParticle(x-5,y+2,(yaw-45)%360,bel);
			this->createParticle(x+2,y+2,(yaw+5)%360,bel);
			this->createParticle(x-5,y-2,(yaw-5)%360,bel);

		}
	}

	void LocalizationManager::mergeDupes()
	{

		if(!this->mergeVector.empty())
		{
		std::vector<Particle*>::iterator begin = this->mergeVector.begin();
		std::vector<Particle*>::iterator end = this->mergeVector.end();
	//	this->particleVector.insert(this->particleVector.end(),begin,end);
			for(;begin!=end;begin++)
			{
				this->particleVector.push_back((*begin));

			}
			this->mergeVector.clear();
		}
	}

	void LocalizationManager::createRandomParticle()
	{
		int col,row;
		double x,y;
			int yaw;
			do
			{
				col= rand() % this->map->getCols() ;
				 row= rand() % this->map->getRows() ;
				 yaw = rand() %360;
			}while(this->map->getOg()->getCell(col,row)!= CELL_FREE);
			x=this->map->colTox(col);
			y=this->map->rowToy(row);
			this->createParticle(x,y,yaw,NEW_TH);
	}

	void LocalizationManager::createParticle(double x,double y,int yaw,double bel)
	{
		Particle* particle=new Particle(x,y,yaw,bel);
		this->mergeVector.push_back(particle);

	}

	void LocalizationManager::updateParticles(HamsterAPI::LidarScan scan)
	{
		for (int i = 0;i < particleVector.size(); i++) {
				Particle* particle = particleVector[i];
				//particle->updatePosition(particle->getParticlePos()->getX()+(deltaX),particle->getParticlePos()->getY()+(deltaY),((particle->getParticlePos()->getYaw())%360+deltaYaw)%360);

				/*particle->i = particle->y / ogrid.getResolution();
				particle->j = particle->x / ogrid.getResolution();*/
				double oldbel = particle->getBel();

				particle->setBel( /*NORMAL*oldbel**/(computeBelief(scan,particle)));
			}
	}

	double LocalizationManager::computeBelief(HamsterAPI::LidarScan scan,Particle* particle)
	{
		int hits=0;
			int misses=0;
			for(int i=0; i< scan.getScanSize();i++){
				double angle = scan.getScanAngleIncrement() * i * DEG2RAD;//TODO CHECK IF DEG2RAD needed
				if(scan.getDistance(i) < scan.getMaxRange() - 0.001){
					double partX=particle->getX();
					double partY=particle->getY();
					int partYaw= particle->getYaw();
					//TODO CHECK ACCURACY WITH A TEST


					double obsX = partX + scan.getDistance(i) * cos(partYaw * DEG2RAD +  angle  - 180 * DEG2RAD);
					double obsY = partY + scan.getDistance(i) * sin(partYaw * DEG2RAD + angle  - 180 * DEG2RAD);

					int pixelsX= map->xToCol(obsX) ;
					int pixelsY = map->yToRow(obsY) ;

					/*int pixelsX = obsX / map->getOg().getResolution() + map->getOg().getWidth() /2;
					int pixelsY = obsY / map->getOg().getResolution() + map->getOg().getHeight() /2;*/


					if (map->getOg()->getCell(pixelsX,pixelsY) == CELL_OCCUPIED){
						hits++;


					}
					else{
						misses++;
					}
				}
			}

			return (float)hits/(hits+misses);	}

	void LocalizationManager::paintParticleVector()
	{

		for(int i=0;i<this->particleVector.size();i++)
		{

			this->map->paintOneParticle(this->particleVector[i]);
		}
	}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}

