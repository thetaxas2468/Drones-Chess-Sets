/*
 * Pieces.h
 *
 *  Created on: Nov 24, 2020
 *      Author: win 10
 */

#ifndef PIECE_H_
#define PIECE_H_
//piece class that is in each square we start their name by entering to its constructor and it has no def constructor
class Piece {
public:
	enum{BlackKing='K',BlackQueen='Q',BlackRook='R',BlackBishop='B',BlackKnight='N',BlackPawn='P',
		 WhiteKing='k',WhiteQueen='q',WhiteRook='r',WhiteBishop='b',WhiteKnight='n',WhitePawn='p',
		 Empty='.'
	};
	Piece(char name):name(name){}
	char getName();
private:
	//char feild like pPqQ....
	 char name;
};

#endif /* PIECE_H_ */
