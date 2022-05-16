/*
 * SingleRotor.h
 *
 *  Created on: Jan 1, 2021
 *      Author: win 10
 */

#ifndef SINGLEROTOR_H_
#define SINGLEROTOR_H_
#include "Drone.h"
class SingleRotor :virtual public Drone{
private:
	double a,b,ye;
public:
	SingleRotor(double x,double y,double speedx,double speedy,int when):Drone(x,y,speedx,speedy,when),a(0.01),b(-0.1),ye(-0.25){}
	~SingleRotor(){}
	virtual std::string getName()const;
	virtual void nextMove(Forest& forest);
	virtual void nextSpeed(Forest& forest);
	virtual Drone& operator=(const Drone& rhs);
	SingleRotor& operator=(const SingleRotor& rhs);

	double getA() const ;
	double getB() const ;

	double getYe() const ;
};

#endif /* SINGLEROTOR_H_ */
