/*
 * SingleRotor.cpp
 *
 *  Created on: Jan 1, 2021
 *      Author: win 10
 */

#include "SingleRotor.h"
using namespace std;
void SingleRotor::nextMove(Forest& forest){
	Drone::nextMoveALL(forest);
}
void SingleRotor::nextSpeed(Forest& forest){
	Drone::nextSpeedALL(a,b,ye,forest);
}
Drone& SingleRotor::operator=(const Drone& rhs){
	if(&rhs==this){
		return *this;
	}
	return operator=(dynamic_cast<const SingleRotor&>(rhs));
}
SingleRotor& SingleRotor::operator=(const SingleRotor& rhs){
	if(&rhs==this){
		return *this;
	}
	Drone::operator=(rhs);
	a=rhs.getA();
	b=rhs.getB();
	ye=rhs.getYe();
	return *this;
}
double SingleRotor::getA() const {
		return a;
	}

double SingleRotor::getB() const {
	return b;
}

double SingleRotor::getYe() const {
	return ye;
}
string SingleRotor::getName()const{return "SingleRotor";}
