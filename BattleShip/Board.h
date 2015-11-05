#pragma once
#include <string>
#include <vector>
using namespace std;
//Piece orientation
enum Orientation {
	//Piece is straight up... i.e. [0,0], [0,1], [0,2]
	ZeroDegrees,
	//Piece is right of its center... i.e. [0,0], [1,0], [2,0]
	NinetyDegrees,
	//Piece is straight down... i.e [0,0], [0, -1], [0, -2]
	OneHundredEightyDegrees,
	//Piece is left of its center... i.e. [0,0], [-1,0], [-2, 0]
	TwoHundredSeventyDegrees
};
struct Coordinate {
	//Position width wise
	int x;
	//Position height wise
	int y;
};
//A single gamepiece
struct Piece {
	//List of places piece occupies
	Coordinate CenterAxis;
	//Length of piece
	int piecelength;
	//Orientation of piece
	Orientation orientation;
	//Piece name.
	string pieceName;
};
//A ten by ten array of pieces
struct Board {
	Piece **GameBoard;//[10][10]...
	Coordinate *Hits; 
};
