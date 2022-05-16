/*
 * Square.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: win 10
 */

#include "Square.h"



Square& Square::operator =(const Square& other) {
	this->planes = other.planes;
	return *this;
}
Square::Square(const Square& other) {
	this->planes = other.planes;
}

Square& Square::operator ++() {
	this->planes++;
	return *this;
}
const Square Square::operator ++(int) {
	const Square temp = *this;
	this->planes++;
	return temp;
}

Square& Square::operator --() {
	this->planes--;
	if (this->planes < 0) {
		this->planes = 0;
		return *this;
	}
	return *this;
}

const Square Square::operator --(int) {
	const Square temp = *this;
	this->planes--;
	if (this->planes < 0) {
		this->planes = 0;
		return temp;
	}
	return temp;
}
