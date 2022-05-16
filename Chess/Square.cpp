/*
 * Square.cpp
 *
 *  Created on: Nov 24, 2020
 *      Author: win 10
 */

#include "Square.h"
#include "Piece.h"
#include <iostream>
Square::Square(){
	piece=new Piece('.');
}
//Square::Square(const Square &other){}//:x(other.x),y(other.y),piece(other.piece.getName()){}


//Square& Square::operator=(const Square &other) {
////	if(this==&other){
////		return *this;
////	}
////	else{
////		this->piece.name=other.piece.getName();
////		this->x=other.x;
////		this->y=other.y;
////		return *this;
////	}
//}

void Square::setSquare(Piece *piece) {
	this->piece=piece;
}

Piece* Square::getSquare() {
	return this->piece;
}

void Square::clear() {
	delete piece;
	this->piece=NULL;
}

void Square::setExistedSquare(char name) {
	delete piece;
	this->piece=new Piece(name);
}

