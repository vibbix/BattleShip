#include "Board.h"
#include "AI.h"

AI::AI() {
	aiIntel = Easy;
}

AI::AI(Difficulty intel) {
	aiIntel = intel;
}

Coordinate AI::MakeMove() {
	/*if (aiIntel == Easy) {
		return EasyAI();
	}
	else if (aiIntel == Medium) {
		return MediumAI();
	}
	else {
		return AdvanceAI();
	}*/
	return Coordinate{ 0,0 };
}

Coordinate AI::GetRandomPoint(bool wparity) {
	//required methods:
	//getsunkships()
	int ny = 0, nx = 0;
	if (wparity) {
		ny = rand() % 10;
		nx = (ny % 2 == 0) ? 2 * (rand() % 5) : 2 * (rand() % 5) + 1;
	}
	else {
		ny = rand() % 10;
		nx = rand() % 10;
	}
	//if odd row, column must be even
	//if even row column must be odd
	Coordinate c{ nx,ny };
	bool isValidMove = false;
	while(!isValidMove){
		//for each hit, check if it's already been attempted
		isValidMove = true;
		for (int i = 0; i < opponentHits->size(); i++) {
			Coordinate h = opponentHits->at(i);
			if (h.x == c.x && h.y == c.y) {
				isValidMove = false;
				break;
			}
		}
		if (!isValidMove) {
			if (wparity) {
				ny = rand() % 10;
				nx = (ny % 2 == 0) ? 2 * (rand() % 5) : 2 * (rand() % 5);
			}
			else {
				ny = rand() % 10;
				nx = rand() % 10;
			}
		}
	}
	opponentHits->push_back(c);
};
Coordinate AI::GetProbabilityPoint() {

};
Coordinate AI::GetHunterPoint() {

};


void AI::PlacePieces() {
	
}