/*
 * Hybrid.h
 *
 *  Created on: Jan 1, 2021
 *      Author: win 10
 */

#ifndef HYBRID_H_
#define HYBRID_H_
#include "SingleRotor.h"
#include "FixedWing.h"
class Hybrid :public SingleRotor,public FixedWing{
private:
	double a,b,ye;
public:
	Hybrid(double x,double y,double speedx,double speedy,int when):Drone(x,y,speedx,speedy,when),SingleRotor(x,y,speedx,speedy,when),FixedWing(x,y,speedx,speedy,when),a(0.01),b(-0.1),ye(-0.25){}
	virtual ~Hybrid(){}
	virtual std::string getName()const;
	virtual void nextMove(Forest& forest);
	virtual void nextSpeed(Forest& forest);
	virtual Drone& operator=(const Drone& rhs);
	Hybrid& operator=(const Hybrid& rhs);
	double getA() const;
	double getB() const;
	double getYe() const ;
};

#endif /* HYBRID_H_ */
