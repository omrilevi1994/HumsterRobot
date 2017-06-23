/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jun 3, 2016
 *      Author: colman
 */

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager(const char* configurationPath)
{

	// Open parameters file
	ifstream parameters;
	parameters.open("parameters.txt");

	if (parameters.is_open())
	{
		string line;
		string lineName;

		// Get Map File - line contains map: path
		getline(parameters,line);
		std::istringstream mapLine(line);
		mapLine >> lineName >> mapFile;

		// Get Robot starting position - line contains startLocation: x y yaw
		getline(parameters,line);
		istringstream startLocationLine(line);
		startLocationLine >> lineName >> robotStart.x >> robotStart.y >> robotStartYAW;

		// Get Goal - line contains goal: x y
		getline(parameters,line);
		istringstream goalLine(line);
		goalLine >> lineName >> goal.x >> goal.y;

		// Get Robot Size - line contains robotSize: height width
		getline(parameters,line);
		istringstream sizeLine(line);
		sizeLine >> lineName >> robotHeight >> robotWidth;

		// Get Map resolution in CM - line contains MapResolutionCM: resolution
		getline(parameters,line);
		istringstream mapResolutionLine(line);
		mapResolutionLine >> lineName >> mapResolutionCM;

		// Get Grid resolution in CM - line contains GridResolutionCM: resolution
		getline(parameters,line);
		istringstream gridResolutionLine(line);
		gridResolutionLine >> lineName >> gridResolutionCM;

		parameters.close();
	}
	else
	{
		cout << "Unable to open file";
	}
}

ConfigurationManager::~ConfigurationManager()
{
	// TODO Auto-generated destructor stub
}
