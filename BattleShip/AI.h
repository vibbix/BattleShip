#pragma once
#include "GameLogic.h"
#include "Board.h"
#pragma message ("AI object is defined")
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
	AI(Difficulty intel);
	//Inherited functions:

	Coordinate MakeMove();
	//
	void PlacePieces();

	void ProcessMove(MoveResult mr);
private:
	/* http://www.datagenetics.com/blog/december32011/ */
	//EasyAI, just random hits
	Coordinate EasyAI();
	Difficulty aiIntel;
	//MediumAI, uses random hits + direction attempting
	//void MediumAI();
	Coordinate current;//Current Coordinate
	int AvailableDirections; //[N, E, S, W] -> [8, 4, 2, 1]
	int lastDirection;
	//AdvanceAI, uses probability
	//void AdvanceAI();
	//Stage 1:get point to target
	Coordinate GetRandomPoint(bool wparity = false);
	Coordinate GetProbabilityPoint();
	Coordinate GetHunterPoint();
	//

};