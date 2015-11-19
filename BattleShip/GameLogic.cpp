#include "GameLogic.h"
#include <vector>
#pragma region GameLogicClass
Game::Game() {
	P1Board = new Board();
	P2Board = new Board();
	P1Hits = vector<Coordinate>();
	P2Hits = vector<Coordinate>();
}

void Game::Delete() {
	delete P1Board;
	delete P2Board;
	P1Hits.clear();
	P2Hits.clear();
}
//Implement core game loop here
GameResult Game::PlayGame() {
	return Win;
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

void Player::StartGameLoop(Channel<MoveResult> chanin, Channel<Coordinate> chanout) {
	while (true) {
		MoveResult mr;
		chanin.get(mr);
		if (mr == Quit) {
			break;
		}
		while (mr == MoveRequest || mr == InvalidMove) {
			chanout.put(MakeMove());
			chanin.get(mr);
		}
		chanin.get(mr);
		if (mr == Quit) {
			break;
		}
		ProcessMove(mr);
	}
}

void Player::setHits(vector<Coordinate> *oh, vector<Coordinate> *ph) {
	opponentHits = oh;
	playerHits = ph;
}
#pragma endregion
