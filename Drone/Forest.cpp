
#include "Forest.h"
#include "Node.h"
Forest::Forest(Tree<Drone> &tree1,int xminlim,int xmaxlim,int yminlim,int ymaxlim,int xgoal,int ygoal):Xminlim(xminlim),Yminlim(yminlim),Xmaxlim(xmaxlim),Ymaxlim(ymaxlim),goalX(xgoal),goalY(ygoal),bestX(0),bestY(0){
		squares=new Square*[xmaxlim-xminlim];
		for(int i=0;i<xmaxlim-xminlim;i++){
			squares[i]=new Square[ymaxlim-yminlim];
		}
		howmanyplanes=0;
		tree=&tree1;
}
Forest::~Forest(){
	delete tree;
	for(int i=0;i<Xmaxlim-Xminlim;i++){
		delete []squares[i];
	}
	delete []squares;
}
int Forest::getXmaxlim() const {
	return Xmaxlim;
}

int Forest::getXminlim() const {
	return Xminlim;
}

int Forest::getYmaxlim() const {
	return Ymaxlim;
}

int Forest::getYminlim() const {
	return Yminlim;
}
Drone* Forest::operator[](int w){
	if(tree->searchByInt(w)!=0){
		return tree->searchByInt(w)->getData();
	}
	else{
		return 0;
	}
}
void Forest::minSquares(int a) {
	squares[(int)tree->searchByInt(a)->getData()->getX()][(int)tree->searchByInt(a)->getData()->getY()]--;
}
void Forest::maxSquares(int a) {
	squares[(int)tree->searchByInt(a)->getData()->getX()][(int)tree->searchByInt(a)->getData()->getY()]++;
}

