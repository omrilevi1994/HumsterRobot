/*
 * ConfigurationManager.h
 *
 *  Created on: 03/06/2016
 *      Author: Eylam Milner & Lucas Aids
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

// Read configuration
#define LINE_TO_READ 			100
#define PROPERITES_NUMBER 		10

// Obstacles awareness
#define LASER_RIGHT_VALUE 		250
#define LASER_LEFT_VALUE		250
#define LASER_STRAIGHT_VALUE	60
#define LASER					111
#define MINIUM_ALLOWED_DISTANCE 0.25
#define SPEED					0.1
#define DEGREE_INDEXE			2.4667
#define YAW_DIFFERNCE			2
#define RIGHT_SPEED				-0.2
#define LEFT_SPEED				0.2
#define ACTION_COUNT			2

#include <string>
#include "Map.h"

using namespace std;

class ConfigurationManager
{
	public:

		// Configuration constructor and destructor
		ConfigurationManager(const char* configurationPath);
		virtual ~ConfigurationManager();

		//char fileInfo[PROPERITES_NUMBER][LINE_TO_READ];
		string map_path;
		//int start_x;
		//int start_y;
		//int yaw;
		//int target_x;
		//int target_y;
		//double robot_length;
		//double robot_width;
		//double map_resolution;
		//double grid_resolution;
		//char* configurationPath;

		// Luac
		string	mapFile;
		Point 	robotStart;
		double 	robotStartYAW;
		Point 	goal;
		double 	robotHeight;
		double 	robotWidth;
		double 	mapResolutionCM;
		double 	gridResolutionCM;

		void ReadConfigurationData(const char* configurationPath);
		void ReadConfigFile(const char* configPath);
		void ReadParametrsFile(const char* configPath);
		void Read(const char* configPath);
		void convertSizeToCM();
};

#endif /* CONFIGURATIONMANAGER_H_ */
