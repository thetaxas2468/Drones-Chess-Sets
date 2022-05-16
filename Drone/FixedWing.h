/*
 * FixedWing.h
 *
 *  Created on: Jan 1, 2021
 *      Author: win 10
 */

#ifndef FIXEDWING_H_
#define FIXEDWING_H_
#include "Drone.h"
class FixedWing :virtual public Drone{
private:
	double a,b,ye;
public:
	FixedWing(double x,double y,double speedx,double speedy,int when):Drone(x,y,speedx,speedy,when),a(0.25),b(1),ye(1){}
	virtual ~FixedWing(){}
	virtual std::string getName()const;
	virtual void nextMove(Forest& forest);
	virtual void nextSpeed(Forest& forest);
	virtual Drone& operator=(const Drone& rhs);
	FixedWing& operator=(const FixedWing& rhs);
	double getA() const ;
	double getB() const ;
	double getYe() const ;
};

#endif /* FIXEDWING_H_ */
