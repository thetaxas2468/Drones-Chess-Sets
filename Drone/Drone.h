/*
 * Drone.h
 *
 *  Created on: Jan 1, 2021
 *      Author: win 10
 */

#ifndef DRONE_H_
#define DRONE_H_
#include <iostream>
class Forest;
//here we have drone the father of all other drones that is abstract class that we cant make objects from it and it has functionw
//that not overried in the sons and some not like next move and next speed that all have the same function but with different parameters
//so like that we have not muhc code for the same function
class Drone {
protected:
	double x,y,speedX,speedY,personalX,personalY,lastX,lastY;
	int when;
	void nextSpeedALL(double a,double b,double ye,Forest& forest);
	void nextMoveALL(Forest& forest);
public:
	Drone(double x,double y,double speedx,double speedy,int when);
	virtual ~Drone()=0;
	void DoubleCheck(Forest& forest);
	int getWhen()const;
	double getX()const ;
	double getY() const;
	double getspeedX()const;
	double getspeedY()const;
	double getpersonalX()const;
	double getpersonalY()const;
	void setPersonal(double a,double b);
	virtual void nextMove(Forest& forest);
	virtual void nextSpeed(Forest& forest);
	virtual std::string getName()const{return "";}
	friend bool operator<(const Drone& drone,const Drone& drone2);
	friend bool operator>(const Drone& drone,const Drone& drone2);
	friend bool operator==(const Drone& drone,const Drone& drone2);
	friend bool operator>(const Drone& drone,const int& number);
	friend bool operator<(const Drone& drone,const int& number);
	friend bool operator==(const Drone& drone,const int& number);
	friend std::ostream& operator<<(std::ostream& out,const Drone& drone);
	virtual Drone& operator=(const Drone& rhs);
};
#endif /* DRONE_H_ */
