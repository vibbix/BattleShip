#pragma once
#include "Board.h"
#include "AI.h"
enum GameResult {
	Win,
	Lose
};
class Game {
public:
	Game();
	//Place pieces
	/*Actions*/

	//Initializes the game, UI, AI, etc.
	Game(Difficulty AIDifficulty);
	//Deletes all game instance information.
	void Delete();
	Board *GetPlayerBoard();
	Board *GetEnemyBoard();
private:
	Board *PlayerBoard;
	Board *EnemyBoard;
	AI gameAI;
};