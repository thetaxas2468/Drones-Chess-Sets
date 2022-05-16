

#include <iostream>
using namespace std;
#include <iomanip>
//T object has > oberator that give us his place and ==
#include "Tree.h"
#include "Drone.h"
#include "SingleRotor.h"
#include "Hybrid.h"
#include "MultiRotor.h"
#include "FixedWing.h"
#include "Forest.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <math.h>
#include <ctime>
#include <fstream>
int main(int argc, char* argv[]) {
//	Tree<Drone>* tr=new Tree<Drone>();
//	Drone *a=new FixedWing(1,1,1,1,0);
//	Drone *b=new FixedWing(1,1,1,1,1);
//	Drone *c=new FixedWing(1,1,1,1,2);
//	Drone *d=new FixedWing(1,1,1,1,3);
//	Drone *e=new FixedWing(1,1,1,1,4);
//	tr->insert(a);tr->insert(b);tr->insert(c);tr->insert(d);tr->insert(e);
//	tr->print();
//	tr->remove(*e);
//	cout<<"4 expected"<<endl;
//	tr->print();
//	return 0;
	//check if arguments 4 or 5
	if (argc != 4 && argc!=5) {
		cerr << "Error; invalid input" << endl;
		exit(1);
	}
	int random;
	//if 5 then we have extra arg for srand
	if(argc==5){
		random=atof(argv[4]);
		srand(random);
	}
	else{
		srand(time(NULL));
	}
	//opening file using streams
	ifstream file1(argv[1]);
	ifstream file2(argv[2]);
	ofstream file3(argv[3]);
	if (!file1 || !file2 || !file3) {
		cerr << "Error; invalid input" << endl;
		exit(1);
	}
	//checking if it is correct if not not vaild
	string line;
	getline(file1, line);
	int spaces = 0;
	for (unsigned int i = 0; i < line.size(); i++) {
		if (isspace(line[i])) {
			spaces++;
		}
	}
	if (spaces != 3) {
		cerr << "Error; invalid input" << endl;
		exit(1);
	}
	//getting information and checking if they are valid or not and then initalize them like forest size width height,..... from config
	stringstream str(line);
	string forestsize;
	string sizes[4];
	int index = 0;
	while (str >> forestsize) {
		sizes[index++] = forestsize;
	}
	for (unsigned int i = 0; i < sizes[0].size(); i++) {
		if (!isdigit(sizes[0].c_str()[i])) {
			cerr << "Error; invalid input" << endl;
			exit(1);
		}
	}
	for (unsigned int i = 0; i < sizes[1].size(); i++) {
		if (!isdigit(sizes[1].c_str()[i])) {
			cerr << "Error; invalid input" << endl;
			exit(1);
		}
	}
	for (unsigned int i = 0; i < sizes[2].size(); i++) {
		if (!isdigit(sizes[2].c_str()[i])) {
			cerr << "Error; invalid input" << endl;
			exit(1);
		}
	}
	for (unsigned int i = 0; i < sizes[3].size(); i++) {
		if (!isdigit(sizes[3].c_str()[i])) {
			cerr << "Error; invalid input" << endl;
			exit(1);
		}
	}
	//Border limits
	double Xminlim = atof(sizes[0].c_str());
	double Yminlim = atof(sizes[1].c_str());
	double Xmaxlim = atof(sizes[2].c_str());
	double Ymaxlim = atof(sizes[3].c_str());
	index = 0;
	//valid test
	getline(file1, line);
	for (unsigned int i = 0; i < line.size(); i++) {
		if (isspace(line[i])) {
			index++;
		}
	}
	if (index != 1) {
		cerr << "Error; invalid input" << endl;
		exit(1);
	}
	stringstream line2(line);
	string STRgoalx;
	string STRgoaly;
	line2 >> STRgoalx;
	line2 >> STRgoaly;
	//getteting what is the goal x and goal y
	for (unsigned int i = 0; i < STRgoalx.size(); i++) {
		if (STRgoalx[i] == '.' || isdigit(STRgoalx.c_str()[i])) {
			continue;
		}
		else {
			cerr << "Error; invalid input" << endl;
			exit(1);
		}
	}
	for (unsigned int i = 0; i < STRgoaly.size(); i++) {
		if (STRgoaly[i] == '.' || isdigit(STRgoaly.c_str()[i])) {
			continue;
		}
		else {
			cerr << "Error; invalid input" << endl;
			exit(1);
		}
	}
	double goalx = atof(STRgoalx.c_str());
	double goaly = atof(STRgoaly.c_str());
	getline(file1, line);
	for (unsigned int i = 0; i < line.size(); i++) {
		if (isdigit(line.c_str()[i])) {
			continue;
		}
		else {
			cerr << "Error; invalid input" << endl;
			exit(1);
		}
	}
	//how many iteration and creating our BST and then creating our forest that we will work in
	int iteration = atof(line.c_str());
	Tree<Drone> *tree=new Tree<Drone>;
	Forest forest(*tree, Xminlim, Xmaxlim, Yminlim, Ymaxlim, goalx, goaly);
	getline(file2,line);
	for(unsigned int i=0;i<line.size();i++){
		if(!isdigit(line[i])){
			cerr << "Error; invalid input" << endl;
			exit(1);
		}
	}
	int howmanyplanes=atof(line.c_str());
	forest.setHowManyPlanes(howmanyplanes);
	string spare;
	double x;
	double y;
	double speedx;
	double speedy;
	int whichone=0;
	int BinaryCounter=0;
	//initalize everything in the config data by its correct type like Hybrid FixedWings ... by its goal and location and speed and to check by its char
	for(int i=0;i<howmanyplanes;i++){
		getline(file2,line);
		int spacecounter=0;
		for(unsigned int i=0;i<line.size();i++){
			if(isspace(line[i])){
				spacecounter++;
			}
		}
		if(spacecounter!=4){
			cerr << "Error; invalid input" << endl;
			exit(1);
		}
		stringstream s(line);
		char type;
		s>>type;
		if(type=='S'){
			while(s>>spare){
				int dotcounter=0;
				if(!isdigit(spare[0])&&spare[0]!='-'){
					cerr << "Error; invalid input" << endl;
					exit(1);
				}
				for(unsigned int i=0;i<spare.size();i++){
					if(isdigit(spare[i])){
						continue;
					}
					else if(spare[i]=='.'){
						dotcounter++;
					}
					else{
						cerr << "Error; invalid input" << endl;
						exit(1);
					}
				}
				if(dotcounter>1){
					cerr << "Error; invalid input" << endl;
					exit(1);
				}
				if(whichone==0){
					x=atof(spare.c_str());
					whichone++;
				}
				else if(whichone==1){
					y=atof(spare.c_str());
					whichone++;
				}
				else if(whichone==2){
					speedx=atof(spare.c_str());
					whichone++;
				}
				else{
					speedy=atof(spare.c_str());
					whichone++;
					whichone=0;
				}
			}
			Drone *s=new SingleRotor(x,y,speedx,speedy,BinaryCounter++);
			forest.add(*s);
		}
		else if(type=='M'){
			while(s>>spare){
				int dotcounter=0;
				if(!isdigit(spare[0])&&spare[0]!='-'){
					cerr << "Error; invalid input" << endl;
					exit(1);
				}
				for(unsigned int i=0;i<spare.size();i++){
					if(isdigit(spare[i])){
						continue;
					}
					else if(spare[i]=='.'){
						dotcounter++;
					}
					else{
						cerr << "Error; invalid input" << endl;
						exit(1);
					}
				}
				if(dotcounter>1){
					cerr << "Error; invalid input" << endl;
					exit(1);
				}
				if(whichone==0){
					x=atof(spare.c_str());
					whichone++;
				}
				else if(whichone==1){
					y=atof(spare.c_str());
					whichone++;
				}
				else if(whichone==2){
					speedx=atof(spare.c_str());
					whichone++;
				}
				else{
					speedy=atof(spare.c_str());
					whichone++;
					whichone=0;
				}
			}
			Drone *s=new MultiRotor(x,y,speedx,speedy,BinaryCounter++);
			forest.add(*s);
		}
		else if(type=='W'){
			while(s>>spare){
				int dotcounter=0;
				if(!isdigit(spare[0])&&spare[0]!='-'){
					cerr << "Error; invalid input" << endl;
					exit(1);
				}
				for(unsigned int i=0;i<spare.size();i++){
					if(isdigit(spare[i])){
						continue;
					}
					else if(spare[i]=='.'){
						dotcounter++;
					}
					else{
						cerr << "Error; invalid input" << endl;
						exit(1);
					}
				}
				if(dotcounter>1){
					cerr << "Error; invalid input" << endl;
					exit(1);
				}
				if(whichone==0){
					x=atof(spare.c_str());
					whichone++;
				}
				else if(whichone==1){
					y=atof(spare.c_str());
					whichone++;
				}
				else if(whichone==2){
					speedx=atof(spare.c_str());
					whichone++;
				}
				else{
					speedy=atof(spare.c_str());
					whichone++;
					whichone=0;
				}
			}
			Drone *s=new FixedWing(x,y,speedx,speedy,BinaryCounter++);
			forest.add(*s);
		}
		else if(type=='H'){
			while(s>>spare){
				int dotcounter=0;
				if(!isdigit(spare[0])&&spare[0]!='-'){
					cerr << "Error; invalid input" << endl;
					exit(1);
				}
				for(unsigned int i=0;i<spare.size();i++){
					if(isdigit(spare[i])){
						continue;
					}
					else if(spare[i]=='.'){
						dotcounter++;
					}
					else{
						cerr << "Error; invalid input" << endl;
						exit(1);
					}
				}
				if(dotcounter>1){
					cerr << "Error; invalid input" << endl;
					exit(1);
				}
				if(whichone==0){
					x=atof(spare.c_str());
					whichone++;
				}
				else if(whichone==1){
					y=atof(spare.c_str());
					whichone++;
				}
				else if(whichone==2){
					speedx=atof(spare.c_str());
					whichone++;
				}
				else{
					speedy=atof(spare.c_str());
					whichone++;
					whichone=0;
				}
			}
			Drone *s=new Hybrid(x,y,speedx,speedy,BinaryCounter++);
			forest.add(*s);
		}
		else{
			cerr << "Error; invalid input" << endl;
			exit(1);
		}
		forest.maxSquares(BinaryCounter-1);
	}
	//checking Drone if they are in the range of the forest
	for(int i=0;i<howmanyplanes;i++){
		forest[i]->DoubleCheck(forest);
	}
	int cnt=0;
//	int sb=0;
	bool stop=false;
	if (forest.getSquareGoal().getPlanes()> 0) {//if we found where the is the point we put planes places into the file
		stop=true;
	}
	if(stop==false){
		for (int i = 1; i < iteration+1; i++) {
			cnt=i;
			if (forest.getSquareGoal().getPlanes()> 0) {//if we found where the is the point we put planes places into the file
			//	stop=true;
				break ;
			}
			//here to get at every time the best of the planes
			forest.setbestX(forest[0]->getX());
			forest.setbestY(forest[0]->getY());
			for(int w=1;w<howmanyplanes;w++){
				if(sqrt((pow(forest[w]->getX()-forest.getgoalX(),2)+pow(forest[w]->getY()-forest.getgoalY(),2)))<sqrt((pow(forest.getbestX()-forest.getgoalX(),2)+pow(forest.getbestY()-forest.getgoalY(),2)))){
					forest.setbestX(forest[w]->getX());
					forest.setbestY(forest[w]->getY());
				}
			}
			//here we make the planes move and then we get their new speed for the next move
			for(int w=0;w<howmanyplanes;w++){
				forest.minSquares(w);
				//planes number w we takes its next move and after that we take the next speed for the next move
			//	cout<<"Name: "<<forest[0]->getName()<<",X: "<<forest[0]->getX()<<" ,Y: "<<forest[0]->getY()<<" ,speedX: "<<forest[0]->getspeedX()<<" ,speedY: "<<forest[0]->getspeedY()<<endl;
				forest[w]->nextMove(forest);
				forest[w]->nextSpeed(forest);
				forest.maxSquares(w);
			}
//			sb++;
//			if(sb==4){
//				return 0;
//			}
		}
	}
	file3 << cnt;
	file3 << endl;
	//formatted printing into file 3
	for (int w = 0; w < howmanyplanes; w++) {
		setprecision(2);
		file3 << forest[w]->getX();
		file3<< " " ;
		file3<<forest[w]->getY()<<endl;
	}
//	for(int i=0;i<forest.getXmaxlim()-forest.getXminlim();i++){
//		for(int j=0;j<forest.getYmaxlim()-forest.getYminlim();j++){
//			cout<<forest(i,j)<<" ";
//		}
//		cout<<endl;
//	}
	cout<<"Done";
	return 0;
	//	Drone *y=new SingleRotor(1,551,5,5,0);
	//	Drone *w=new FixedWing(1,2,5,5,1);
	//	Drone *q=new Hybrid(1,1,5,5,3);
	//	Drone *f=new MultiRotor(1,55,5,5,4);
	//	forest.add(*y);
	//	forest.add(*w);
	//	forest.add(*q);
	//	forest.add(*q);
	//	forest.add(*f);



	//	Drone *y=new SingleRotor(1,5,5,5,0);
	//	Drone *w=new FixedWing(1,2,5,5,1);
	//	Drone *q=new Hybrid(1,1,5,5,1);
	//	Drone *f=new MultiRotor(1,55,5,5,2);
	//	tree->insert(y);
	//	tree->insert(w);
	////	tree->remove(*y);
	//	tree->print();
////	x.remove(*w);
////	*x.search(1)->getData();
//	x.print();
//	cout<<"w"<<endl;
//	Tree<int>x;
//	int *a1=new int(8);
//	int *a2=new int(9);
//	x.insert(a1);
//	x.insert(a2);
//	x.print();
//	x.remove(*a2);
//	x.print();
//	delete w;
//	w=new Hybrid(1,1,5,5,0);
//	x.insert(w);
//	x.print();

}
