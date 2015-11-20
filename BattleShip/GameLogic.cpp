#include "GameLogic.h"
#include <vector>
#include <thread>
#include <windows.h>

#pragma region GameLogicClass
Game::Game() {
	P1Board = new Board();
	P2Board = new Board();
}

void Game::SetP1(Player* p1) {
	P1 = p1;
}

void Game::SetP2(Player* p2) {
	P2 = p2;
}

void Game::Delete() {
	delete P1Board;
	delete P2Board;
}
//Implement core game loop here
GameResult Game::PlayGame() {
	//Verify both boards are good
	OutputDebugStringA("\nGame Thread: Starting");


	bool p1good = P1Board->BoardisValid();
	bool p2good = P2Board->BoardisValid();
	if (p1good && !p2good) {
		OutputDebugStringA("\nGame Thread: p1 win");
		return Win;
	}
	else if (!p1good && p2good) {
		OutputDebugStringA("\nGame Thread: p2 win");
		return Lose;
	}
	else if (!p1good && !p2good) {
		OutputDebugStringA("\nGame Thread: both fail");
		return Lose;
	}
	//Give each player access to the boards & hits;
	P1->setPlayerBoard(P1Board);
	P1->setHits(&P2Board->Hits);
	P2->setPlayerBoard(P2Board);
	P2->setHits(&P1Board->Hits);
	srand(time(NULL));
	//determines which player goes first
	//int fplayer = rand() % 2;
	OutputDebugStringA("\nGame Thread: Starting game threads");
	std::thread p1thread(&Player::StartGameLoop, P1, &p1chanin, &p1chanout);
	std::thread p2thread(&Player::StartGameLoop, P2, &p2chanin, &p2chanout);
	while ((P1Board->BoardResult() == InProgress) && (P2Board->BoardResult() == InProgress)) {
		//p1 is first
		//int start = fplayer;
		bool victory = false;
		bool p1gone = false, p2gone = false;
		//p1
		OutputDebugStringA("\nGame Thread: P1 gettin moverequest");
		//request p1 move
		p1chanin.put(MoveRequest);
		//process p1 move
		Coordinate c;
		p1chanout.get(c);
		OutputDebugStringA("\nGame Thread: P1 got c");
		//send back p1 move
		MoveResult mr = P2Board->isHit(c);
		while (mr == InvalidMove) {
			OutputDebugStringA("\nGame Thread: Coord is invalid");
			p1chanin.put(InvalidMove);
			p1chanout.get(c);
			mr = P2Board->isHit(c);
		}
		OutputDebugStringA("\nGame Thread: Sending back MR");
		p1chanin.put(mr);
		P2Board->AddHit(c);
		p1gone = true;
		//end P1 turn

		//request p2 move
		OutputDebugStringA("\nGame Thread: P2 getting moverequest");
		p2chanin.put(MoveRequest);
		//process p2 move
		Coordinate c2;
		p2chanout.get(c2);
		OutputDebugStringA("\nGame Thread: P2 got coord");
		//send back p1 move
		MoveResult mr2 = P2Board->isHit(c2);
		while (mr2 == InvalidMove) {
			OutputDebugStringA("\nGame Thread: P2 invalid move");
			p2chanin.put(InvalidMove);
			p2chanout.get(c2);
			mr2 = P1Board->isHit(c2);
		}
		OutputDebugStringA("\nGame Thread: P2 sending back MR");
		p2chanin.put(mr2);
		p2gone = true;
		P1Board->AddHit(c2);
		//end P2 turn
		victory = ((P1Board->BoardResult() == Lose) || (P2Board->BoardResult() == Lose));
		// = (start == 0) ? 1 : 0;
	}
	OutputDebugStringA("\nGame Thread: GAMEOVER");
	if (P1Board->BoardResult() == Lose) {
		p1chanin.close();
		p1chanout.close();
		p2chanin.close();
		p2chanout.close();
		p1thread.join();
		p2thread.join();
		return Lose;
		//} else if(P2Board->BoardResult == Lose){
	}
	else {
		p1chanin.close();
		p1chanout.close();
		p2chanin.close();
		p2chanout.close();
		p1thread.join();
		p2thread.join();
		return Win;
	}
}
Board* Game::GetP1Board() {
	return P1Board;
}

Board* Game::GetP2Board() {
	return P2Board;
}
#pragma endregion
#pragma region PlayerCode
Player::Player() {}

void Player::setPlayerBoard(Board *pb) {
	PlayerBoard = pb;
}

void Player::StartGameLoop(Channel<MoveResult> *chanin, Channel<Coordinate> *chanout) {
	MoveResult mr;
	while (true) {
		chanin->get(mr);
		while (mr == MoveRequest || mr == InvalidMove) {
			chanout->put(MakeMove());
			chanin->get(mr);
		}
		if (mr == Quit) {
			break;
		}
		ProcessMove(mr);
	}
	return;
}

void Player::setHits(vector<Coordinate> *oh) {
	opponentHits = oh;
}
#pragma endregion

#pragma region UserPlayerCode
UserPlayer::UserPlayer() {}
#pragma region UserPlayerCode
UserPlayer::UserPlayer(Channel<MoveResult> *ccout, Channel<Coordinate> *ccin) {
	chanin = ccin;
	chanout = ccout;
}
void UserPlayer::PlacePieces() {
	return;
}
Coordinate UserPlayer::MakeMove() {
	OutputDebugStringA("\nUserPlayer Thread: Getting move");
	Coordinate c;
	chanin->get(c);
	return c;
}
void UserPlayer::ProcessMove(MoveResult mr) {
	OutputDebugStringA("\nUserPlayer Thread: Processing move");
	chanout->put(mr);
}
#pragma endregion
