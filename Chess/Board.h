/*
 * Board.h
 *
 *  Created on: Nov 23, 2020
 *      Author: win 10
 */


#ifndef BOARD_H_
#define BOARD_H_
#include "Square.h"
#include <iostream>
//board class that is in the game that has 64 square and each square has a piece
using namespace std;
class Board {
public:
	//we making consturctor to start the 64 sqare and non of them has new to use the destructor
	Board();
	~Board();
	//printing board
	void PrintBoard();
	//get square in place x y
	Square& getBoard(int x,int y);
	//make this board same as other board
	void Same(Board &other);
//	Board(const Board &other);
//	Board& operator=(const Board &other);
private:
	//64 square that is in the game and each one has different type like K k Q q ....
	Square board[8][8];
};

#endif /* BOARD_H_ */
