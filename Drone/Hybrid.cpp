/*
 * Hybrid.cpp
 *
 *  Created on: Jan 1, 2021
 *      Author: win 10
 */

#include "Hybrid.h"
using namespace std;
void Hybrid::nextMove(Forest& forest){
	Drone::nextMoveALL(forest);
}
void Hybrid::nextSpeed(Forest& forest){
	Drone::nextSpeedALL(a,b,ye,forest);
}
Drone& Hybrid::operator=(const Drone& rhs){
	if(&rhs==this){
		return *this;
	}
	return operator=(dynamic_cast<const Hybrid&>(rhs));
}
Hybrid& Hybrid::operator=(const Hybrid& rhs){
	if(&rhs==this){
		return *this;
	}
	Drone::operator=(rhs);
	a=rhs.getA();
	b=rhs.getB();
	ye=rhs.getYe();
	return *this;
}
double Hybrid::getA() const {
		return a;
	}

double Hybrid::getB() const {
	return b;
}

double Hybrid::getYe() const {
	return ye;
}
string Hybrid::getName()const{return "Hybrid";}
