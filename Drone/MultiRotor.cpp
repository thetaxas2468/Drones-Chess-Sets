/*
 * MultiRotor.cpp
 *
 *  Created on: Jan 1, 2021
 *      Author: win 10
 */

#include "MultiRotor.h"
using namespace std;
void MultiRotor::nextMove(Forest& forest){
	Drone::nextMoveALL(forest);
}
void MultiRotor::nextSpeed(Forest& forest){
	Drone::nextSpeedALL(a,b,ye,forest);
}
Drone& MultiRotor::operator=(const Drone& rhs){
	if(&rhs==this){
		return *this;
	}
	return operator=(dynamic_cast<const MultiRotor&>(rhs));
}
MultiRotor& MultiRotor::operator=(const MultiRotor& rhs){
	if(&rhs==this){
		return *this;
	}
	Drone::operator=(rhs);
	a=rhs.getA();
	b=rhs.getB();
	ye=rhs.getYe();
	return *this;
}
double MultiRotor::getA() const {
		return a;
	}

double MultiRotor::getB() const {
	return b;
}

double MultiRotor::getYe() const {
	return ye;
}
string MultiRotor::getName()const{return "MultiRotor";}
