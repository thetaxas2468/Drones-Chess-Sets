/*
 * Drone.cpp
 *
 *  Created on: Jan 1, 2021
 *      Author: win 10
 */
#include "Drone.h"
#include "Forest.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
Drone::Drone(double x,double y,double speedx,double speedy,int when):x(x),y(y),speedX(speedx),speedY(speedy),when(when){
	personalX=x;
	personalY=y;
	lastX=x;
	lastY=y;
}
void Drone::DoubleCheck(Forest& forest){
	if(x>forest.getXmaxlim()||x<forest.getXminlim()||y<forest.getYminlim()||y>forest.getYmaxlim()){
		cerr << "Error; invalid input" << endl;
		exit(1);
	}
	return;
}
bool operator==(const Drone& drone,const Drone& drone2){
	return (drone2.when==drone.when)?1:0;
}
bool operator<(const Drone& drone,const Drone& drone2){
	return drone.when<drone2.when;
}
bool operator>(const Drone& drone,const Drone& drone2){
	return drone.when>drone2.when;
}
bool operator>(const Drone& drone,const int& number){
	return drone.when>number;
}
bool operator<(const Drone& drone,const int& number){
	return drone.when<number;
}
bool operator==(const Drone& drone,const int& number){
	return drone.when==number;
}
ostream& operator<<(ostream& out,const Drone& drone2){
	out<<drone2.getName()<<" "<<drone2.getX()<<" "<<drone2.getY()<<endl;
	return out;
}
Drone::~Drone() {
}
void Drone::nextMoveALL(Forest& forest){
	this->x = x+speedX;
	this->y = y+speedY;
	if (x > forest.getXmaxlim()) {
		this->x = forest.getXmaxlim();
	}
	if (y > forest.getYmaxlim()) {
		this->y = forest.getYmaxlim();
	}
	if (x < forest.getXminlim()) {
		this->x = forest.getXminlim();
	}
	if (y < forest.getYminlim()) {
		this->y = forest.getYminlim();
	}
	double a1=forest.getgoalX()-x;
	double a2=forest.getgoalY()-y;
	double a3=forest.getgoalX()-personalX;
	double a4=forest.getgoalY()-personalY;
	if (sqrt((a1*a1)+(a2*a2))<sqrt((a3*a3)+(a4*a4))) {
		this->personalX = x;
		this->personalY = y;
	}
}
void Drone::nextSpeedALL(double a, double b, double ye,Forest& forest) {
	double r1 = (static_cast<double>(rand()) / (static_cast<double>(RAND_MAX)));
	double r2 = (static_cast<double>(rand()) / (static_cast<double>(RAND_MAX)));
	double q1 = ((a * speedX) + (b*r1* (personalX - lastX)) + (ye*r2* (forest.getbestX() - lastX)));
	double q2 = ((a * speedY) +  (b*r1* (personalY - lastY)) + (ye*r2* (forest.getbestY() - lastY)));
	lastX=x;
	lastY=y;
//	cout<<"Q1:"<<forest.getbestX() - x<<endl;
//	cout<<"Q2:"<<forest.getbestY() - y<<endl;
	speedX=q1;
	speedY=q2;
}
int Drone::getWhen()const{return when;}
double Drone::getX()const { return x; }
double Drone::getY() const{ return y; }
double Drone::getspeedX()const{return speedX;}
double Drone::getspeedY()const{return speedY;}
double Drone::getpersonalX()const{return personalX;}
double Drone::getpersonalY()const{return personalY;}
void Drone::setPersonal(double a,double b){personalX=a;personalY=b;}
void Drone::nextMove(Forest& forest){}
void Drone::nextSpeed(Forest& forest){}
Drone& Drone::operator=(const Drone& rhs){
	x=rhs.getX();
	y=rhs.getY();
	speedX=rhs.getspeedX();
	speedY=rhs.getspeedY();
	personalX=rhs.getpersonalX();
	personalY=rhs.getpersonalY();
	return *this;
}
