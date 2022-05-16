/*
 * Game.cpp
 *
 *  Created on: Nov 24, 2020
 *      Author: win 10
 */

#include "Game.h"

Board* Game::getBoard() {
	return board;
}
void Game::GameBoard(){
	board->PrintBoard();
}
