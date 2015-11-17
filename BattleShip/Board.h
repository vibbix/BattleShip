#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
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
enum PieceType {
	//A single 1x5 unit, Radiation level .5
	AircraftCarrier,
	//A single 1x4 unit, radiation level .4
	Battleship,
	//A single 1x3 unit, radiation level .15
	Submarine,
	//A single 1x3 unit, radiation level .3
	Cruiser,
	//A single 1x2 unit, radiation level .25
	Destroyer
};
//Get's the length of a gamepiece
int getPieceLength(PieceType pt);
struct Coordinate {
	//Position width wise, A-J
	int x;
	//Position height wise, 1-10
	int y;
	static friend Coordinate CoordinateFromString(string str);
};
//A single gamepiece
struct Piece {
	//Default constructor
	Piece();
	//Set if valid location
	bool isValid;
	//List of places piece occupies
	Coordinate CenterAxis;
	//Length of piece
	int piecelength;
	//Orientation of piece
	Orientation orientation;
	//Piece name.
	string Name;
	//Piece type
	PieceType Type;
};
//A ten by ten array of pieces
struct Board {
	//Default construcutor
	Board();
	//Intializes the Board
	Piece **GameBoard;
	//The collection of hits
	vector<Coordinate> Hits; 
	//Add's a hit
	void AddHit(Coordinate hit);
	//Tell's you if the coordinate has already been hit
	bool IsHit(Coordinate hit);
	//Deletes all instance data
	void Delete();
};

