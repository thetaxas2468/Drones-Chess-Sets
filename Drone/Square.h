/*
 * Square.h
 *
 *  Created on: Dec 13, 2020
 *      Author: win 10
 */

#ifndef SQUARE_H_
#define SQUARE_H_
//Square header that has some methods that square had and each square can have how many planes it wants
class Square {
private:
	int planes;
public:
	//constructor regular one each square with 0 planes cause they is no planes yet destruct empty cause they is no planes
	//operator++ and -- by making one pre and one post
	Square() :planes(0) {}
	Square(const Square& other);
	~Square() {}
	Square& operator=(const Square& other);
	const Square operator++(int);
	Square& operator++();
	Square& operator--();
	const Square operator--(int);
	int getPlanes()const { return planes; }
	void setPlanes(int planes) { this->planes = planes; }
};

#endif /* SQUARE_H_ */
