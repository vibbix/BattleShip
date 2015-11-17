#pragma once
#include "Board.h"
#include "AI.h"
#include <vector>
using namespace std;
enum GameResult {
	Win,
	Lose,
	InProgress
};
enum MoveResult {
	Hit,
	Miss
};
//Core Game Logic
class Game {
public:
	Game();
	//Place pieces
	/*Actions*/
	//Initializes the game, UI, AI, etc.
	Game(Difficulty AIDifficulty);
	//Deletes all game instance information.
	void Delete();
	//Get's player 1's board
	Board *GetP1Board();
	//Get's player 2's board
	Board *GetP2Board();
	//Get's the game result from the perspective of player 1
	GameResult PlayGame();
private:
	Board *P1Board;
	Board *P2Board;
	//Hit's made by P1 to P2
	vector<Coordinate> P1Hits;
	//Hit's made by P2 to P1
	vector<Coordinate> P2Hits;
	//Core game AI
	AI gameAI;
};

//Player Interface
class Player {
public:
	//Game object uses this to get the move for the player
	virtual Coordinate GetMove() = 0;
	//Get's the move result from GetMove()
	virtual MoveResult GetMoveResult(Coordinate c) = 0;
	//Get's the result from the perspective of the player
	virtual GameResult GetResult() = 0;
	void setPlayerBoard(Board *pb);
	void setHits(vector<Coordinate> *oh, vector<Coordinate> *ph);
protected:
	Board *PlayerBoard;
	//Hit's made by this player to the opponent
	vector<Coordinate> *opponentHits;
	//Hit's made by opponent to this player
	vector<Coordinate> *playerHits;
};