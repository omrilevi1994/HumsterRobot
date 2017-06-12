/*
 * Location.h
 *
 */

#ifndef LOCATION_H_
#define LOCATION_H_

class Location {
private:
	int i,j;
	double x,y;
	int yaw;

public:
	Location(double x,double y,int yaw);
	Location();
	virtual ~Location();
	Location(Location* otherLocation);
	void changeLocation(double x,double y,int yaw);
	double getX() const {
		return x;
	}

	void setX(double x) {
		this->x = x;
	}

	double getY() const {
		return y;
	}

	void setY(double y) {
		this->y = y;
	}

	int getYaw() const {
		return yaw;
	}

	void setYaw(int yaw) {
		this->yaw = yaw;
	}

	void print();

	int getI() const {
		return i;
	}

	void setI(int i) {
		this->i = i;
	}

	int getJ() const {
		return j;
	}

	void setJ(int j) {
		this->j = j;
	}
};

#endif /* LOCATION_H_ */
