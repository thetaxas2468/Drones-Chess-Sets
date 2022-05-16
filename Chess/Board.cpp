/*
 * Board.cpp
 *
 *  Created on: Nov 23, 2020
 *      Author: win 10
 */

#include "Board.h"
#include "Piece.h"
//start the squares in the board
Board::Board(){
	board[0][0].setSquare(new Piece('R'));
	board[0][1].setSquare(new Piece('N'));
	board[0][2].setSquare(new Piece('B'));
	board[0][3].setSquare(new Piece('Q'));
	board[0][4].setSquare(new Piece('K'));
	board[0][5].setSquare(new Piece('B'));
	board[0][6].setSquare(new Piece('N'));
	board[0][7].setSquare(new Piece('R'));
	board[7][0].setSquare(new Piece('r'));
	board[7][1].setSquare(new Piece('n'));
	board[7][2].setSquare(new Piece('b'));
	board[7][3].setSquare(new Piece('q'));
	board[7][4].setSquare(new Piece('k'));
	board[7][5].setSquare(new Piece('b'));
	board[7][6].setSquare(new Piece('n'));
	board[7][7].setSquare(new Piece('r'));
	for(int i=0;i<8;i++){
		board[6][i].setSquare(new Piece('p'));
	}
	for(int i=0;i<8;i++){
		board[1][i].setSquare(new Piece('P'));
	}
//	board[6][3].setSquare(new Piece('p'));
//	board[6][4].setSquare(new Piece('p'));
//	board[1][4].setSquare(new Piece('q'));
//	board[3][4].setSquare(new Piece('P'));
//	board[1][4].setSquare(new Piece('.'));
//	board[6][5].setSquare(new Piece('.'));
//	board[6][6].setSquare(new Piece('.'));
//	board[4][6].setSquare(new Piece('p'));
//	board[5][5].setSquare(new Piece('P'));
}
Board::~Board() {
}
//print the board
void Board::PrintBoard() {
	for(int i=0;i<8;i++){
		cout<<8-i<<"  ";
		for(int j=0;j<8;j++){
			cout<<board[i][j].getSquare()->getName()<<" ";
		}
		cout<<endl;
	}
	cout<<"   A B C D E F G H"<<endl;
}
//getting the square x y
Square& Board::getBoard(int x,int y) {
	return board[x][y];
}
//
//Board::Board(const Board &other) {
//	// TODO Auto-generated constructor stub
//
//}
//
//copying other board to this baord so both are the same but each one is different by reference
void Board::Same(Board &other) {
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			this->getBoard(i,j).setExistedSquare(other.getBoard(i,j).getSquare()->getName());
		}
	}
}
//
