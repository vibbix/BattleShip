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
	//Initliazes the game.
	Game();
	//Deletes all game instance information.
	void Delete();
	//Get's player 1's board
	Board *GetP1Board();
	//Get's player 2's board
	Board *GetP2Board();
	//Set player 1
	void SetPlayer1(Player *p1);
	//Set player 2
	void SetPlayer2(Player *p2);
	//Get's the game result from the perspective of player 1
	GameResult PlayGame();
	//Get's the global game result
	GameResult CurrentGameStatus();
private:
	//Player 1's board
	Board *P1Board;
	//Player 2's board
	Board *P2Board;
	//Hit's made by P1 to P2
	vector<Coordinate> P1Hits;
	//Hit's made by P2 to P1
	vector<Coordinate> P2Hits;
	//Player 1 
	Player *P1;
	//Player 2
	Player *P2;
};

//Player Interface
class Player {
public:
	//Game object uses this to get the move for the player
	virtual Coordinate GetMove() = 0;
	//Games class passes the move result to the player
	virtual void TakeMoveResult(MoveResult mr) = 0;

	virtual void DoTurn();

	//Get's the result from the perspective of the player
	virtual GameResult GetResult() = 0;
	//Places pieces for user
	virtual void PlacePieces()=0;
	void setPlayerBoard(Board *pb);
	void setHits(vector<Coordinate> *oh, vector<Coordinate> *ph);
protected:
	Board *PlayerBoard;
	//Hit's made by this player to the opponent
	vector<Coordinate> *hitsToOpponent;
	//Hit's made by opponent to this player
	vector<Coordinate> *hitsToPlayer;
};

//User player is directly controlled from the UI
class UserPlayer : public Player {
public:
	Coordinate GetMove();
	//takes the moveresult from the gameclass
	void TakeMoveResult(MoveResult mr);
	//Get's the game result from the point of this player
	GameResult GetResult();
	//Place pieces
	void PlacePieces();
};