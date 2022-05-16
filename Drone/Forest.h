#ifndef FOREST_H_
#define FOREST_H_
#include <cstdlib>
#include <iostream>
using namespace std;
#include "Tree.h"
#include "Square.h"
#include "Drone.h"
class Forest {
private:
	int Xminlim,Yminlim,Xmaxlim,Ymaxlim;
	Square **squares;
	Tree<Drone> *tree;
	int howmanyplanes;
	double goalX;
	double goalY;
	double bestX;
	double bestY;
public:
	Forest(Tree<Drone> &tree1,int xminlim,int xmaxlim,int yminlim,int ymaxlim,int xgoal,int ygoal);
	~Forest();
	Drone* operator[](int w);
	double getgoalX()const{return goalX;}
	double getgoalY()const{return goalY;}
	double getbestX()const{return bestX;}
	double getbestY()const{return bestY;}
	void setHowManyPlanes(int x){howmanyplanes=x;}
	Square& getSquareGoal()const{return squares[(int)goalX][(int)goalY];}
	void setbestX(double x){bestX=x;}
	void setbestY(double x){bestY=x;}
	int getXmaxlim() const ;
	int getXminlim() const;
	int getYmaxlim() const;
	int getYminlim() const;
	const int operator()(int i, int j)const { return squares[i][j].getPlanes(); }
	const int howmany()const { return howmanyplanes; }
	void add(Drone& drone){tree->insert(&drone);}
	void add(Drone* drone){tree->insert(drone);}
	void minSquares(int a);
	void maxSquares(int a);
};
#endif /* FOREST_H_ */
