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

	void setX(double x1) {
		x = x1;
	}

	double getY() const {
		return y;
	}

	void setY(double y1) {
		y = y1;
	}

	int getYaw() const {
		return yaw;
	}

	void setYaw(int yaw1) {
		yaw = yaw1;
	}

	void print();

	int getI() const {
		return i;
	}

	void setI(int i1) {
		i = i1;
	}

	int getJ() const {
		return j;
	}

	void setJ(int j1) {
		j = j1;
	}
};

#endif /* LOCATION_H_ */
