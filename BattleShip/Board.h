#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstring>


#pragma message ("Board object, piece & coordinate struct are defined.")
using namespace std;
//The result of the game
enum GameResult {
	Win,
	Lose,
	InProgress
};
//the result
enum MoveResult {
	Hit,
	Miss,
	InvalidMove,
	MoveRequest,
	Quit
};

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
//movement of pieces for piece placement
enum PieceMovement {
	Left = 1 << 0,
	Right = 1 << 1,
	Up = 1 << 2,
	Down = 1 << 3,
	Clockwise = 1 << 4,
	CounterClockwise = 1 << 5,
	ShipChange = 1 << 6
};
//Type of piece
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

	/*Move's*/

	//Moves pieces one up
	void shiftUp();
	//Moves piece one down
	void shiftDown();
	//Moves Piece one left
	void shiftLeft();
	//Moves Piece one right
	void shiftRight();
	//Rotates piece to the left
	void rotateLeft();
	//Rotates piece to the right
	void rotateRight();
	//Get's the position of each space the ship occupies
	vector<Coordinate> GetOccupiedSpace();
};
//A ten by ten array of pieces
struct Board {
	/*Default construcutor*/
	Board();
	/*Intializes the Board*/
	vector<Piece> BoardPieces;
	/*The collection of hits on this board*/
	vector<Coordinate> Hits; 
	/*Add's a hit*/
	void AddHit(Coordinate hit);
	/*Tell's you if the coordinate has already been hit*/
	MoveResult isHit(Coordinate hit);
	/*Get's the the GameState of the board*/
	GameResult BoardResult();
	/*Get's the piece at coordinate, if exists*/
	Piece *GetPieceAtCoordinate(Coordinate c);
	/*Valid place to put piece*/
	bool ValidPieceSpot(Piece loc);
	/*Next valid spot to put piece*/
	void NextValidPieceSpot(Piece *loc, PieceMovement pm);
	/*Validates if board is Allset*/
	bool BoardisValid();
	/*Get's the availability grid, used for various functions*/
	bool GetAvailabilityGrid(int (&grid)[10][10]);
	/*Clears the board*/
	void ClearBoard();
	/*Checks if piece already exists*/
	bool IsPieceOnBoard(PieceType pt);
	/*Deletes a piece from the board, if it exists*/
	bool PopPieceFromBoard(PieceType pt);
	/*Returns the index of the board piece*/
	int GetPieceOnBoard(PieceType pt);
	/*Deletes all instance data*/
	//void Delete();
};