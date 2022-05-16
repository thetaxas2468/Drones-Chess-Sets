/*
 * FixedWing.cpp
 *
 *  Created on: Jan 1, 2021
 *      Author: win 10
 */

#include "FixedWing.h"
using namespace std;
void FixedWing::nextMove(Forest& forest){
	Drone::nextMoveALL(forest);
}
void FixedWing::nextSpeed(Forest& forest){
	Drone::nextSpeedALL(a,b,ye,forest);
}
Drone& FixedWing::operator=(const Drone& rhs){
	if(&rhs==this){
		return *this;
	}
	return operator=(dynamic_cast<const FixedWing&>(rhs));
}
FixedWing& FixedWing::operator=(const FixedWing& rhs){
	if(&rhs==this){
		return *this;
	}
	Drone::operator=(rhs);
	a=rhs.getA();
	b=rhs.getB();
	ye=rhs.getYe();
	return *this;
}

string FixedWing::getName()const{return "FixedWing";}
double FixedWing::getA() const {
		return a;
	}

double FixedWing::getB() const {
	return b;
}

double FixedWing::getYe() const {
	return ye;
}
