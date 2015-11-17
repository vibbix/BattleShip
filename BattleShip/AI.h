#pragma once
#include "Board.h"
#include "GameLogic.h"
//Game Difficulty
enum Difficulty {
	//Just random hits
	Easy,
	//Random Hits with attempt to sink ships knowing previous positions
	Medium,
	//Knows players ships ahead of time
	Hard
};
class AI : public Player {
public:
	AI();
	//Creates the AI instance
	AI(Difficulty intel, Board *b);
	//Get's the move
	Coordinate GetMove();
	GameResult GetResult();
	void PlacePieces();
private:
	/* http://www.datagenetics.com/blog/december32011/ */
	//EasyAI, just random hits
	Coordinate EasyAI();
	Difficulty aiIntel;
	//MediumAI, uses random hits + direction attempting
	Coordinate MediumAI();
	Coordinate current;//Current Coordinate
	int AvailableDirections; //[N, E, S, W] -> [8, 4, 2, 1]
	int lastDirection;
	//AdvanceAI, uses probability
	Coordinate AdvanceAI();
	
};