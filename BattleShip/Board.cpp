#include "Board.h"

Board::Board() {

}

void Board::AddHit(Coordinate hit) {
	
}

bool Board::IsHit(Coordinate hit) {
	return false;
}

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