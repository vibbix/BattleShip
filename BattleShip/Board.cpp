#include "Board.h"
#include "GameLogic.h"
#include <iostream>
#include <time.h>
using namespace std;
//Initlialize the board
#pragma region BoardCode
Board::Board() {
	Hits = vector<Coordinate>();
	BoardPieces = vector<Piece>();
}

bool Board::AddHit(Coordinate hit) {
	//check if valid
	if (hit.x < 0 || hit.x > 9 || hit.y < 0 || hit.y > 9) {
		return false;
	}
	//check if duplicate
	for (uint8_t i = 0; i < Hits.size(); i++) {
		Coordinate coord = Hits.at(i);
		if (coord.x == hit.x && coord.y == hit.y) {
			return false;
		}
	}
	Hits.push_back(hit);
	return true;
}

MoveResult Board::isHit(Coordinate hit) {
	//check if valid coord
	if (hit.x < 0 || hit.x > 9 || hit.y < 0 || hit.y > 9) {
		return InvalidMove;
	}
	//check if duplicate
	for (uint8_t i = 0; i < Hits.size(); i++) {
		Coordinate coord = Hits.at(i);
		if (coord.x == hit.x && coord.y == hit.y) {
			return InvalidMove;
		}
	}
	int available[10][10];
	bool check = GetAvailabilityGrid(available);
	if (available[hit.x][hit.y] != 0) {
		//Check if it will sink ships
		return Hit;
	}
	return Miss;
}

//TO-DO: FINISH THIS LATER
bool Board::WillSinkShip(Coordinate c){
	//For each piece, get all hits.
	//if the total amount of missing hits is 1,
	//check if that hit is equal to parameter c
	vector<Coordinate> ls;
	for (auto pc : BoardPieces) {
		ls = pc.GetOccupiedSpace();
		int chit = 0;
		for (Coordinate h : Hits) {
			break;
		}
		break;
	}
	return false;

}
GameResult Board::BoardResult() {
	//Get all possible occupied space
	int available[10][10];
	vector<Coordinate> ls;
	//Get's all pieces
	for (auto pc : BoardPieces) {
		ls = pc.GetOccupiedSpace();
		for (int i = 0; i < getPieceLength(pc.Type); i++) {
			available[ls[i].x][ls[i].y] -= 1;
		}
	}
	for (auto hit : Hits) {
		available[hit.x][hit.y] -= 1;
	}

	int hcount = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (available[i][j] == -2) {
				hcount++;
			}
		}
	}
	if (hcount == 17) {
		return Lose;
	}
	//get's all hits
	return InProgress;
}

bool Board::ValidPieceSpot(Piece loc) {
	//get's all current positions on board
	//Get all possible occupied space
	//Get availability grid
	int available[10][10];
	bool check = GetAvailabilityGrid(available);
	if (check == false) {
		//delete available;
		return false;
	}
	vector<Coordinate> ls;
	ls = loc.GetOccupiedSpace();
	//check if each occupied space is valid
	for (int i = 0; i < getPieceLength(loc.Type); i++) {
		//if out of bounds instantly false
		if (ls[i].x < 0 || ls[i].x > 9 || ls[i].y < 0 || ls[i].y > 9) {
			return false;
		}
		//if spot is already taken, return false
		if (available[ls[i].x][ls[i].y] != 0) {
			return false;
		}
	}
	return true;
}

void Board::NextValidPieceSpot(Piece *loc, PieceMovement pm) {
	int ox = loc->CenterAxis.x, oy = loc->CenterAxis.y;
	Orientation orig= loc->orientation;
	vector<Coordinate> ls;
	ls = loc->GetOccupiedSpace();
	int available[10][10];
	bool attempted = false;
	bool check = GetAvailabilityGrid(available);
	int attempts = 0;
	//loop until good place found, or until no longer in bounds
	while ((loc->CenterAxis.x >= 0 && loc->CenterAxis.x <= 9 && loc->CenterAxis.y >= 0 && loc->CenterAxis.y <= 9) && attempts < 20) {
		bool isValid = true;
		switch (pm)
		{
		case Left:
			loc->shiftLeft();
			break;
		case Right:
			loc->shiftRight();
			break;
		case Up:
			loc->shiftUp();
			break;
		case Down:
			loc->shiftDown();
			break;
		case Clockwise:
			loc->rotateRight();
			break;
		case CounterClockwise:
			loc->rotateLeft();
			break;
		case ShipChange:
			//Means ship type changed
			//don't wanna be stuck in an infinite loop if a bad parameter is passed
			//Attempt 
			if (!attempted) {
				attempted = true;
				break;
			}
			loc->rotateLeft();
			break;
		default:
			if (!attempted) {
				attempted = true;
				break;
			}
			loc->rotateLeft();
			break;
		}
		for (int i = 0; i < getPieceLength(loc->Type); i++) {
			//tests if each occupied space is valid
			if (ls[i].x < 0 || ls[i].x > 9 || ls[i].y < 0 || ls[i].y > 9) {
				isValid = false;
				break;
			//checks if space is already in the way
			} else if (available[ls[i].x][ls[i].y] == -1) {
				isValid = false;
				break;
			}
		}
		if (isValid) {
			return;
		}
		attempts++;
	}
	//check original position to see if it works
	bool isValid = true;
	loc->CenterAxis.x = ox;
	loc->CenterAxis.y = oy;
	loc->orientation = orig;
	for (int i = 0; i < getPieceLength(loc->Type); i++) {
		if (ls[i].x < 0 || ls[i].x > 9 || ls[i].y < 0 || ls[i].y > 9) {
			isValid = false;
			break;
		} else if (available[ls[i].x][ls[i].y] == -1) {
			isValid = false;
			break;
		}
	}
	if (isValid) {
		return;
	}
	//apply transform once
	switch (pm)
	{
	case Clockwise:
		loc->rotateRight();
		break;
	case CounterClockwise:
		loc->rotateLeft();
		break;
	default:
		break;
	}
	//expand out until space is found
	int rattempts = 0;
	srand(time(NULL));
	while (!isValid) {
		int newx = rand() % 10;//0 to 9
		int newy = rand() % 10;//0 to 9
		if (newx < 0 || newx > 9 || newy < 0 || newy > 9) {
			break;
		}
		loc->CenterAxis.x = newx;
		loc->CenterAxis.y = newy;
		ls = loc->GetOccupiedSpace();
		int ecount = 0;
		for (int r = 0; r < 3; r++) {
			for (int i = 0; i < getPieceLength(loc->Type); i++) {
				if (ls[i].x < 0 || ls[i].x > 9 || ls[i].y < 0 || ls[i].y > 9) {
					ecount++;
					break;
				}
				else if (available[ls[i].x][ls[i].y] == -1) {
					ecount++;
					break;
				}
			}
			if (ecount == 0) {
				return;
			}
			loc->rotateRight();
			ecount = 0;
		}
		rattempts++;
		if (rattempts > 200) {
			break;
		}
	}
	return;
}

