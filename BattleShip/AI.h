#pragma once
#include "Board.h"
//Game Difficulty
enum Difficulty {
	//Just random hits
	Easy,
	//Random Hits with attempt to sink ships knowing previous positions
	Medium,
	//Knows players ships ahead of time
	Hard
};
class AI {
public:
	AI();
	//Creates the AI instance
	AI(Difficulty Intelligence, Board *EnemyBoard);
	//Makes a move
	void MakeMove();
	void PlacePieces();
private:
	/* http://www.datagenetics.com/blog/december32011/ */
	//EasyAI, just random hits
	void EasyAI();
	Difficulty aiIntel;
	Board *AIBoard;
	Coordinate *Hits;
	//MediumAI, uses random hits + direction attempting
	void MediumAI();
	Coordinate current;//Current Coordinate
	int AvailableDirections; //[N, E, S, W] -> [8, 4, 2, 1]
	int lastDirection;
	//AdvanceAI, uses probability
	void AdvanceAI();
	
};