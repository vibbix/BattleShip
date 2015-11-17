#include "Board.h"
#include "AI.h"

AI::AI() {

}



AI::AI(Difficulty intel, Board *b) {
	aiIntel = intel;
}

Coordinate AI::GetMove() {
	if (aiIntel == Easy) {
		return EasyAI();
	}
	else if (aiIntel == Medium) {
		return MediumAI();
	}
	else {
		return AdvanceAI();
	}
	return Coordinate{ 0,0 };
}

void AI::PlacePieces() {
	
}
#pragma region AILogic
Coordinate AI::EasyAI() {
	return Coordinate{ 0,0 };
}

Coordinate AI::MediumAI() {
	return Coordinate{ 0,0 };
}

Coordinate AI::AdvanceAI() {
	return Coordinate{ 0,0 };
}
#pragma endregion