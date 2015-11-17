#include "Board.h"
#include "AI.h"

AI::AI() {

}

AI::AI(Difficulty Intelligence, Board *EnemyBoard) {
	aiIntel = Intelligence;
	AIBoard = EnemyBoard;
}

void AI::MakeMove() {
	/*if (aiIntel == Easy) {
		EasyAI();
	}
	else if (aiIntel == Medium) {
		MediumAI();
	}
	else {
		AdvanceAI();
	}*/
}

void AI::PlacePieces() {
	
}