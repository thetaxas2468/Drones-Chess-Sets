/*
 * MultiRotor.h
 *
 *  Created on: Jan 1, 2021
 *      Author: win 10
 */

#ifndef MULTIROTOR_H_
#define MULTIROTOR_H_
#include "Drone.h"
class MultiRotor :public Drone{
private:
	double a,b,ye;
public:
	MultiRotor(double x,double y,double speedx,double speedy,int when):Drone(x,y,speedx,speedy,when),a(0.05),b(0.1),ye(0){}
	virtual ~MultiRotor(){}
	virtual std::string getName()const;
	virtual void nextMove(Forest& forest);
	virtual void nextSpeed(Forest& forest);
	virtual Drone& operator=(const Drone& rhs);
	MultiRotor& operator=(const MultiRotor& rhs);

	double getA() const ;

	double getB() const;

	double getYe() const ;
};

#endif /* MULTIROTOR_H_ */
