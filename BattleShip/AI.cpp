#include "Board.h"
#include "AI.h"
#include <Windows.h>

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
	OutputDebugStringA("AI Thread: Getting move/n");
	return GetRandomPoint();
}

Coordinate AI::EasyAI() {
	return GetRandomPoint(false);
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
	return c;
	//opponentHits->push_back(c);
};
//finish later
Coordinate AI::GetProbabilityPoint() {
	return Coordinate{ 0,0 };
};
//finish later
Coordinate AI::GetHunterPoint() {
	return Coordinate{ 0,0 };
};
//FINISH THIS FUNCTION
void AI::ProcessMove(MoveResult mr) {
	OutputDebugStringA("AI Thread: Processing move/n");
	return;
}

void AI::PlacePieces() {
	PieceType pt[5];
	srand(time(NULL));
	for (int i = 0; i < 5; i++) {
		pt[i] = static_cast<PieceType>(i);
		int x = rand() % 10;
		Sleep(1);
		int y = rand() % 10;
		Piece pc = Piece();
		pc.Type = pt[i];
		pc.CenterAxis = Coordinate{ 0,0 };
		int rotate = rand() % 2;
		if (rotate == 1) {
			pc.rotateRight();
		}
		PlayerBoard->NextValidPieceSpot(&pc, Right);
		while (!PlayerBoard->ValidPieceSpot(pc)) {
			PlayerBoard->NextValidPieceSpot(&pc, Clockwise);
		}
		PlayerBoard->BoardPieces.push_back(pc);
	}
	while (!PlayerBoard->BoardisValid()) {
		for (auto pc : PlayerBoard->BoardPieces) {
			PlayerBoard->NextValidPieceSpot(&pc, Clockwise);
			Sleep(1);
		}
	}

}