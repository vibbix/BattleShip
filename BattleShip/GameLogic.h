#pragma once
#include "Board.h"
#include <vector>
#include "channel.h"

#pragma message ("Game & player objects are defined")
using namespace std;

//Core Game Logic
class Game {
public:
	//Place pieces
	/*Actions*/
	//Initializes the game, UI, AI, etc.
	Game();
	//Fix's weird deleted fucntion error
	//Game(Game &&) {}
	//Game(const Game&) = default;
	Game(const Game&) = default;
	Game& operator=(const Game&) = default;
	//Get's the game result from the perspective of player 1
	GameResult PlayGame();
	//Deletes all game instance information.
	void Delete();
	//Get P1 board
	Board* GetP1Board();
	//Get P2 board
	Board* GetP2Board();
private:
	Board *P1Board;
	Board *P2Board;
	//Hit's made by P1 to P2
	vector<Coordinate> P1Hits;
	//Hit's made by P2 to P1
	vector<Coordinate> P2Hits;
	//channels for players
	Channel<MoveResult> p1chanin, p2chanin;
	Channel<Coordinate> p1chanout, p2chanout;
};

//Player Interface
class Player {
public:
	Player();
	//Thread indepedent game loop
	void StartGameLoop(Channel<MoveResult> chanin, Channel<Coordinate> chanout);
	//Place Pieces on board, verifies all is good
	virtual void PlacePieces() = 0;
	virtual Coordinate MakeMove() = 0;
	virtual void ProcessMove(MoveResult) = 0;
	//Set's the players board
	void setPlayerBoard(Board *pb);
	//Set's the hit vectors up
	void setHits(vector<Coordinate> *oh, vector<Coordinate> *ph);
	//Set channels
	void setChannels(Channel<MoveResult> cin, Channel<Coordinate> cout);
protected:
	//This Player's board
	Board *PlayerBoard;
	//Hit's made by this player to the opponent
	vector<Coordinate> *opponentHits;
	//Hit's made by opponent to this player
	vector<Coordinate> *playerHits;
};