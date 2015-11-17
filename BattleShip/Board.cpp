#include "Board.h"
#include "GameLogic.h"
#include <iostream>
using namespace std;
//Initlialize the board
#pragma region BoardCode
Board::Board() {
	Hits = new vector<Coordinate>();
	BoardPieces = vector<Piece>();
}

void Board::AddHit(Coordinate hit) {
	Hits->push_back(hit);
}

bool Board::IsHit(Coordinate hit) {
	for (int i = 0; i < Hits->size; i++) {
		Coordinate coord = Hits->at(i);
		if (coord.x == hit.x && coord.y == hit.y) {
			return true;
		}
	}
	return false;
}

GameResult Board::BoardResult() {
	//Get all possible 
}
#pragma endregion

#pragma region PieceCommands
Piece::Piece() {
	isValid = false;
}

int getPieceLength(PieceType pt) {
	switch (pt)
	{
	case AircraftCarrier:
		return 5;
	case Battleship:
		return 4;
	case Submarine:
		return 3;
	case Cruiser:
		return 3;
	case Destroyer:
		return 2;
	default:
		return 0;
	}
}

void Piece::rotateLeft() {
	if (orientation == ZeroDegrees) {
		orientation = TwoHundredSeventyDegrees;
		return;
	}
	orientation = static_cast<Orientation>(orientation - 1);
}

void Piece::rotateRight() {
	if (orientation == TwoHundredSeventyDegrees) {
		orientation = ZeroDegrees;
		return;
	}
	orientation = static_cast<Orientation>(orientation + 1);
}

void Piece::shiftDown() {
	CenterAxis.y += 1;
}

void Piece::shiftUp() {
	CenterAxis.y -= 1;
}

void Piece::shiftLeft() {
	CenterAxis.x -= 1;
}

void Piece::shiftRight() {
	CenterAxis.x += 1;
}

Coordinate *Piece::GetOccupiedSpace() {
	PieceType pt = Type;
	int len = getPieceLength(pt);
	int xinc = 0;
	int yinc = 0;
	int cx = 0;
	int cy = 0;
	Coordinate *space = new Coordinate[len];

	//create shift values
	switch (orientation)
	{
	case ZeroDegrees:
		yinc = 1;
	case NinetyDegrees:
		xinc = 1;
	case OneHundredEightyDegrees:
		yinc = -1;
	case TwoHundredSeventyDegrees:
		xinc = -1;
	default:
		break;
	}
	//Add coordinate for each occupied space
	cx = CenterAxis.x;
	cy = CenterAxis.y;
	space[0] = CenterAxis;
	for (int i = 1; i < len; i++) {
		space[i] = Coordinate{cx += xinc, cy += yinc };
	}
	return space;
}
#pragma endregion