bool Board::BoardisValid(){
	//All pieces are in use
	//all pieces are on valid tiles
	//no pieces overlap each other
	//Easy way to check this: use availability grid, and count the number of occurances for -1
	int available[10][10];
	bool check = GetAvailabilityGrid(available);
	if (!check) {
		return false;
	}
	int occurances = 0;
	for (int i = 0; i < 10; i++) {//i -> x or rows
		for (int j = 0; j < 10; j++) { //j -> y or columns
			if (available[i][j] == -1) {
				occurances++;
			}
		}
	}
	//17 being the sum total of each type of ships pegs
	if (occurances == 17) {
		return true;
	}
	return false;

}

void Board::ClearBoard() {
	BoardPieces.clear();
	Hits.clear();
}

Piece *Board::GetPieceAtCoordinate(Coordinate c) {
	if (c.x < 0 || c.x > 9 || c.y < 0 || c.y > 9) {
		return NULL;
	}
	vector<Coordinate> ls;
	//Get's all pieces
	//for (auto pc : BoardPieces) {
	for (uint8_t i = 0; i < BoardPieces.size(); i++){
		Piece pc = BoardPieces.at(i);
		ls = pc.GetOccupiedSpace();
		for (int i = 0; i < getPieceLength(pc.Type); i++) {
			if (ls[i].x == c.x && ls[i].y == c.y) {
				return &BoardPieces[i];
			}
		}
	}
	return NULL;
}
//MAKE SURE THIS THINGS WORKS!!!!!!!
bool Board::GetAvailabilityGrid(int(&grid)[10][10]) {
	//normalize grid
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			grid[i][j] = 0;
		}
	}
	vector<Coordinate> ls;
	//Get's all pieces
	for (auto pc : BoardPieces) {
		ls = pc.GetOccupiedSpace();
		for (int i = 0; i < getPieceLength(pc.Type); i++) {
			if (ls[i].x < 0 || ls[i].x > 9 || ls[i].y < 0 || ls[i].y > 9) {
				return false;
			}
			grid[ls[i].x][ls[i].y] = -1;
		}
	}
	return true;
}

bool Board::IsPieceOnBoard(PieceType pt) {
	for (auto cp : BoardPieces) {
		if (cp.Type == pt) {
			return true;
		}
	}
	return false;
}

bool Board::PopPieceFromBoard(PieceType pt) {
	for (uint8_t i = 0; i < BoardPieces.size(); i++) {
		if (BoardPieces.at(i).Type == pt) {
			//switchs matching element with the last item
			if (i != BoardPieces.size() - 1) {
				std::swap(BoardPieces.at(i), BoardPieces.at(BoardPieces.size() - 1));
			}
			BoardPieces.pop_back();
		}
	}
	return false;
}

int Board::GetPieceOnBoard(PieceType pt) {
	for (uint8_t i = 0; i < BoardPieces.size(); i++) {
		if (BoardPieces.at(i).Type == pt) {
			return (int)i;
		}
	}
	return -1;
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

void Piece::shiftRight() {
	if (CenterAxis.y == 9) {
		CenterAxis.y = 0;
		return;
	}
	CenterAxis.y += 1;
}

void Piece::shiftLeft() {
	if (CenterAxis.y == 0) {
		CenterAxis.y = 9;
		return;
	}
	CenterAxis.y -= 1;
}

void Piece::shiftUp() {
	if (CenterAxis.x == 0) {
		CenterAxis.x = 9;
		return;
	}
	CenterAxis.x -= 1;
}

void Piece::shiftDown() {
	if (CenterAxis.x == 9) {
		CenterAxis.x = 0;
		return;
	}
	CenterAxis.x += 1;
}

vector<Coordinate> Piece::GetOccupiedSpace() {
	PieceType pt = Type;
	int len = getPieceLength(pt);
	int xinc = 0;
	int yinc = 0;
	int cx = 0;
	int cy = 0;
	vector<Coordinate> space = vector<Coordinate>(len);
	//create shift values
	switch (orientation)
	{
	case ZeroDegrees:
		yinc = -1;
		break;
	case NinetyDegrees:
		xinc = 1;
		break;
	case OneHundredEightyDegrees:
		yinc = 1;
		break;
	case TwoHundredSeventyDegrees:
		xinc = -1;
		break;
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
