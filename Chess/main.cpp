#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <cctype>
#include <cstring>
#include<math.h>
#include <sstream>
using namespace std;
#include "Game.h"
#include "Square.h"
#include "Piece.h"
#include "Board.h"
#include "Board.h"
#include "Game.h"
#include "Piece.h"
#include "Square.h"
//here we have few things lastxy is for enpassant to know what the last movement was because if it was 2 squares and we know enapassant is available
//then we can do the enpassant other than that if enpassant true but we cant to it because cooridenate x and y then we dont
int lastxy[2]={-1,-1};
//error to know if existed error has occured to stop us from print the board again
bool error=false;
//enpassant and player1turn to check if player1 turn or not
bool enpassant=false;
bool player1turn=true;
bool end=false;
//each player has 2 castling and we check them by variables
bool player1acastling=true;
bool player1bcastling=true;
bool player2acastling=true;
bool player2bcastling=true;
//we check if king moved so we can do castling or stop both of them
bool kingamoved=false;
bool kingbmoved=false;
bool wannaprint=true;
//int all is the whole steps that has occured
int all=1;
//checking if a movement is legal cause we cant move out from the board
bool legalmove(string x){
	if(x!="A8"&&x!="A7"&&x!="A6"&&x!="A5"&&x!="A4"&&x!="A3"&&x!="A2"&&x!="A1"
	 &&x!="B8"&&x!="B7"&&x!="B6"&&x!="B5"&&x!="B4"&&x!="B3"&&x!="B2"&&x!="B1"
	 &&x!="C8"&&x!="C7"&&x!="C6"&&x!="C5"&&x!="C4"&&x!="C3"&&x!="C2"&&x!="C1"
	 &&x!="D8"&&x!="D7"&&x!="D6"&&x!="D5"&&x!="D4"&&x!="D3"&&x!="D2"&&x!="D1"
	 &&x!="E8"&&x!="E7"&&x!="E6"&&x!="E5"&&x!="E4"&&x!="E3"&&x!="E2"&&x!="E1"
	 &&x!="F8"&&x!="F7"&&x!="F6"&&x!="F5"&&x!="F4"&&x!="F3"&&x!="F2"&&x!="F1"
	 &&x!="G8"&&x!="G7"&&x!="G6"&&x!="G5"&&x!="G4"&&x!="G3"&&x!="G2"&&x!="G1"
	 &&x!="H8"&&x!="H7"&&x!="H6"&&x!="H5"&&x!="H4"&&x!="H3"&&x!="H2"&&x!="H1"){
		return false;
	}
	return true;
}
//we check if existed name is legal cause we cant have M cause its not in the game
bool legalname(string name){
	if(name!="p"&&name!="P"&&name!="r"&&name!="R"&&name!="n"&&name!="N"&&name!="b"&&name!="B"&&name!="Q"&&name!="q"&&name!="K"&&name!="k"){
		return false;
	}
	return true;
}
//here is a long function that tell us if the king from the player1orplayer2 is in danger of dying or not
bool KingCanDie(Board *board,bool player1playing){
	//checking if it is player 1 turn or not and move to each player2 elemnts to check if they can kill player1 king or not if yes true else false
	//same thing player 2 we cehck players from player 1 to check if they can kill player 2 king
	if(player1playing==true){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				//if it is P then we can available P movents that can kill elements and we check if the enemy is king
				if(board->getBoard(i,j).getSquare()->getName()=='P'){
					if(j+1<8&&i+1<8){
						if(board->getBoard(i+1,j+1).getSquare()->getName()=='k'){
							return true;
						}
					}
					if(j-1>=0&&i+1<8){
						if(board->getBoard(i+1,j-1).getSquare()->getName()=='k'){
							return true;
						}
					}
				}
				//we check if rock can kill the king by his movements
				else if(board->getBoard(i,j).getSquare()->getName()=='R'){
					int w=j+1;
					while(w<8&&board->getBoard(i,w).getSquare()->getName()=='.'){
						w++;
					}
					if(w<8){
						if(board->getBoard(i,w).getSquare()->getName()=='k'){
							return true;
						}
					}
					w=j-1;
					while(w>=0&&board->getBoard(i,w).getSquare()->getName()=='.'){
						w--;
					}
					if(w>=0){
						if(board->getBoard(i,w).getSquare()->getName()=='k'){
							return true;
						}
					}
				    w=i+1;
					while(w<8&&board->getBoard(w,j).getSquare()->getName()=='.'){
						w++;
					}
					if(w<8){
						if(board->getBoard(w,j).getSquare()->getName()=='k'){
							return true;
						}
					}
				    w=i-1;
					while(w>=0&&board->getBoard(w,j).getSquare()->getName()=='.'){
						w--;
					}
					if(w>=0){
						if(board->getBoard(w,j).getSquare()->getName()=='k'){
							return true;
						}
					}
				}
				//same we check if Knight from player 2 can make player1 king in danger
				else if(board->getBoard(i,j).getSquare()->getName()=='N'){
					if(i-2>=0&&j+1<8){
						if(board->getBoard(i-2,j+1).getSquare()->getName()=='k'){
							return true;
						}
					}
					if(i-2>=0&&j-1>=0){
						if(board->getBoard(i-2,j-1).getSquare()->getName()=='k'){
							return true;
						}
					}
					if(i+2<8&&j+1<8){
						if(board->getBoard(i+2,j+1).getSquare()->getName()=='k'){
							return true;
						}
					}
					if(i+2<8&&j-1>=0){
						if(board->getBoard(i+2,j-1).getSquare()->getName()=='k'){
							return true;
						}
					}
					if(i-1>=0&&j+2<8){
						if(board->getBoard(i-1,j+2).getSquare()->getName()=='k'){
							return true;
						}
					}
					if(i-1>=0&&j-2>=0){
						if(board->getBoard(i-1,j-2).getSquare()->getName()=='k'){
							return true;
						}
					}
					if(i+1<8&&j+2<8){
						if(board->getBoard(i+1,j+2).getSquare()->getName()=='k'){
							return true;
						}
					}
					if(i+1<8&&j-2>=0){
						if(board->getBoard(i+1,j-2).getSquare()->getName()=='k'){
							return true;
						}
					}
				}
				//same we check if Bishop from player 2 can kill player 1 king by checking his movement and if they are true and not error and check if the square is king
				else if(board->getBoard(i,j).getSquare()->getName()=='B'){
					int w=i-1;
					int q=j+1;
					while(q<8&&w>=0&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='k')){
						if(board->getBoard(w,q).getSquare()->getName()=='k'){
							return true;
						}
						w--;
						q++;
					}
					w=i+1;
					q=j+1;
					while(w<8&&q<8&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='k')){
						if(board->getBoard(w,q).getSquare()->getName()=='k'){
							return true;
						}
						q++;
						w++;
					}
					w=i-1;
					q=j-1;
					while(w>=0&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='k')){
						if(board->getBoard(w,q).getSquare()->getName()=='k'){
							return true;
						}
						w--;
						q--;
					}
					w=i+1;
					q=j-1;
					while(w<8&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='k')){
						if(board->getBoard(w,q).getSquare()->getName()=='k'){
							return true;
						}
						q--;
						w++;
					}
				}
				//queen is a combine of rock and bishop so we check from play4er 2 	Queen if it can danger the king
				else if(board->getBoard(i,j).getSquare()->getName()=='Q'){
					int w=j+1;
					while(w<8&&board->getBoard(i,w).getSquare()->getName()=='.'){
						w++;
					}
					if(w<8){
						if(board->getBoard(i,w).getSquare()->getName()=='k'){
							return true;
						}
					}
					w=j-1;
					while(w>=0&&board->getBoard(i,w).getSquare()->getName()=='.'){
						w--;
					}
					if(w>=0){
						if(board->getBoard(i,w).getSquare()->getName()=='k'){
							return true;
						}
					}
					w=i+1;
					while(w<8&&board->getBoard(w,j).getSquare()->getName()=='.'){
						w++;
					}
					if(w<8){
						if(board->getBoard(w,j).getSquare()->getName()=='k'){
							return true;
						}
					}
					w=i-1;
					while(w>=0&&board->getBoard(w,j).getSquare()->getName()=='.'){
						w--;
					}
					if(w>=0){
						if(board->getBoard(w,j).getSquare()->getName()=='k'){
							return true;
						}
					}
					w=i-1;
					int q=j+1;
					while(q<8&&w>=0&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='k')){
						if(board->getBoard(w,q).getSquare()->getName()=='k'){
							return true;
						}
						w--;
						q++;
					}
					w=i+1;
					q=j+1;
					while(w<8&&q<8&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='k')){
						if(board->getBoard(w,q).getSquare()->getName()=='k'){
							return true;
						}
						q++;
						w++;
					}
					w=i-1;
					q=j-1;
					while(w>=0&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='k')){
						if(board->getBoard(w,q).getSquare()->getName()=='k'){
							return true;
						}
						w--;
						q--;
					}
					w=i+1;
					q=j-1;
					while(w<8&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='k')){
						if(board->getBoard(w,q).getSquare()->getName()=='k'){
							return true;
						}
						q--;
						w++;
					}
				}
				//We check if player 2 king can danger our king maybe this can not happend but it can if you start the board differently
				else if(board->getBoard(i,j).getSquare()->getName()=='K'){
					if(i-1>=0&&j+1<8){
						char name=board->getBoard(i-1,j+1).getSquare()->getName();
						if(name=='k'){
							return true;
						}
					}
					if(i-1>=0&&j-1>=0){

						char name=board->getBoard(i-1,j-1).getSquare()->getName();
						if(name=='k'){
							return true;
						}
					}
					if(i+1<8&&j+1<8){

						char name=board->getBoard(i+1,j+1).getSquare()->getName();
						if(name=='k'){
							return true;
						}
					}
					if(i+1<8&&j-1>=0){
						char name=board->getBoard(i+1,j-1).getSquare()->getName();
						if(name=='k'){
							return true;
						}
					}
					if(i-1>=0){
						char name=board->getBoard(i-1,j).getSquare()->getName();
						if(name=='k'){
							return true;
						}
					}
					if(i+1<8){
						char name=board->getBoard(i+1,j).getSquare()->getName();
						if(name=='k'){
							return true;
						}
					}
					if(j-1>=0){
						char name=board->getBoard(i,j-1).getSquare()->getName();
						if(name=='k'){
							return true;
						}
					}
					if(j+1<8){
						char name=board->getBoard(i,j+1).getSquare()->getName();
						if(name=='k'){
							return true;
						}
					}
				}
			}
		}
	}
	//here we do the same thing that we did in the first player king danger but to player 2 if none of them retured true that player 1 or player 2 turn
	//kings are in danger then it return in else false so we know player 1 king is not in danger or palyer 2 king is not in danger
	else{
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(board->getBoard(i,j).getSquare()->getName()=='p'){
					if(j+1<8&&i-1>=0){
						if(board->getBoard(i-1,j+1).getSquare()->getName()=='K'){
							return true;
						}
					}
					if(j-1>=0&&i-1>=0){
						if(board->getBoard(i-1,j-1).getSquare()->getName()=='K'){
							return true;
						}
					}
				}
				else if(board->getBoard(i,j).getSquare()->getName()=='r'){
					int w=j+1;
					while(w<8&&board->getBoard(i,w).getSquare()->getName()=='.'){
						w++;
					}
					if(w<8){
						if(board->getBoard(i,w).getSquare()->getName()=='K'){
							return true;
						}
					}
					w=j-1;
					while(w>=0&&board->getBoard(i,w).getSquare()->getName()=='.'){
						w--;
					}
					if(w>=0){
						if(board->getBoard(i,w).getSquare()->getName()=='K'){
							return true;
						}
					}
					w=i+1;
					while(w<8&&board->getBoard(w,j).getSquare()->getName()=='.'){
						w++;
					}
					if(w<8){
						if(board->getBoard(w,j).getSquare()->getName()=='K'){
							return true;
						}
					}
					w=i-1;
					while(w>=0&&board->getBoard(w,j).getSquare()->getName()=='.'){
						w--;
					}
					if(w>=0){
						if(board->getBoard(w,j).getSquare()->getName()=='K'){
							return true;
						}
					}
				}
				else if(board->getBoard(i,j).getSquare()->getName()=='n'){
					if(i-2>=0&&j+1<8){
						if(board->getBoard(i-2,j+1).getSquare()->getName()=='K'){
							return true;
						}
					}
					if(i-2>=0&&j-1>=0){
						if(board->getBoard(i-2,j-1).getSquare()->getName()=='K'){
							return true;
						}
					}
					if(i+2<8&&j+1<8){
						if(board->getBoard(i+2,j+1).getSquare()->getName()=='K'){
							return true;
						}
					}
					if(i+2<8&&j-1>=0){
						if(board->getBoard(i+2,j-1).getSquare()->getName()=='K'){
							return true;
						}
					}
					if(i-1>=0&&j+2<8){
						if(board->getBoard(i-1,j+2).getSquare()->getName()=='K'){
							return true;
						}
					}
					if(i-1>=0&&j-2>=0){
						if(board->getBoard(i-1,j-2).getSquare()->getName()=='K'){
							return true;
						}
					}
					if(i+1<8&&j+2<8){
						if(board->getBoard(i+1,j+2).getSquare()->getName()=='K'){
							return true;
						}
					}
					if(i+1<8&&j-2>=0){
						if(board->getBoard(i+1,j-2).getSquare()->getName()=='K'){
							return true;
						}
					}
				}
				else if(board->getBoard(i,j).getSquare()->getName()=='b'){
					int w=i-1;
					int q=j+1;
					while(q<8&&w>=0&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='K')){
						if(board->getBoard(w,q).getSquare()->getName()=='K'){
							return true;
						}
						w--;
						q++;
					}
					w=i+1;
					q=j+1;
					while(w<8&&q<8&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='K')){
						if(board->getBoard(w,q).getSquare()->getName()=='K'){
							return true;
						}
						q++;
						w++;
					}
					w=i-1;
					q=j-1;
					while(w>=0&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='K')){
						if(board->getBoard(w,q).getSquare()->getName()=='K'){
							return true;
						}
						w--;
						q--;
					}
					w=i+1;
					q=j-1;
					while(w<8&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='K')){
						if(board->getBoard(w,q).getSquare()->getName()=='K'){
							return true;
						}
						q--;
						w++;
					}
				}
				else if(board->getBoard(i,j).getSquare()->getName()=='q'){
					int w=j+1;
					while(w<8&&board->getBoard(i,w).getSquare()->getName()=='.'){
						w++;
					}
					if(w<8){
						if(board->getBoard(i,w).getSquare()->getName()=='K'){
							return true;
						}
					}
					w=j-1;
					while(w>=0&&board->getBoard(i,w).getSquare()->getName()=='.'){
						w--;
					}
					if(w>=0){
						if(board->getBoard(i,w).getSquare()->getName()=='K'){
							return true;
						}
					}
					w=i+1;
					while(w<8&&board->getBoard(w,j).getSquare()->getName()=='.'){
						w++;
					}
					if(w<8){
						if(board->getBoard(w,j).getSquare()->getName()=='K'){
							return true;
						}
					}
					w=i-1;
					while(w>=0&&board->getBoard(w,j).getSquare()->getName()=='.'){
						w--;
					}
					if(w>=0){
						if(board->getBoard(w,j).getSquare()->getName()=='K'){
							return true;
						}
					}
					w=i-1;
					int q=j+1;
					while(q<8&&w>=0&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='K')){
						if(board->getBoard(w,q).getSquare()->getName()=='K'){
							return true;
						}
						w--;
						q++;
					}
					w=i+1;
					q=j+1;
					while(w<8&&q<8&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='K')){
						if(board->getBoard(w,q).getSquare()->getName()=='K'){
							return true;
						}
						q++;
						w++;
					}
					w=i-1;
					q=j-1;
					while(w>=0&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='K')){
						if(board->getBoard(w,q).getSquare()->getName()=='K'){
							return true;
						}
						w--;
						q--;
					}
					w=i+1;
					q=j-1;
					while(w<8&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.'||board->getBoard(w,q).getSquare()->getName()=='K')){
						if(board->getBoard(w,q).getSquare()->getName()=='K'){
							return true;
						}
						q--;
						w++;
					}
				}
				else if(board->getBoard(i,j).getSquare()->getName()=='k'){
					if(i-1>=0&&j+1<8){
						char name=board->getBoard(i-1,j+1).getSquare()->getName();
						if(name=='K'){
							return true;
						}
					}
					if(i-1>=0&&j-1>=0){

						char name=board->getBoard(i-1,j-1).getSquare()->getName();
						if(name=='K'){
							return true;
						}
					}
					if(i+1<8&&j+1<8){

						char name=board->getBoard(i+1,j+1).getSquare()->getName();
						if(name=='K'){
							return true;
						}
					}
					if(i+1<8&&j-1>=0){
						char name=board->getBoard(i+1,j-1).getSquare()->getName();
						if(name=='K'){
							return true;
						}
					}
					if(i-1>=0){
						char name=board->getBoard(i-1,j).getSquare()->getName();
						if(name=='K'){
							return true;
						}
					}
					if(i+1<8){
						char name=board->getBoard(i+1,j).getSquare()->getName();
						if(name=='K'){
							return true;
						}
					}
					if(j-1>=0){
						char name=board->getBoard(i,j-1).getSquare()->getName();
						if(name=='K'){
							return true;
						}
					}
					if(j+1<8){
						char name=board->getBoard(i,j+1).getSquare()->getName();
						if(name=='K'){
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
//here is a function that check if player 1 elenments in the board has a availbe move to move or player 2
bool CanMove(Board *board,bool player1playing){//,bool player1playing){
	if(player1playing==true){
		//here we check every square of player 1 to check if it can move or anything,move or kill=Move
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				//checking player 1 elements if they can move or not
				if(board->getBoard(i,j).getSquare()->getName()=='p'){
					if(j+1<8&&i-1>=0){//check import toi+1<8
						char name=board->getBoard(i-1,j+1).getSquare()->getName();
						if(name!='.'&&name!='p'&&name!='q'&&name!='k'&&name!='n'&&name!='b'&&name!='r'){
							return true;
						}
					}
					if(j-1>=0&&i-1>=0){
						char name=board->getBoard(i+1,j-1).getSquare()->getName();
						if(name!='.'&&name!='p'&&name!='q'&&name!='k'&&name!='n'&&name!='b'&&name!='r'){
							return true;
						}
					}
					if(i-1>=0){
						if(board->getBoard(i-1,j).getSquare()->getName()=='.'){
							return true;
						}
					}
				}
				//checking rock if it can move or not and we know that we cant get off the board for all functions
				//********So its importnat to check that we are still in board to stop getting failures cause we cant get a null name
				else if(board->getBoard(i,j).getSquare()->getName()=='r'){
					if(i-1>=0){
						char name=board->getBoard(i-1,j).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
					if(i+1<8){
						char name=board->getBoard(i+1,j).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
					if(j-1>=0){
						char name=board->getBoard(i,j-1).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
					if(j+1<8){
						char name=board->getBoard(i,j+1).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
				}
				//we check if a existed Kniht has avaiable L move if not then weo go fo the second and if all not we get false we cant move
				//this situaten maybe get us to draw and get other player that can win to draw
				else if(board->getBoard(i,j).getSquare()->getName()=='n'){
					if(i-2>=0&&j+1<8){
						char name=board->getBoard(i-2,j+1).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
					if(i-2>=0&&j-1>=0){
						char name=board->getBoard(i-2,j-1).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
					if(i+2<8&&j+1<8){
						char name=board->getBoard(i+2,j+1).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
					if(i+2<8&&j-1>=0){
						char name=board->getBoard(i+2,j-1).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
					if(i-1>=0&&j+2<8){
						char name=board->getBoard(i-1,j+2).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
					if(i-1>=0&&j-2>=0){
						char name=board->getBoard(i-1,j-2).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
					if(i+1<8&&j+2<8){
						char name=board->getBoard(i+1,j+2).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
					if(i+1<8&&j-2>=0){
						char name=board->getBoard(i+1,j-2).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
				}
				//checking if bishop can move or not for plalyer 1
				else if(board->getBoard(i,j).getSquare()->getName()=='b'){
					if(i-1>=0&&j+1<8){
						char name=board->getBoard(i-1,j+1).getSquare()->getName();
						if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
							return true;
						}
					}
					if(i-1>=0&&j-1>=0){
						char name=board->getBoard(i-1,j-1).getSquare()->getName();
						if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
							return true;
						}
					}
					if(i+1<8&&j+1<8){
						char name=board->getBoard(i+1,j+1).getSquare()->getName();
						if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
							return true;
						}
					}
					if(i+1<8&&j-1>=0){
						char name=board->getBoard(i+1,j-1).getSquare()->getName();
						if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
							return true;
						}
					}
				}
				//combine bishop and rock and we check if the queen can move or not
				else if(board->getBoard(i,j).getSquare()->getName()=='q'){
					if(i-1>=0&&j+1<8){
						char name=board->getBoard(i-1,j+1).getSquare()->getName();
						if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
							return true;
						}
					}
					if(i-1>=0&&j-1>=0){
						char name=board->getBoard(i-1,j-1).getSquare()->getName();
						if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
							return true;
						}
					}
					if(i+1<8&&j+1<8){
						char name=board->getBoard(i+1,j+1).getSquare()->getName();
						if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
							return true;
						}
					}
					if(i+1<8&&j-1>=0){
						char name=board->getBoard(i+1,j-1).getSquare()->getName();
						if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
							return true;
						}
					}
					if(i-1>=0){
						char name=board->getBoard(i-1,j).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
					if(i+1<8){
						char name=board->getBoard(i+1,j).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
					if(j-1>=0){
						char name=board->getBoard(i,j-1).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
					if(j+1<8){
						char name=board->getBoard(i,j+1).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							return true;
						}
					}
				}
				//here we check if the king can move or not and maybe if we move it
				//we get king can be in danger and that is not good movement so we check that king is not in danger
				//and can move without getting in danger
				else if(board->getBoard(i,j).getSquare()->getName()=='k'){
					Board spare;
					if(i-1>=0&&j+1<8){
						spare.Same(*board);
						char name=board->getBoard(i-1,j+1).getSquare()->getName();
						if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
							board->getBoard(i-1,j+1).setExistedSquare('k');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,true);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(i-1>=0&&j-1>=0){
						spare.Same(*board);
						char name=board->getBoard(i-1,j-1).getSquare()->getName();
						if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
							board->getBoard(i-1,j-1).setExistedSquare('k');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,true);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(i+1<8&&j+1<8){
						spare.Same(*board);
						char name=board->getBoard(i+1,j+1).getSquare()->getName();
						if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
							board->getBoard(i+1,j+1).setExistedSquare('k');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,true);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(i+1<8&&j-1>=0){
						spare.Same(*board);
						char name=board->getBoard(i+1,j-1).getSquare()->getName();
						if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
							board->getBoard(i+1,j-1).setExistedSquare('k');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,true);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(i-1>=0){
						spare.Same(*board);
						char name=board->getBoard(i-1,j).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							board->getBoard(i-1,j).setExistedSquare('k');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,true);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(i+1<8){
						spare.Same(*board);
						char name=board->getBoard(i+1,j).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							board->getBoard(i+1,j).setExistedSquare('k');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,true);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(j-1>=0){
						spare.Same(*board);
						char name=board->getBoard(i,j-1).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							board->getBoard(i,j-1).setExistedSquare('k');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,true);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(j+1<8){
						spare.Same(*board);
						char name=board->getBoard(i,j+1).getSquare()->getName();
						if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
							board->getBoard(i,j+1).setExistedSquare('k');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,true);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
				}
			}
		}
		return false;
	}
	//same thing but for the player 2 and if all can not move or one of two players that we chceck we get false
	else{
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				if(board->getBoard(i,j).getSquare()->getName()=='P'){
					if(j+1<8&&i+1<8){
						char name=board->getBoard(i+1,j+1).getSquare()->getName();
						if(name!='.'&&name!='P'&&name!='Q'&&name!='K'&&name!='N'&&name!='B'&&name!='R'){
							return true;
						}
					}
					if(j-1>=0&&i+1<8){
						char name=board->getBoard(i+1,j-1).getSquare()->getName();
						if(name!='.'&&name!='P'&&name!='Q'&&name!='K'&&name!='N'&&name!='B'&&name!='R'){
							return true;
						}
					}
					if(i+1<8){
						if(board->getBoard(i+1,j).getSquare()->getName()=='.'){
							return true;
						}
					}
				}
				else if(board->getBoard(i,j).getSquare()->getName()=='R'){
					if(i-1>=0){
						char name=board->getBoard(i-1,j).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
					if(i+1<8){
						char name=board->getBoard(i+1,j).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
					if(j-1>=0){
						char name=board->getBoard(i,j-1).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
					if(j+1<8){
						char name=board->getBoard(i,j+1).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
				}
				else if(board->getBoard(i,j).getSquare()->getName()=='N'){
					if(i-2>=0&&j+1<8){
						char name=board->getBoard(i-2,j+1).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
					if(i-2>=0&&j-1>=0){
						char name=board->getBoard(i-2,j-1).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
					if(i+2<8&&j+1<8){
						char name=board->getBoard(i+2,j+1).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
					if(i+2<8&&j-1>=0){
						char name=board->getBoard(i+2,j-1).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
					if(i-1>=0&&j+2<8){
						char name=board->getBoard(i-1,j+2).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
					if(i-1>=0&&j-2>=0){
						char name=board->getBoard(i-1,j-2).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
					if(i+1<8&&j+2<8){
						char name=board->getBoard(i+1,j+2).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
					if(i+1<8&&j-2>=0){
						char name=board->getBoard(i+1,j-2).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
				}
				else if(board->getBoard(i,j).getSquare()->getName()=='B'){
					if(i-1>=0&&j+1<8){
						char name=board->getBoard(i-1,j+1).getSquare()->getName();
						if(name=='.'||name=='q'||name=='k'||name=='n'||name=='r'||name=='p'||name=='b'){
							return true;
						}
					}
					if(i-1>=0&&j-1>=0){
						char name=board->getBoard(i-1,j-1).getSquare()->getName();
						if(name=='.'||name=='q'||name=='k'||name=='n'||name=='r'||name=='p'||name=='b'){
							return true;
						}
					}
					if(i+1<8&&j+1<8){
						char name=board->getBoard(i+1,j+1).getSquare()->getName();
						if(name=='.'||name=='q'||name=='k'||name=='n'||name=='r'||name=='p'||name=='b'){
							return true;
						}
					}
					if(i+1<8&&j-1>=0){
						char name=board->getBoard(i+1,j-1).getSquare()->getName();
						if(name=='.'||name=='q'||name=='k'||name=='n'||name=='r'||name=='p'||name=='b'){
							return true;
						}
					}
				}
				else if(board->getBoard(i,j).getSquare()->getName()=='Q'){
					if(i-1>=0&&j+1<8){
						char name=board->getBoard(i-1,j+1).getSquare()->getName();
						if(name=='.'||name=='q'||name=='k'||name=='n'||name=='r'||name=='p'||name=='b'){
							return true;
						}
					}
					if(i-1>=0&&j-1>=0){
						char name=board->getBoard(i-1,j-1).getSquare()->getName();
						if(name=='.'||name=='q'||name=='k'||name=='n'||name=='r'||name=='p'||name=='b'){
							return true;
						}
					}
					if(i+1<8&&j+1<8){
						char name=board->getBoard(i+1,j+1).getSquare()->getName();
						if(name=='.'||name=='q'||name=='k'||name=='n'||name=='r'||name=='p'||name=='b'){
							return true;
						}
					}
					if(i+1<8&&j-1>=0){
						char name=board->getBoard(i+1,j-1).getSquare()->getName();
						if(name=='.'||name=='q'||name=='k'||name=='n'||name=='r'||name=='p'||name=='b'){
							return true;
						}
					}
					if(i-1>=0){
						char name=board->getBoard(i-1,j).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
					if(i+1<8){
						char name=board->getBoard(i+1,j).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
					if(j-1>=0){
						char name=board->getBoard(i,j-1).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
					if(j+1<8){
						char name=board->getBoard(i,j+1).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							return true;
						}
					}
				}
				else if(board->getBoard(i,j).getSquare()->getName()=='K'){
					Board spare;
					if(i-1>=0&&j+1<8){
						spare.Same(*board);
						char name=board->getBoard(i-1,j+1).getSquare()->getName();
						if(name=='.'||name=='q'||name=='k'||name=='n'||name=='r'||name=='p'||name=='b'){
							board->getBoard(i-1,j+1).setExistedSquare('K');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,false);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(i-1>=0&&j-1>=0){
						spare.Same(*board);
						char name=board->getBoard(i-1,j-1).getSquare()->getName();
						if(name=='.'||name=='q'||name=='k'||name=='n'||name=='r'||name=='p'||name=='b'){
							board->getBoard(i-1,j-1).setExistedSquare('K');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,false);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(i+1<8&&j+1<8){
						spare.Same(*board);
						char name=board->getBoard(i+1,j+1).getSquare()->getName();
						if(name=='.'||name=='q'||name=='k'||name=='n'||name=='r'||name=='p'||name=='b'){
							board->getBoard(i+1,j+1).setExistedSquare('K');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,false);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(i+1<8&&j-1>=0){
						spare.Same(*board);
						char name=board->getBoard(i+1,j-1).getSquare()->getName();
						if(name=='.'||name=='q'||name=='k'||name=='n'||name=='r'||name=='p'||name=='b'){
							board->getBoard(i+1,j-1).setExistedSquare('K');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,false);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(i-1>=0){
						spare.Same(*board);
						char name=board->getBoard(i-1,j).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							board->getBoard(i-1,j).setExistedSquare('K');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,false);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(i+1<8){
						spare.Same(*board);
						char name=board->getBoard(i+1,j).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							board->getBoard(i+1,j).setExistedSquare('K');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,false);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(j-1>=0){
						spare.Same(*board);
						char name=board->getBoard(i,j-1).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							board->getBoard(i,j-1).setExistedSquare('K');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,false);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
					if(j+1<8){
						spare.Same(*board);
						char name=board->getBoard(i,j+1).getSquare()->getName();
						if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
							board->getBoard(i,j+1).setExistedSquare('K');
							board->getBoard(i,j).setExistedSquare('.');
							bool check=KingCanDie(board,false);
							if(!check){
								board->Same(spare);
								return true;
							}
							board->Same(spare);
						}
					}
				}
			}
		}
		return false;
	}
	return false;
}
//here is a function that check every thing and check who can CheckMate the second player
bool CheckMate(Board *board,bool player1playing){
	Board spare;
	spare.Same(*board);
	//we check if it is the turn for player 1 and if he do it and king for second player is in danger and he cant do nothing then player 1 wins
	if(player1playing==true){
		if(KingCanDie(board,true)==true){
			//we check if king is in danger cause if it not we can not lose if it is we check if we can do a movement that protect king
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					//we check if existed movement from p that can help king from dying
					if(board->getBoard(i,j).getSquare()->getName()=='p'){
						if(i==6){
							char name=board->getBoard(4,j).getSquare()->getName();
							if(name=='.'){
							board->getBoard(4,j).setExistedSquare('p');
							board->getBoard(i,j).setExistedSquare('.');//we want to see if this has effect
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						if(i-1>=0){
						if(board->getBoard(i-1,j).getSquare()->getName()=='.'){
							board->getBoard(i-1,j).setExistedSquare('p');
							board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							board->Same(spare);
						}
						}
						if(i-1>=0&&j+1<8){
						char name=board->getBoard(i-1,j+1).getSquare()->getName();
						if(name!='.'&&name!='p'&&name!='r'&&name!='q'&&name!='k'&&name!='b'&&name!='n'){
							board->getBoard(i-1,j+1).setExistedSquare('p');
							board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							board->Same(spare);
						}
						}
						if(i-1>=0&&j-1>=0){
						char name=board->getBoard(i-1,j-1).getSquare()->getName();
						if(name!='.'&&name!='p'&&name!='r'&&name!='q'&&name!='k'&&name!='b'&&name!='n'){
							board->getBoard(i-1,j-1).setExistedSquare('p');
							board->getBoard(i,j).setExistedSquare('.');
//							board->PrintBoard();
//							cout<<endl;
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							board->Same(spare);
						}
						}

					}
					//checking if the Rock can do anything that can make king survive
					else if(board->getBoard(i,j).getSquare()->getName()=='r'){
						int w=j+1;
						while(w<8&&board->getBoard(i,w).getSquare()->getName()=='.'){
							board->getBoard(i,w).setExistedSquare('r');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							w++;
						}
						if(w<8){
						if(board->getBoard(i,w).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(i,w).setExistedSquare('r');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=j-1;
						while(w>=0&&board->getBoard(i,w).getSquare()->getName()=='.'){
							board->getBoard(i,w).setExistedSquare('r');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							w--;
						}
						if(w>=0){
						if(board->getBoard(i,w).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(i,w).setExistedSquare('r');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=i+1;
						while(w<8&&board->getBoard(w,j).getSquare()->getName()=='.'){
							board->getBoard(w,j).setExistedSquare('r');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							w++;
						}
						if(w<8){
						if(board->getBoard(w,j).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(w,j).setExistedSquare('r');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=i-1;
						while(w>=0&&board->getBoard(w,j).getSquare()->getName()=='.'){
							board->getBoard(w,j).setExistedSquare('r');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							w--;
						}
						if(w>=0){
						if(board->getBoard(w,j).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(w,j).setExistedSquare('r');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
					}
					//making anything from knight that can make knight still alive by using L movement
					else if(board->getBoard(i,j).getSquare()->getName()=='n'){
						if(i-2>=0&&j+1<8){
							char name=board->getBoard(i-2,j+1).getSquare()->getName();
							if(name=='.'||name=='P'||name=='Q'||name=='N'||name=='B'||name=='R'){
								board->getBoard(i-2,j+1).setExistedSquare('n');
								if(KingCanDie(board,true)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i-2>=0&&j-1>=0){
							char name=board->getBoard(i-2,j-1).getSquare()->getName();
							if(name=='.'||name=='P'||name=='Q'||name=='N'||name=='B'||name=='R'){
								board->getBoard(i-2,j-1).setExistedSquare('n');
								if(KingCanDie(board,true)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i+2<8&&j+1<8){
							char name=board->getBoard(i+2,j+1).getSquare()->getName();
							if(name=='.'||name=='P'||name=='Q'||name=='N'||name=='B'||name=='R'){
								board->getBoard(i+2,j+1).setExistedSquare('n');
								if(KingCanDie(board,true)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i+2<8&&j-1>=0){
							char name=board->getBoard(i+2,j-1).getSquare()->getName();
							if(name=='.'||name=='P'||name=='Q'||name=='N'||name=='B'||name=='R'){
								board->getBoard(i+2,j-1).setExistedSquare('n');
								if(KingCanDie(board,true)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i-1>=0&&j+2<8){
							char name=board->getBoard(i-1,j+2).getSquare()->getName();
							if(name=='.'||name=='P'||name=='Q'||name=='N'||name=='B'||name=='R'){
								board->getBoard(i-1,j+2).setExistedSquare('n');
								if(KingCanDie(board,true)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i-1>=0&&j-2>=0){
							char name=board->getBoard(i-1,j-2).getSquare()->getName();
							if(name=='.'||name=='P'||name=='Q'||name=='N'||name=='B'||name=='R'){
								board->getBoard(i-1,j-2).setExistedSquare('n');
								if(KingCanDie(board,true)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i+1<8&&j+2<8){
							char name=board->getBoard(i+1,j+2).getSquare()->getName();
							if(name=='.'||name=='P'||name=='Q'||name=='N'||name=='B'||name=='R'){
								board->getBoard(i+1,j+2).setExistedSquare('n');
								if(KingCanDie(board,true)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i+1<8&&j-2>=0){
							char name=board->getBoard(i+1,j-2).getSquare()->getName();
							if(name=='.'||name=='P'||name=='Q'||name=='N'||name=='B'||name=='R'){
								board->getBoard(i+1,j-2).setExistedSquare('n');
								if(KingCanDie(board,true)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
					}
					//we check if the bishop can save the king from dying
					else if(board->getBoard(i,j).getSquare()->getName()=='b'){
						int w=i-1;
						int q=j+1;
						while(q<8&&w>=0&&(board->getBoard(w,q).getSquare()->getName()=='.')){
							board->getBoard(w,q).setExistedSquare('b');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							w--;
							q++;
						}
						if(q<8&&w>=0){
						if(board->getBoard(w,q).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(w,q).setExistedSquare('b');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=i+1;
						q=j+1;
						while(w<8&&q<8&&(board->getBoard(w,q).getSquare()->getName()=='.')){
							board->getBoard(w,q).setExistedSquare('b');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							q++;
							w++;
						}
						if(w<8&&q<8){
						if(board->getBoard(w,q).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(w,q).setExistedSquare('b');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						w=i-1;
						q=j-1;
						while(w>=0&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.')){
							board->getBoard(w,q).setExistedSquare('b');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							w--;
							q--;
						}
						if(q>=0&&w>=0){
						if(board->getBoard(w,q).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(w,q).setExistedSquare('b');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						w=i+1;
						q=j-1;
						while(w<8&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.')){
							board->getBoard(w,q).setExistedSquare('b');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							q--;
							w++;
						}
						if(w<8&&q>=0){
						if(board->getBoard(w,q).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(w,q).setExistedSquare('b');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
					}
					//we check if the queen can help the king from dying or not
					else if(board->getBoard(i,j).getSquare()->getName()=='q'){
						int w=i-1;
						int q=j+1;
						while(q<8&&w>=0&&(board->getBoard(w,q).getSquare()->getName()=='.')){
							board->getBoard(w,q).setExistedSquare('q');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							w--;
							q++;
						}
						if(w>=0&&q<8){
						if(board->getBoard(w,q).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(w,q).setExistedSquare('q');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=i+1;
						q=j+1;
						while(w<8&&q<8&&(board->getBoard(w,q).getSquare()->getName()=='.')){
							board->getBoard(w,q).setExistedSquare('q');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							q++;
							w++;
						}
						if(q<8&&w<8){
						if(board->getBoard(w,q).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(w,q).setExistedSquare('q');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						w=i-1;
						q=j-1;
						while(w>=0&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.')){
							board->getBoard(w,q).setExistedSquare('q');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							w--;
							q--;
						}
						if(q>=0&&w>0){
						if(board->getBoard(w,q).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(w,q).setExistedSquare('q');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						w=i+1;
						q=j-1;
						while(w<8&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.')){
							board->getBoard(w,q).setExistedSquare('q');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							q--;
							w++;
						}
						if(q>=0&&w<8){
						if(board->getBoard(w,q).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(w,q).setExistedSquare('q');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						w=j+1;
						while(w<8&&board->getBoard(i,w).getSquare()->getName()=='.'){
							board->getBoard(i,w).setExistedSquare('q');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							w++;
						}
						if(w<8){
						if(board->getBoard(i,w).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(i,w).setExistedSquare('q');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=j-1;
						while(w>=0&&board->getBoard(i,w).getSquare()->getName()=='.'){
							board->getBoard(i,w).setExistedSquare('q');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							w--;
						}
						if(w>=0){
						if(board->getBoard(i,w).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(i,w).setExistedSquare('q');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=i+1;
						while(w<8&&board->getBoard(w,j).getSquare()->getName()=='.'){
							board->getBoard(w,j).setExistedSquare('q');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							w++;
						}
						if(w<8){
						if(board->getBoard(w,j).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(w,j).setExistedSquare('q');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=i-1;
						while(w>=0&&board->getBoard(w,j).getSquare()->getName()=='.'){
							board->getBoard(w,j).setExistedSquare('q');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
							w--;
						}
						if(w>=0){
						if(board->getBoard(w,j).getSquare()->getName()=='Q'||board->getBoard(i,w).getSquare()->getName()=='R'||board->getBoard(i,w).getSquare()->getName()=='P'||board->getBoard(i,w).getSquare()->getName()=='N'||board->getBoard(i,w).getSquare()->getName()=='B'){
							board->getBoard(w,j).setExistedSquare('q');
							if(KingCanDie(board,true)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
					}
					//we check that if the king by his self can do anything to protect his self from dying
					else if(board->getBoard(i,j).getSquare()->getName()=='k'){
						if(i-1>=0&&j+1<8){
							char name=board->getBoard(i-1,j+1).getSquare()->getName();
							if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
								board->getBoard(i-1,j+1).setExistedSquare('k');
								bool check=KingCanDie(board,true);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(i-1>=0&&j-1>=0){
							char name=board->getBoard(i-1,j-1).getSquare()->getName();
							if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
								board->getBoard(i-1,j-1).setExistedSquare('k');
								bool check=KingCanDie(board,true);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(i+1<8&&j+1<8){
							char name=board->getBoard(i+1,j+1).getSquare()->getName();
							if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
								board->getBoard(i+1,j+1).setExistedSquare('k');
								bool check=KingCanDie(board,true);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(i+1<8&&j-1>=0){
							char name=board->getBoard(i+1,j-1).getSquare()->getName();
							if(name=='.'||name=='Q'||name=='K'||name=='N'||name=='R'||name=='P'||name=='B'){
								board->getBoard(i+1,j-1).setExistedSquare('k');
								bool check=KingCanDie(board,true);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(i-1>=0){
							char name=board->getBoard(i-1,j).getSquare()->getName();
							if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
								board->getBoard(i-1,j).setExistedSquare('k');
								bool check=KingCanDie(board,true);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(i+1<8){
							char name=board->getBoard(i+1,j).getSquare()->getName();
							if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
								board->getBoard(i+1,j).setExistedSquare('k');
								bool check=KingCanDie(board,true);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(j-1>=0){
							char name=board->getBoard(i,j-1).getSquare()->getName();
							if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
								board->getBoard(i,j-1).setExistedSquare('k');
								bool check=KingCanDie(board,true);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(j+1<8){
							char name=board->getBoard(i,j+1).getSquare()->getName();
							if(name=='.'||name=='R'||name=='Q'||name=='K'||name=='P'||name=='B'||name=='N'){
								board->getBoard(i,j+1).setExistedSquare('k');
								bool check=KingCanDie(board,true);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
					}

				}
			}
			return true;
		}
		else{
			return false;
		}
	}
	//same thing we do for the other side but we do it by making the turn to player 2
	else{
		if(KingCanDie(board,false)==true){
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					if(board->getBoard(i,j).getSquare()->getName()=='P'){
						if(i==1){
							char name=board->getBoard(3,j).getSquare()->getName();
							if(name=='.'){
							board->getBoard(3,j).setExistedSquare('P');
							//board->getBoard(i,j).setExistedSquare('.');//we want to see if this has effect
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							}
						}
						if(i+1<8){
						if(board->getBoard(i+1,j).getSquare()->getName()=='.'){
							board->getBoard(i+1,j).setExistedSquare('P');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							board->Same(spare);
						}
						}
						if(j+1<8&&j+1<8){
						char name=board->getBoard(i+1,j+1).getSquare()->getName();
						if(name!='.'&&name!='P'&&name!='R'&&name!='Q'&&name!='K'&&name!='B'&&name!='N'){
							board->getBoard(i+1,j+1).setExistedSquare('P');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							board->Same(spare);
						}
						}
						if(j-1>=0&&i+1<8){
						char name=board->getBoard(i+1,j-1).getSquare()->getName();
						if(name!='.'&&name!='P'&&name!='R'&&name!='Q'&&name!='K'&&name!='B'&&name!='N'){
							board->getBoard(i+1,j-1).setExistedSquare('P');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							board->Same(spare);
						}
						}

					}
					else if(board->getBoard(i,j).getSquare()->getName()=='R'){
						int w=j+1;
						while(w<8&&board->getBoard(i,w).getSquare()->getName()=='.'){
							board->getBoard(i,w).setExistedSquare('R');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							w++;
						}
						if(w<8){
						if(board->getBoard(i,w).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
							board->getBoard(i,w).setExistedSquare('R');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=j-1;
						while(w>=0&&board->getBoard(i,w).getSquare()->getName()=='.'){
							board->getBoard(i,w).setExistedSquare('R');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							w--;
						}
						if(w>=0){
						if(board->getBoard(i,w).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
							board->getBoard(i,w).setExistedSquare('R');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=i+1;
						while(w<8&&board->getBoard(w,j).getSquare()->getName()=='.'){
							board->getBoard(w,j).setExistedSquare('R');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							w++;
						}
						if(w<8){
						if(board->getBoard(w,j).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
							board->getBoard(w,j).setExistedSquare('R');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=i-1;
						while(w>=0&&board->getBoard(w,j).getSquare()->getName()=='.'){
							board->getBoard(w,j).setExistedSquare('R');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							w--;
						}
						if(w>=0){
						if(board->getBoard(w,j).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
							board->getBoard(w,j).setExistedSquare('R');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
					}
					else if(board->getBoard(i,j).getSquare()->getName()=='N'){
						if(i-2>=0&&j+1<8){
							char name=board->getBoard(i-2,j+1).getSquare()->getName();
							if(name=='.'||name=='p'||name=='q'||name=='n'||name=='b'||name=='r'){
								board->getBoard(i-2,j+1).setExistedSquare('N');
								if(KingCanDie(board,false)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i-2>=0&&j-1>=0){
							char name=board->getBoard(i-2,j-1).getSquare()->getName();
							if(name=='.'||name=='p'||name=='q'||name=='n'||name=='b'||name=='r'){
								board->getBoard(i-2,j-1).setExistedSquare('N');
								if(KingCanDie(board,false)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i+2<8&&j+1<8){
							char name=board->getBoard(i+2,j+1).getSquare()->getName();
							if(name=='.'||name=='p'||name=='q'||name=='n'||name=='b'||name=='r'){
								board->getBoard(i+2,j+1).setExistedSquare('N');
								if(KingCanDie(board,false)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i+2<8&&j-1>=0){
							char name=board->getBoard(i+2,j-1).getSquare()->getName();
							if(name=='.'||name=='p'||name=='q'||name=='n'||name=='b'||name=='r'){
								board->getBoard(i+2,j-1).setExistedSquare('N');
								if(KingCanDie(board,false)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i-1>=0&&j+2<8){
							char name=board->getBoard(i-1,j+2).getSquare()->getName();
							if(name=='.'||name=='p'||name=='q'||name=='n'||name=='b'||name=='r'){
								board->getBoard(i-1,j+2).setExistedSquare('N');
								if(KingCanDie(board,false)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i-1>=0&&j-2>=0){
							char name=board->getBoard(i-1,j-2).getSquare()->getName();
							if(name=='.'||name=='p'||name=='q'||name=='n'||name=='b'||name=='r'){
								board->getBoard(i-1,j-2).setExistedSquare('N');
								if(KingCanDie(board,false)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i+1<8&&j+2<8){
							char name=board->getBoard(i+1,j+2).getSquare()->getName();
							if(name=='.'||name=='p'||name=='q'||name=='n'||name=='b'||name=='r'){
								board->getBoard(i+1,j+2).setExistedSquare('N');
								if(KingCanDie(board,false)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
						if(i+1<8&&j-2>=0){
							char name=board->getBoard(i+1,j-2).getSquare()->getName();
							if(name=='.'||name=='p'||name=='q'||name=='n'||name=='b'||name=='r'){
								board->getBoard(i+1,j-2).setExistedSquare('N');
								if(KingCanDie(board,false)==false){
									board->Same(spare);
									return false;
								}
							}
						}
						board->Same(spare);
					}
					else if(board->getBoard(i,j).getSquare()->getName()=='B'){

					int w=i-1;
					int q=j+1;
					while(q<8&&w>=0&&(board->getBoard(w,q).getSquare()->getName()=='.')){
						board->getBoard(w,q).setExistedSquare('B');
						if(KingCanDie(board,false)==false){
							board->Same(spare);
							return false;
						}
						w--;
						q++;
					}
					if(q<8&&w>=0){
					if(board->getBoard(w,q).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
						board->getBoard(w,q).setExistedSquare('B');
						if(KingCanDie(board,false)==false){
							board->Same(spare);
							return false;
						}
					}
					}
					board->Same(spare);
					w=i+1;
					q=j+1;
					while(w<8&&q<8&&(board->getBoard(w,q).getSquare()->getName()=='.')){
						board->getBoard(w,q).setExistedSquare('B');
						if(KingCanDie(board,false)==false){
							board->Same(spare);
							return false;
						}
						q++;
						w++;
					}
					if(w<8&&q<8){
					if(board->getBoard(w,q).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
						board->getBoard(w,q).setExistedSquare('B');
						if(KingCanDie(board,false)==false){
							board->Same(spare);
							return false;
						}
					}
					}
					w=i-1;
					q=j-1;
					while(w>=0&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.')){
						board->getBoard(w,q).setExistedSquare('B');
						if(KingCanDie(board,false)==false){
							board->Same(spare);
							return false;
						}
						w--;
						q--;
					}
					if(q>=0&&w>=0){
					if(board->getBoard(w,q).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
						board->getBoard(w,q).setExistedSquare('B');
						if(KingCanDie(board,false)==false){
							board->Same(spare);
							return false;
						}
					}
					}
					w=i+1;
					q=j-1;
					while(w<8&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.')){
						board->getBoard(w,q).setExistedSquare('B');
						if(KingCanDie(board,false)==false){
							board->Same(spare);
							return false;
						}
						q--;
						w++;
					}
					if(q>=0&&w<8){
					if(board->getBoard(w,q).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
						board->getBoard(w,q).setExistedSquare('B');
						if(KingCanDie(board,false)==false){
							board->Same(spare);
							return false;
						}
					}
					}
					}
					else if(board->getBoard(i,j).getSquare()->getName()=='Q'){
						cout<<"bfn5k"<<endl;
						int w=j+1;
						while(w<8&&board->getBoard(i,w).getSquare()->getName()=='.'){
							board->getBoard(i,w).setExistedSquare('Q');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							w++;
						}
						if(w<8){
						if(board->getBoard(i,w).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
							board->getBoard(i,w).setExistedSquare('Q');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=j-1;
						while(w>=0&&board->getBoard(i,w).getSquare()->getName()=='.'){
							board->getBoard(i,w).setExistedSquare('Q');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							w--;
						}
						if(w>=0){
						if(board->getBoard(i,w).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
							board->getBoard(i,w).setExistedSquare('Q');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=i+1;
						while(w<8&&board->getBoard(w,j).getSquare()->getName()=='.'){
							board->getBoard(w,j).setExistedSquare('Q');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							w++;
						}
						if(w<8){
						if(board->getBoard(w,j).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
							board->getBoard(w,j).setExistedSquare('Q');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=i-1;
						while(w>=0&&board->getBoard(w,j).getSquare()->getName()=='.'){
							board->getBoard(w,j).setExistedSquare('Q');
						//	board->getBoard(i,j).setExistedSquare('.');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							w--;
						}
						if(w>=0){
						if(board->getBoard(w,j).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
							board->getBoard(w,j).setExistedSquare('Q');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=i-1;
						int q=j+1;
						while(q<8&&w>=0&&(board->getBoard(w,q).getSquare()->getName()=='.')){
							board->getBoard(w,q).setExistedSquare('Q');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							w--;
							q++;
						}
						if(w>=0&&q<8){
						if(board->getBoard(w,q).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
							board->getBoard(w,q).setExistedSquare('Q');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						board->Same(spare);
						w=i+1;
						q=j+1;
						while(w<8&&q<8&&(board->getBoard(w,q).getSquare()->getName()=='.')){
							board->getBoard(w,q).setExistedSquare('Q');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							q++;
							w++;
						}
						if(w<8&&q<8){
						if(board->getBoard(w,q).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
							board->getBoard(w,q).setExistedSquare('Q');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						w=i-1;
						q=j-1;
						while(w>=0&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.')){
							board->getBoard(w,q).setExistedSquare('Q');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							w--;
							q--;
						}
						if(w>=0&&q>=0){
						if(board->getBoard(w,q).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
							board->getBoard(w,q).setExistedSquare('Q');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
						}
						}
						w=i+1;
						q=j-1;
						while(w<8&&q>=0&&(board->getBoard(w,q).getSquare()->getName()=='.')){
							cout<<"Whyyyy";
							board->getBoard(w,q).setExistedSquare('Q');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
							q--;
							w++;
						}
						if(q>=0&&w<8){
						if(board->getBoard(w,q).getSquare()->getName()=='q'||board->getBoard(i,w).getSquare()->getName()=='r'||board->getBoard(i,w).getSquare()->getName()=='p'||board->getBoard(i,w).getSquare()->getName()=='n'||board->getBoard(i,w).getSquare()->getName()=='b'){
							board->getBoard(w,q).setExistedSquare('Q');
							if(KingCanDie(board,false)==false){
								board->Same(spare);
								return false;
							}
						}
						}
					}
					else if(board->getBoard(i,j).getSquare()->getName()=='k'){
						if(i-1>=0&&j+1<8){
							char name=board->getBoard(i-1,j+1).getSquare()->getName();
							if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
								board->getBoard(i-1,j+1).setExistedSquare('K');
								bool check=KingCanDie(board,false);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(i-1>=0&&j-1>=0){
							char name=board->getBoard(i-1,j-1).getSquare()->getName();
							if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
								board->getBoard(i-1,j-1).setExistedSquare('K');
								bool check=KingCanDie(board,false);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(i+1<8&&j+1<8){
							char name=board->getBoard(i+1,j+1).getSquare()->getName();
							if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
								board->getBoard(i+1,j+1).setExistedSquare('K');
								bool check=KingCanDie(board,false);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(i+1<8&&j-1>=0){
							char name=board->getBoard(i+1,j-1).getSquare()->getName();
							if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
								board->getBoard(i+1,j-1).setExistedSquare('K');
								bool check=KingCanDie(board,false);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(i-1>=0){
							char name=board->getBoard(i-1,j).getSquare()->getName();
							if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
								board->getBoard(i-1,j).setExistedSquare('K');
								bool check=KingCanDie(board,false);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(i+1<8){
							char name=board->getBoard(i+1,j).getSquare()->getName();
							if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
								board->getBoard(i+1,j).setExistedSquare('K');
								bool check=KingCanDie(board,false);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(j-1>=0){
							char name=board->getBoard(i,j-1).getSquare()->getName();
							if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
								board->getBoard(i,j-1).setExistedSquare('K');
								bool check=KingCanDie(board,false);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
						if(j+1<8){
							char name=board->getBoard(i,j+1).getSquare()->getName();
							if(name=='.'||name=='r'||name=='q'||name=='k'||name=='p'||name=='b'||name=='n'){
								board->getBoard(i,j+1).setExistedSquare('K');
								bool check=KingCanDie(board,false);
								if(!check){
									board->Same(spare);
									return false;
								}
								board->Same(spare);
							}
						}
					}
					return true;
				}
			}
			return true;
		}
		else{
			return false;
		}
	}
	return true;
}
void possiblemove(char name,Board* board,int my_x,int my_y,int to_x,int to_y,int step,char change){
	//here is the most important function that can make our player move from step to step in board
	//checking if where we wanna move is in the board or not
	if(to_x>7||to_x<0||to_y>7||to_y<0){
		error=true;
		cerr<<step<<") Invalid input; please enter a move:"<<endl;
		return;
	}
	//check if we did move or not
	if(my_x==to_x&&to_y==my_y){
		error=true;
		cerr<<step<<") Invalid input; please enter a move:"<<endl;
		return;
	}
	//if the name is p that we take by my input so now we check to input to see where it goes
	if(name=='p'){
		if(abs(to_x-my_x)==1){//we move only 1 spot
				if(to_x!=0){//we reached the top
					if(change!=' '){
						error=true;
						cerr<<step<<") Invalid input; please enter a move:"<<endl;
						return;
					}
				}
		}
		char us=board->getBoard(to_x,to_y).getSquare()->getName();
		if(us=='p'||us=='r'||us=='n'||us=='b'||us=='q'||us=='k'){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		if(to_x>=my_x){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		//first we try to kill other we do regular
		if(to_x==my_x-1&&(my_y==to_y-1||my_y==to_y+1)){
			if(board->getBoard(to_x,to_y).getSquare()->getName()!='.'){//enpassant is here cause we going to .
				if(to_x==0){
					if(change!='r'&&change!='b'&&change!='q'&&change!='n'){
						error=true;
						cerr<<step<<") Invalid input; please enter a move:"<<endl;
						return;
					}
					else{
						board->getBoard(to_x,to_y).setExistedSquare(change);
						board->getBoard(my_x,my_y).setExistedSquare('.');
						player1turn=false;
						enpassant=false;
						all++;
						return;
					}
				}
				board->getBoard(to_x,to_y).setExistedSquare('p');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=false;
				enpassant=false;
				all++;
				return;
			}
			if(enpassant){//we chheck if enpassant can be happend and after that we check our array last x y
					if(board->getBoard(my_x,my_y-1).getSquare()->getName()=='P'&&lastxy[0]==my_x&&lastxy[1]==my_y-1){
						if(to_x+1==my_x&&to_y+1==my_y){
							board->getBoard(to_x,to_y).setExistedSquare('p');
							board->getBoard(my_x,my_y).setExistedSquare('.');
							board->getBoard(my_x,my_y-1).setExistedSquare('.');
							player1turn=false;
							enpassant=false;
							all++;
							return;
						}
						else{
							error=true;
							cerr<<step<<") Invalid input; please enter a move:"<<endl;
							return;
						}
					}
					else if(board->getBoard(my_x,my_y+1).getSquare()->getName()=='P'&&lastxy[0]==my_x&&lastxy[1]==my_y+1){
						if(to_x+1==my_x&&to_y-1==my_y){
							board->getBoard(to_x,to_y).setExistedSquare('p');
							board->getBoard(my_x,my_y).setExistedSquare('.');
							board->getBoard(my_x,my_y+1).setExistedSquare('.');
							player1turn=false;
							enpassant=false;
							all++;
							return;
						}
						else{
							error=true;
							cerr<<step<<") Invalid input; please enter a move:"<<endl;
							return;
						}
					}
				}
			}
		if(to_y-my_y==0&&abs(to_x-my_x)<=2){//in the same line and less than 2
			if(abs(to_x-my_x)>2){//bigger than 2
				error=true;
				cerr<<step<<")Illegal move; please enter a move:"<<endl;
				return;
			}
			if(abs(to_x-my_x)<=2&&my_x==6){//first travel and less than 2
				if(abs(to_x-my_x)==2){
					if(board->getBoard(to_x+1,to_y).getSquare()->getName()!='.'){
						error=true;
						cerr<<step<<")Illegal move; please enter a move:"<<endl;
						return;
					}
				}
				if(abs(to_x-my_x)==2){
					if(board->getBoard(to_x,to_y).getSquare()->getName()=='.'){//going to legal place that has .
						lastxy[0]=to_x;
						lastxy[1]=to_y;
						board->getBoard(to_x,to_y).setExistedSquare(name);
						board->getBoard(my_x,my_y).setExistedSquare('.');
						player1turn=false;
						enpassant=true;
						all++;
						return;
					}
					else{
						error=true;
						cerr<<step<<")Illegal move; please enter a move:"<<endl;
						return;
					}
				}
				if(board->getBoard(to_x,to_y).getSquare()->getName()=='.'){//going to legal place that has .
					board->getBoard(to_x,to_y).setExistedSquare(name);
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=false;
					enpassant=false;
					all++;
					return;
				}
				else{
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			else if(abs(to_x-my_x)==1){//we move only 1 spot
				if(board->getBoard(to_x,to_y).getSquare()->getName()=='.'){
					if(to_x==0){//we reached the top
						if(change!='r'&&change!='b'&&change!='q'&&change!='n'){
							error=true;
							cerr<<step<<") Invalid input; please enter a move:"<<endl;
							return;
						}
						board->getBoard(to_x,to_y).setExistedSquare(change);
						board->getBoard(my_x,my_y).setExistedSquare('.');
						player1turn=false;
						enpassant=false;
						all++;
						return;
					}
					else{//not reached the top
						board->getBoard(to_x,to_y).setExistedSquare(name);
						board->getBoard(my_x,my_y).setExistedSquare('.');
						player1turn=false;
						enpassant=false;
						all++;
						return;
					}
				}
				else{
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			else{
				error=true;
				cerr<<step<<")Illegal move; please enter a move:"<<endl;
				return;
			}
		}
		else{
			error=true;
		cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
	}
	else if(name=='P'){
		if(abs(to_x-my_x)==1){//we move only 1 spot
				if(to_x!=7){//we reached the top
					if(change!=' '){
						error=true;
						cerr<<step<<") Invalid input; please enter a move:"<<endl;
						return;
					}
				}
		}
		char us=board->getBoard(to_x,to_y).getSquare()->getName();
		if(us=='P'||us=='R'||us=='N'||us=='B'||us=='Q'||us=='K'){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		if(to_x<=my_x){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		//first we try to kill other we do regular
		if(to_x==my_x+1&&(my_y==to_y-1||my_y==to_y+1)){
			if(board->getBoard(to_x,to_y).getSquare()->getName()!='.'){
				if(to_x==7){
					if(change!='R'&&change!='B'&&change!='Q'&&change!='N'){
						error=true;
						cerr<<step<<") Invalid input; please enter a move:"<<endl;
						return;
					}
					else{
						board->getBoard(to_x,to_y).setExistedSquare(change);
						board->getBoard(my_x,my_y).setExistedSquare('.');
						player1turn=true;
						enpassant=false;
						all++;
						return;
					}
				}
				board->getBoard(to_x,to_y).setExistedSquare('P');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=true;
				enpassant=false;
				all++;
				return;
			}
			if(enpassant){//we check enpassant and after that our last two movements if they are like P p to do the enpassant
				if(board->getBoard(my_x,my_y-1).getSquare()->getName()=='p'&&lastxy[0]==my_x&&lastxy[1]==my_y-1){
					if(to_x-1==my_x&&to_y+1==my_y){
						board->getBoard(to_x,to_y).setExistedSquare('P');
						board->getBoard(my_x,my_y).setExistedSquare('.');
						board->getBoard(my_x,my_y-1).setExistedSquare('.');
						player1turn=true;
						enpassant=false;
						all++;
						return;
					}
				}
				else if(board->getBoard(my_x,my_y+1).getSquare()->getName()=='p'&&lastxy[0]==my_x&&lastxy[1]==my_y+1){
					if(to_x-1==my_x&&to_y-1==my_y){
						board->getBoard(to_x,to_y).setExistedSquare('P');
						board->getBoard(my_x,my_y).setExistedSquare('.');
						board->getBoard(my_x,my_y+1).setExistedSquare('.');
						player1turn=true;//check here ................................
						enpassant=false;
						all++;
						return;
					}
				}
			}
		}
		if(to_y-my_y==0&&abs(to_x-my_x)<=2){//in the same line and less than 2
			if(abs(to_x-my_x)>2){//bigger than 2//check
				error=true;
				cerr<<step<<")Illegal move; please enter a move:"<<endl;
				return;
			}
			if(abs(to_x-my_x)<=2&&my_x==1){//first travel and less than 2
				if(abs(to_x-my_x)==2){
					if(board->getBoard(to_x-1,to_y).getSquare()->getName()!='.'){
						error=true;
						cerr<<step<<")Illegal move; please enter a move:"<<endl;
						return;
					}

				}
				if(abs(to_x-my_x)==2){
					if(board->getBoard(to_x,to_y).getSquare()->getName()=='.'){//going to legal place that has .
						lastxy[0]=to_x;
						lastxy[1]=to_y;
						board->getBoard(to_x,to_y).setExistedSquare(name);
						board->getBoard(my_x,my_y).setExistedSquare('.');
						player1turn=true;
						enpassant=true;
						all++;
						return;
					}
					else{
						error=true;
						cerr<<step<<")Illegal move; please enter a move:"<<endl;
						return;
					}
				}
				if(board->getBoard(to_x,to_y).getSquare()->getName()=='.'){//going to legal place that has .
					board->getBoard(to_x,to_y).setExistedSquare(name);
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=true;
					enpassant=false;
					all++;
					return;
				}
				else{
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			else if(abs(to_x-my_x)==1){//we move only 1 spot
				if(board->getBoard(to_x,to_y).getSquare()->getName()=='.'){
					if(to_x==7){//we reached the top
						if(change!='R'&&change!='B'&&change!='Q'&&change!='N'){
							error=true;
							cerr<<step<<") Invalid input; please enter a move:"<<endl;
							return;
						}
						board->getBoard(to_x,to_y).setExistedSquare(change);
						board->getBoard(my_x,my_y).setExistedSquare('.');
						player1turn=true;
						enpassant=false;
						all++;
						return;
					}
					else{//not reached the top
						board->getBoard(to_x,to_y).setExistedSquare(name);
						board->getBoard(my_x,my_y).setExistedSquare('.');
						player1turn=true;
						enpassant=false;
						all++;
						return;
					}
				}
				else{
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			else{
				error=true;
				cerr<<step<<")Illegal move; please enter a move:"<<endl;
				return;
			}
		}
		else{
			error=true;
		cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
	}
	//we check rock availble move if not error if yes or kill we move our rock a time like -> a time like <- a time up a time down
	else if(name=='r'){
		if(my_y!=to_y&&my_x!=to_x){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		char name=board->getBoard(to_x,to_y).getSquare()->getName();
		if(name=='p'||name=='r'||name=='n'||name=='b'||name=='q'||name=='k'){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		if(my_x>to_x){
			char name;
			for(int i=my_x-1;i>to_x;i--){
				name=board->getBoard(i,my_y).getSquare()->getName();
				if(name!='.'){
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			board->getBoard(to_x,to_y).setExistedSquare('r');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			if(my_x==7&&my_y==7){
				player1bcastling=false;
			}
			else if(my_x==7&&my_y==0){
				player1acastling=false;
			}
			player1turn=false;
			all++;
			return;

		}
		if(my_x<to_x){
			char name;
			for(int i=my_x+1;i<to_x;i++){
				name=board->getBoard(i,my_y).getSquare()->getName();
				if(name!='.'){
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			board->getBoard(to_x,to_y).setExistedSquare('r');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			if(my_x==7&&my_y==7){
				player1bcastling=false;
			}
			else if(my_x==7&&my_y==0){
				player1acastling=false;
			}
			player1turn=false;
			all++;
			return;

		}
		if(my_y<to_y){
			char name;
			for(int i=my_y+1;i<to_y;i++){
				name=board->getBoard(my_x,i).getSquare()->getName();
				if(name!='.'){
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			board->getBoard(to_x,to_y).setExistedSquare('r');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			if(my_x==7&&my_y==7){
				player1bcastling=false;
			}
			else if(my_x==7&&my_y==0){
				player1acastling=false;
			}
			player1turn=false;
			all++;
			return;

		}
		if(my_y>to_y){
			char name;
			for(int i=my_y-1;i>to_y;i--){
				name=board->getBoard(my_x,i).getSquare()->getName();
				if(name!='.'){
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			board->getBoard(to_x,to_y).setExistedSquare('r');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			if(my_x==7&&my_y==7){
				player1bcastling=false;
			}
			else if(my_x==7&&my_y==0){
				player1acastling=false;
			}
			player1turn=false;
			all++;
			return;
		}

	}
	//other rock the same exact thing but for player 2 cause -> same as ->
	else if(name=='R'){
		if(my_y!=to_y&&my_x!=to_x){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		char name=board->getBoard(to_x,to_y).getSquare()->getName();
		if(name=='P'||name=='R'||name=='N'||name=='B'||name=='Q'||name=='K'){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		if(my_x>to_x){
			char name;
			for(int i=my_x-1;i>to_x;i--){
				name=board->getBoard(i,my_y).getSquare()->getName();
				if(name!='.'){
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			board->getBoard(to_x,to_y).setExistedSquare('R');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			if(my_x==0&&my_y==0){
				player2bcastling=false;
			}
			else if(my_x==0&&my_y==7){
				player2acastling=false;
			}
			player1turn=true;
			all++;
			return;
		}
		if(my_x<to_x){
			char name;
			for(int i=my_x+1;i<to_x;i++){
				name=board->getBoard(i,my_y).getSquare()->getName();
				if(name!='.'){
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			board->getBoard(to_x,to_y).setExistedSquare('R');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			if(my_x==0&&my_y==0){
				player2bcastling=false;
			}
			else if(my_x==0&&my_y==7){
				player2acastling=false;
			}
			player1turn=true;
			all++;
			return;
		}
		if(my_y<to_y){
			char name;
			for(int i=my_y+1;i<to_y;i++){
				name=board->getBoard(my_x,i).getSquare()->getName();
				if(name!='.'){
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			board->getBoard(to_x,to_y).setExistedSquare('R');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			if(my_x==0&&my_y==0){
				player2bcastling=false;
			}
			else if(my_x==0&&my_y==7){
				player2acastling=false;
			}
			player1turn=true;
			all++;
			return;
		}
		if(my_y>to_y){
			char name;
			for(int i=my_y-1;i>to_y;i--){
				name=board->getBoard(my_x,i).getSquare()->getName();
				if(name!='.'){
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			board->getBoard(to_x,to_y).setExistedSquare('R');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			if(my_x==0&&my_y==0){
				player2bcastling=false;
			}
			else if(my_x==0&&my_y==7){
				player2acastling=false;
			}
			player1turn=true;
			all++;
			return;
		}

	}
	//we ccheck if L movement is allowed and too is not one of our elements like other r p q ... and if yes we move or kill if not error
	else if(name=='n'){
		char name=board->getBoard(to_x,to_y).getSquare()->getName();
		if(name=='p'||name=='r'||name=='n'||name=='b'||name=='q'||name=='k'){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		else{
			if(to_x+2==my_x&&(my_y==to_y+1||my_y==to_y-1)){
				board->getBoard(to_x,to_y).setExistedSquare('n');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=false;
				all++;
				return;
			}
			if(to_y==my_y+2&&(to_x-1==my_x||to_x+1==my_x)){
				board->getBoard(to_x,to_y).setExistedSquare('n');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=false;
				all++;
				return;
			}
			if(to_y+2==my_y&&(to_x-1==my_x||to_x+1==my_x)){
				board->getBoard(to_x,to_y).setExistedSquare('n');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=false;
				all++;
				return;
			}
			if(to_x-2==my_x&&(my_y==to_y+1||my_y==to_y-1)){
				board->getBoard(to_x,to_y).setExistedSquare('n');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=false;
				all++;
				return;
			}
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;

		}
	}
	//same exact thing but frok player 2
	else if(name=='N'){
		char name=board->getBoard(to_x,to_y).getSquare()->getName();
		if(name=='P'||name=='R'||name=='N'||name=='B'||name=='Q'||name=='K'){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		else{
			if(to_x+2==my_x&&(my_y==to_y+1||my_y==to_y-1)){
				board->getBoard(to_x,to_y).setExistedSquare('N');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=true;
				all++;
				return;
			}
			if(to_y==my_y+2&&(to_x-1==my_x||to_x+1==my_x)){
				board->getBoard(to_x,to_y).setExistedSquare('N');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=true;
				all++;
				return;
			}
			if(to_y+2==my_y&&(to_x-1==my_x||to_x+1==my_x)){
				board->getBoard(to_x,to_y).setExistedSquare('N');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=true;
				all++;
				return;
			}
			if(to_x-2==my_x&&(my_y==to_y+1||my_y==to_y-1)){
				board->getBoard(to_x,to_y).setExistedSquare('N');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=true;
				all++;
				return;
			}
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;

		}
	}
	//we check if bishop can kill or move if not error and we know how bishop move and Bishop is exactly the same but for player 2
	else if(name=='b'){
		if(abs(to_x-my_x)!=abs(to_y-my_y)){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		char name=board->getBoard(to_x,to_y).getSquare()->getName();
		if(name=='p'||name=='r'||name=='n'||name=='b'||name=='q'||name=='k'){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		int tempy=my_y+1;
		if(my_x<to_x&&my_y<to_y){
			char name;
			for(int i=my_x+1;i<to_x;i++){
				name=board->getBoard(i,tempy++).getSquare()->getName();
				if(name!='.'){
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			board->getBoard(to_x,to_y).setExistedSquare('b');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			player1turn=false;
			all++;
			return;
		}
			tempy=my_y+1;
			if(my_x>to_x&&my_y<to_y){
				char name;
				for(int i=my_x-1;i>to_x;i--){
					name=board->getBoard(i,tempy++).getSquare()->getName();
					if(name!='.'){
						error=true;
						cerr<<step<<")Illegal move; please enter a move:"<<endl;
						return;
					}
				}
				board->getBoard(to_x,to_y).setExistedSquare('b');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=false;
				all++;
				return;
			}
			tempy=to_y+1;
			if(my_x>to_x&&my_y>to_y){
				char name;
				for(int i=to_x+1;i<my_x;i++){
					name=board->getBoard(i,tempy++).getSquare()->getName();
					if(name!='.'){
						error=true;
						cerr<<step<<")Illegal move; please enter a move:"<<endl;
						return;
					}
				}
				board->getBoard(to_x,to_y).setExistedSquare('b');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=false;
				all++;
				return;
			}
			tempy=to_y+1;
			if(my_x<to_x&&my_y>to_y){
				char name;
				for(int i=to_x-1;i>my_x;i--){
					name=board->getBoard(i,tempy++).getSquare()->getName();
					if(name!='.'){
						error=true;
						cerr<<step<<")Illegal move; please enter a move:"<<endl;
						return;
					}
				}
				board->getBoard(to_x,to_y).setExistedSquare('b');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=false;
				all++;
				return;
			}
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
	}
	//same thing
	else if(name=='B'){
		if(abs(to_x-my_x)!=abs(to_y-my_y)){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		char name=board->getBoard(to_x,to_y).getSquare()->getName();
		if(name=='P'||name=='R'||name=='N'||name=='B'||name=='Q'||name=='K'){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		int tempy=my_y+1;
		if(my_x<to_x&&my_y<to_y){
			char name;
			for(int i=my_x+1;i<to_x;i++){
				name=board->getBoard(i,tempy++).getSquare()->getName();
				if(name!='.'){
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
			}
			board->getBoard(to_x,to_y).setExistedSquare('B');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			player1turn=true;
			all++;
			return;
		}
			tempy=my_y+1;
			if(my_x>to_x&&my_y<to_y){
				char name;
				for(int i=my_x-1;i>to_x;i--){
					name=board->getBoard(i,tempy++).getSquare()->getName();
					if(name!='.'){
						error=true;
						cerr<<step<<")Illegal move; please enter a move:"<<endl;
						return;
					}
				}
				board->getBoard(to_x,to_y).setExistedSquare('B');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=true;
				all++;
				return;
			}
			tempy=to_y+1;
			if(my_x>to_x&&my_y>to_y){
				char name;
				for(int i=to_x+1;i<my_x;i++){
					name=board->getBoard(i,tempy++).getSquare()->getName();
					if(name!='.'){
						error=true;
						cerr<<step<<")Illegal move; please enter a move:"<<endl;
						return;
					}
				}
				board->getBoard(to_x,to_y).setExistedSquare('B');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=true;
				all++;
				return;
			}
			tempy=to_y+1;
			if(my_x<to_x&&my_y>to_y){
				char name;
				for(int i=to_x-1;i>my_x;i--){
					name=board->getBoard(i,tempy++).getSquare()->getName();
					if(name!='.'){
						error=true;
						cerr<<step<<")Illegal move; please enter a move:"<<endl;
						return;
					}
				}
				board->getBoard(to_x,to_y).setExistedSquare('B');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=true;
				all++;
				return;
			}
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
	}
	//a little bit comping of two rock and bishop and it called quenn we check if it can move or kill or not if not we get error cause we cant move it
	else if(name=='q'){
		char name=board->getBoard(to_x,to_y).getSquare()->getName();
		if(name=='p'||name=='r'||name=='n'||name=='b'||name=='q'||name=='k'){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		if(abs(to_x-my_x)==abs(to_y-my_y)){
			int tempy=my_y+1;
			if(my_x<to_x&&my_y<to_y){
				char name;
				for(int i=my_x+1;i<to_x;i++){
					name=board->getBoard(i,tempy++).getSquare()->getName();
					if(name!='.'){
						error=true;
						cerr<<step<<")Illegal move; please enter a move:"<<endl;
						return;
					}
				}
				board->getBoard(to_x,to_y).setExistedSquare('q');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=false;
				all++;
				return;
			}
				tempy=my_y+1;
				if(my_x>to_x&&my_y<to_y){
					char name;
					for(int i=my_x-1;i>to_x;i--){
						name=board->getBoard(i,tempy++).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=false;
					all++;
					return;
				}
				tempy=to_y+1;
				if(my_x>to_x&&my_y>to_y){
					char name;
					for(int i=to_x+1;i<my_x;i++){
						name=board->getBoard(i,tempy--).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=false;
					all++;
					return;
				}
				tempy=to_y+1;
				if(my_x<to_x&&my_y>to_y){
					char name;
					for(int i=to_x-1;i>my_x;i--){
						name=board->getBoard(i,tempy--).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=false;
					all++;
					return;
				}
		}
		else{
			if(my_y!=to_y&&my_x!=to_x){
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
				if(my_x>to_x){
					char name;
					for(int i=my_x-1;i>to_x;i--){
						name=board->getBoard(i,my_y).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=false;
					all++;
					return;

				}
				if(my_x<to_x){
					char name;
					for(int i=my_x+1;i<to_x;i++){
						name=board->getBoard(i,my_y).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=false;
					all++;
					return;

				}
				if(my_y<to_y){
					char name;
					for(int i=my_y+1;i<to_y;i++){
						name=board->getBoard(my_x,i).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=false;
					all++;
					return;

				}
				if(my_y>to_y){
					char name;
					for(int i=my_y-1;i>to_y;i--){
						name=board->getBoard(my_x,i).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=false;
					all++;
					return;
				}
				error=true;
				cerr<<step<<")Illegal move; please enter a move:"<<endl;
				return;
		}

	}
	//same as player 1 but for player 2
	else if(name=='Q'){
		char name=board->getBoard(to_x,to_y).getSquare()->getName();
		if(name=='P'||name=='R'||name=='N'||name=='B'||name=='Q'||name=='K'){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		if(abs(to_x-my_x)==abs(to_y-my_y)){
			int tempy=my_y+1;
			if(my_x<to_x&&my_y<to_y){
				char name;
				for(int i=my_x+1;i<to_x;i++){
					name=board->getBoard(i,tempy++).getSquare()->getName();
					if(name!='.'){
						error=true;
						cerr<<step<<")Illegal move; please enter a move:"<<endl;
						return;
					}
				}
				board->getBoard(to_x,to_y).setExistedSquare('Q');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				player1turn=true;
				all++;
				return;
			}
				tempy=my_y+1;
				if(my_x>to_x&&my_y<to_y){
					char name;
					for(int i=my_x-1;i>to_x;i--){
						name=board->getBoard(i,tempy++).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('Q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=true;
					all++;
					return;
				}
				tempy=to_y+1;
				if(my_x>to_x&&my_y>to_y){
					char name;
					for(int i=to_x+1;i<my_x;i++){
						name=board->getBoard(i,tempy--).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('Q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=true;
					all++;
					return;
				}
				tempy=to_y+1;
				if(my_x<to_x&&my_y>to_y){
					char name;
					for(int i=to_x-1;i>my_x;i--){
						name=board->getBoard(i,tempy--).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('Q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=true;
					all++;
					return;
				}
		}
		else{
			if(my_y!=to_y&&my_x!=to_x){
					error=true;
					cerr<<step<<")Illegal move; please enter a move:"<<endl;
					return;
				}
				if(my_x>to_x){
					char name;
					for(int i=my_x-1;i>to_x;i--){
						name=board->getBoard(i,my_y).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('Q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=true;
					all++;
					return;

				}
				if(my_x<to_x){
					char name;
					for(int i=my_x+1;i<to_x;i++){
						name=board->getBoard(i,my_y).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('Q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=true;
					all++;
					return;

				}
				if(my_y<to_y){
					char name;
					for(int i=my_y+1;i<to_y;i++){
						name=board->getBoard(my_x,i).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('Q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=true;
					all++;
					return;

				}
				if(my_y>to_y){
					char name;
					for(int i=my_y-1;i>to_y;i--){
						name=board->getBoard(my_x,i).getSquare()->getName();
						if(name!='.'){
							error=true;
							cerr<<step<<")Illegal move; please enter a move:"<<endl;
							return;
						}
					}
					board->getBoard(to_x,to_y).setExistedSquare('Q');
					board->getBoard(my_x,my_y).setExistedSquare('.');
					player1turn=true;
					all++;
					return;
				}
				error=true;
				cerr<<step<<")Illegal move; please enter a move:"<<endl;
				return;
		}
	}//we check if we can move the king to kill or not here we dont check if it is availbe move or not in other functions yes we do
	else if(name=='k'){
		char name=board->getBoard(to_x,to_y).getSquare()->getName();
		if(name=='p'||name=='r'||name=='n'||name=='b'||name=='q'||name=='k'){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		if(to_x==7&&to_y==2&&kingamoved==false&&player1acastling==true){
			if(board->getBoard(7,3).getSquare()->getName()!='.'||board->getBoard(7,1).getSquare()->getName()!='.'){
				error=true;
				cerr<<step<<")Illegal move; please enter a move:"<<endl;
				return;
			}
			else{
				board->getBoard(7,2).setExistedSquare('k');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				board->getBoard(7,0).setExistedSquare('.');
				board->getBoard(7,3).setExistedSquare('r');
				player1acastling=false;
				kingamoved=true;
				player1turn=false;
				return;
			}
		}
		if(to_x==7&&to_y==6&&kingamoved==false&&player1bcastling==true){
			if(board->getBoard(7,5).getSquare()->getName()!='.'||board->getBoard(7,6).getSquare()->getName()!='.'){
				error=true;
				cerr<<step<<")Illegal move; please enter a move:"<<endl;
				return;
			}
			else{
				board->getBoard(7,6).setExistedSquare('k');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				board->getBoard(7,7).setExistedSquare('.');
				board->getBoard(7,5).setExistedSquare('r');
				player1bcastling=false;
				kingamoved=true;
				player1turn=false;
				return;
			}
		}
		if(abs(my_x-to_x)==1&&abs(to_y-my_y)==1){
			board->getBoard(to_x,to_y).setExistedSquare('k');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			kingamoved=true;
			player1turn=false;
			return;
		}
		if(abs(my_x-to_x)==1&&my_y==to_y){
			board->getBoard(to_x,to_y).setExistedSquare('k');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			kingamoved=true;
			player1turn=false;
			return;
		}
		if(abs(to_y-my_y)==1&&my_x==to_x){
			board->getBoard(to_x,to_y).setExistedSquare('k');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			kingamoved=true;
			player1turn=false;
			return;
		}
		else{
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
	}//same thing
	else if(name=='K'){
		char name=board->getBoard(to_x,to_y).getSquare()->getName();
		if(name=='P'||name=='R'||name=='K'||name=='B'||name=='Q'||name=='K'){
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
		if(to_x==0&&to_y==2&&kingbmoved==false&&player2acastling==true){
			if(board->getBoard(0,3).getSquare()->getName()!='.'||board->getBoard(0,1).getSquare()->getName()!='.'){
				error=true;
				cerr<<step<<")Illegal move; please enter a move:"<<endl;
				return;
			}
			else{
				board->getBoard(0,2).setExistedSquare('K');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				board->getBoard(0,0).setExistedSquare('.');
				board->getBoard(0,3).setExistedSquare('R');
				player2acastling=false;
				kingbmoved=true;
				player1turn=true;
				return;
			}
		}
		if(to_x==0&&to_y==6&&kingbmoved==false&&player2bcastling==true){
			if(board->getBoard(0,5).getSquare()->getName()!='.'||board->getBoard(0,6).getSquare()->getName()!='.'){
				error=true;
				cerr<<step<<")Illegal move; please enter a move:"<<endl;
				return;
			}
			else{
				board->getBoard(0,6).setExistedSquare('K');
				board->getBoard(my_x,my_y).setExistedSquare('.');
				board->getBoard(0,7).setExistedSquare('.');
				board->getBoard(0,5).setExistedSquare('R');
				player2bcastling=false;
				kingbmoved=true;
				player1turn=true;
				return;
			}
		}
//		if(abs(my_x-to_x)==1&&abs(to_y-my_y)==1){
//			board->getBoard(to_x,to_y).setExistedSquare('K');
//			board->getBoard(my_x,my_y).setExistedSquare('.');
//			kingbmoved=true;
//			player1turn=true;
//			return;
//		}
		if(abs(my_x-to_x)==1&&abs(to_y-my_y)==1){
			board->getBoard(to_x,to_y).setExistedSquare('K');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			kingbmoved=true;
			player1turn=true;
			return;
		}
		if(abs(my_x-to_x)==1&&my_y==to_y){
			board->getBoard(to_x,to_y).setExistedSquare('K');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			kingbmoved=true;
			player1turn=true;
			return;
		}
		if(abs(to_y-my_y)==1&&my_x==to_x){
			board->getBoard(to_x,to_y).setExistedSquare('K');
			board->getBoard(my_x,my_y).setExistedSquare('.');
			kingbmoved=true;
			player1turn=true;
			return;
		}
		else{
			error=true;
			cerr<<step<<")Illegal move; please enter a move:"<<endl;
			return;
		}
	}
}
//check if draw by inusffiecient matrial
bool InsufficientMaterial(Board *board){
	int pawn=0;
	int Pawn=0;
	int Knight=0;
	int knight=0;
	int king=0;
	int King=0;
	int Bishop=0;
	int bishop=0;
	int Queen=0;
	int queen=0;
	int Rock=0;
	int rock=0;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			char name=board->getBoard(i,j).getSquare()->getName();
			if(name=='p'){
				pawn++;
			}
			if(name=='P'){
				Pawn++;
			}
			if(name=='r'){
				rock++;
			}
			if(name=='R'){
				Rock++;
			}
			if(name=='q'){
				queen++;
			}
			if(name=='Q'){
				Queen++;
			}
			if(name=='k'){
				king++;
			}
			if(name=='K'){
				King++;
			}
			if(name=='n'){
				knight++;
			}
			if(name=='N'){
				Knight++;
			}
			if(name=='b'){
				bishop++;
			}
			if(name=='B'){
				Bishop++;
			}
		}
	}
	if(King==1&&king==1&&Pawn==0&&pawn==0&&bishop==0&&Bishop==0&&Queen==0&&queen==0&&Knight==0&&knight==0&&Rock==0&&rock==0){
		return true;
	}
	if(King==1&&king==1&&Pawn==0&&pawn==0&&bishop==1&&Bishop==1&&Queen==0&&queen==0&&Knight==0&&knight==0&&Rock==0&&rock==0){
		return true;
	}
	if(King==1&&king==1&&Pawn==0&&pawn==0&&bishop==0&&Bishop==0&&Queen==0&&queen==0&&Knight==1&&knight==1&&Rock==0&&rock==0){
		return true;
	}
	return false;
}
int main() {
	//we make a game and we make true loop that every time player untill some 1 win or draws
	//and an input [3] but every time third one is impty untill promotions occurs
	Game game;
	string step;
	string input[3];
	Board *board=game.getBoard();
	Board spare;
	while(!end){
		input[2]=' ';
		//if erro dont print if not print the board and check every time if the game has finished by vairable check tro black player
		//and check to white player
		if(!error){
			game.GameBoard();
		}
		bool Check=CheckMate(board,true);
		if(Check){
			cout<<"Black wins with checkmate!"<<endl;
			return 0;

		}
		Check=CheckMate(board,false);
		if(Check){
			cout<<"White wins with checkmate!"<<endl;
			return 0;

		}
		//we check if it is drawn or not
		bool Insufficient=InsufficientMaterial(board);
		if(Insufficient){
			cout<<"The game is drawn due to insufficient material!"<<endl;
			return 0;
		}
		//player 1 turn
		if(player1turn==true){
			if(!error){
				cout<<all<<")Whites turn's, please enter a move:"<<endl;
			}
			//if cant move then it is draw to stalemate it doesnt matter from which player
			bool canmove=CanMove(board,true);
			if(canmove==false&&KingCanDie(board,true)==false){
				cout<<"The game is drawn due to stalemate!"<<endl;
				return 0;
			}
			getline(cin,step);
			if(!cin){return 0;}
			stringstream ss(step);
			int i=0;
			while(ss>>input[i]){
				i++;
			}
		//	if(player1turn){//was i==2
			if(legalmove(input[0])==false||legalmove(input[1])==false){
				error=true;
				cerr<<all<<") Invalid input; please enter a move:"<<endl;
				continue;
			}
			error=false;
			int my_y=input[0].c_str()[0]-65;
			int my_x=7-(input[0].c_str()[1]-49);
			int to_y=input[1].c_str()[0]-65;
			int to_x=7-(input[1].c_str()[1]-49);
			if(my_x==to_x&&my_y==to_y){
				error=true;
				cerr<<all<<")Illegal move; please enter a move:"<<endl;
				continue;
			}
			//possiblemove(char name,Board* board,int my_x,int my_y,int to_x,int to_y,int step)
			char name=board->getBoard(my_x,my_y).getSquare()->getName();
			if(name!='p'&&name!='r'&&name!='n'&&name!='b'&&name!='q'&&name!='k'){
				error=true;
				cerr<<all<<")Illegal move; please enter a move:"<<endl;
				continue;
			}
			spare.Same(*board);
			int spareall=all;
			possiblemove(name,board,my_x,my_y,to_x,to_y,all,input[2].c_str()[0]);
			bool check=KingCanDie(board,!player1turn);
			//if king can die then it is not good move we make the board like it was before
			if(check){
				board->Same(spare);
				error=true;
				all=spareall;
				player1turn=true;
				cerr<<all<<")Illegal move; please enter a move:"<<endl;
				continue;
			}
//			else{
//				error=true;
//				cerr<<all<<")Invalid input; please enter a move:"<<endl;
		}
		else {
			//same thing like second player
			if(!error){
				cout<<all<<")Black's turn, please enter a move:"<<endl;
			}
			bool canmove=CanMove(board,false);
			if(canmove==false&&KingCanDie(board,false)==false){
				cout<<"The game is drawn due to stalemate!"<<endl;
				return 0;
			}
			getline(cin,step);
			if(!cin){return 0;}
			stringstream ss(step);
			int i=0;
			while(ss>>input[i]){
				i++;
			}
			if(legalmove(input[0])==false||legalmove(input[1])==false){
				error=true;
				cerr<<all<<") Invalid input; please enter a move:"<<endl;
				continue;
			}
			//BENTAIM
			error=false;
			int my_y=input[0].c_str()[0]-65;
			int my_x=7-(input[0].c_str()[1]-49);
			int to_y=input[1].c_str()[0]-65;
			int to_x=7-(input[1].c_str()[1]-49);
			if(my_x==to_x&&my_y==to_y){
				error=true;
				cerr<<all<<")Illegal move; please enter a move:"<<endl;
				continue;
			}
			//possiblemove(char name,Board* board,int my_x,int my_y,int to_x,int to_y,int step)
			char name=board->getBoard(my_x,my_y).getSquare()->getName();
			if(name!='P'&&name!='R'&&name!='N'&&name!='B'&&name!='Q'&&name!='K'){
				error=true;
				cerr<<all<<")Illegal move; please enter a move:"<<endl;
				continue;
			}
			//cout<<all<<input[2].c_str()[0];
			spare.Same(*board);
			int spareall=all;
			possiblemove(name,board,my_x,my_y,to_x,to_y,all,input[2].c_str()[0]);
			bool check=KingCanDie(board,!player1turn);
			if(check){
				board->Same(spare);
				error=true;
				all=spareall;
				player1turn=false;
				cerr<<all<<")Illegal move; please enter a move:"<<endl;
				continue;
			}
		}
	}
	return 0;
}
