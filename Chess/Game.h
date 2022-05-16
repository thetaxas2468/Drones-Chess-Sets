/*
 * Game.h
 *
 *  Created on: Nov 24, 2020
 *      Author: win 10
 */

#ifndef GAME_H_
#define GAME_H_
#include "Board.h"
//a game that has a board that has 64 squares and each square has a type of piece
class Game {
public:
	//making new board becuase every game has it own board and deletting it usingg the destructor to stop the data usage after done
	Game():board(new Board){}
	~Game(){delete board;}
	//printing gameboard same as board
	void GameBoard();
	//getting existed board that is already in the game by pointer to it
	Board* getBoard();
private:
	//board pointed to board that is in the game
	Board *board;
};

#endif /* GAME_H_ */
