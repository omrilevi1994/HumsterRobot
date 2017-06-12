/*
 * Map.cpp
 *
 *  Created on: Jan 24, 2017
 *      Author: user
 */

#include "ColoredMap.h"

ColoredMap::ColoredMap(OccupancyGrid* og) {
	this->og=og;
	this->cols=og->getWidth();
	this->rows=og->getHeight();
	this->resolution=og->getResolution();
	this->mat=new cv::Mat(this->rows,this->cols,CV_8UC3,cv::Scalar(0,0,0));
	cv::namedWindow("View");
}


int ColoredMap::xToCol(double x)
{
	return (x/this->resolution);
}

int ColoredMap::yToRow(double y){
	return ((-1)*y/this->resolution);

}

double ColoredMap::colTox(int col)
{
	return (double)(col*this->resolution);
}


double ColoredMap::rowToy(int row)
{
	return (double)((-1)*row*this->resolution);
}

void ColoredMap::paintBasicMap()
{

	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++) {

			if (this->og->getCell(i, j) == CELL_FREE)
			{
				mat->at<cv::Vec3b>(i, j)[0] = 255;
				mat->at<cv::Vec3b>(i, j)[1] = 255;
				mat->at<cv::Vec3b>(i, j)[2] = 255;
			}

			else if (this->og->getCell(i, j) == CELL_OCCUPIED)
			{
				mat->at<cv::Vec3b>(i, j)[0] = 0;
				mat->at<cv::Vec3b>(i, j)[1] = 0;
				mat->at<cv::Vec3b>(i, j)[2] = 0;
			}

			else
			{
				mat->at<cv::Vec3b>(i, j)[0] = 128;
				mat->at<cv::Vec3b>(i, j)[1] = 128;
				mat->at<cv::Vec3b>(i, j)[2] = 128;
			}

		}

	cv::imshow("View",*(this->mat));
	cv::waitKey(1);
}


void ColoredMap::paintOneParticle(Particle* particle)
{
	int col=this->xToCol(particle->getX());
	int row=this->yToRow(particle->getY());

try{
	if(this->og->getCell(col,row)==CELL_FREE)
	{
		/*if(particle->getBel()>0.6)
		{

		}
		else
		{

		}*/
		this->paintLocationRed(col+1,row);
		this->paintLocationRed(col-1,row);

		this->paintLocationRed(col,row+1);
		this->paintLocationRed(col,row-1);

		this->paintLocationRed(col+1,row+1);
		this->paintLocationRed(col-1,row-1);

		this->paintLocationRed(col+1,row-1);
		this->paintLocationRed(col-1,row+1);

		cv::imshow("View",*(this->mat));
			cv::waitKey(1);
	}

} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}
}


void ColoredMap::paintLocationRed(int col,int row)
{
	this->mat->at<cv::Vec3b>(col,row)[0]=0;
	this->mat->at<cv::Vec3b>(col,row)[1]=0;
	this->mat->at<cv::Vec3b>(col,row)[2]=255;
}

void ColoredMap::paintLocationBlue(int col,int row)
{
	this->mat->at<cv::Vec3b>(col,row)[0]=255;
		this->mat->at<cv::Vec3b>(col,row)[1]=0;
		this->mat->at<cv::Vec3b>(col,row)[2]=0;


}


ColoredMap::~ColoredMap() {

}

