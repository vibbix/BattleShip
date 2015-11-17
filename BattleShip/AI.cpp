#include "Board.h"
#include "AI.h"

AI::AI() {

}

AI::AI(Difficulty intel, Board *b) {
	aiIntel = intel;
	AIBoard = b;
}

Coordinate AI::GetMove() {
	/*if (aiIntel == Easy) {
		EasyAI();
	}
	else if (aiIntel == Medium) {
		MediumAI();
	}
	else {
		AdvanceAI();
	}*/
	return Coordinate{ 0,0 };
}

void AI::PlacePieces() {
	
}