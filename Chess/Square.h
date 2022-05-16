/*
 * Square.h
 *
 *  Created on: Nov 24, 2020
 *      Author: win 10
 */

#ifndef SQUARE_H_
#define SQUARE_H_
#include "Piece.h"
//a board has 64 squares that is used to make squares different from each other
class Square {
public:
	//constructor that has new and desturcot that delete
	Square();
	//Square(const Square& other);
	~Square(){delete piece;}
	//we set existed all square to another
	void setSquare(Piece *piece);
	//we set existed square piece name to another name
	void setExistedSquare(char name);
	//we get what in the square which is pointed to piece
	Piece* getSquare();
	//clearing the square
	void clear();
private:
	Piece *piece;
};

#endif /* SQUARE_H_ */
