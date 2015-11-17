#include "GameLogic.h"
#include <vector>
#pragma region GameLogicClass
Game::Game() {
	P1Board = new Board();
	P2Board = new Board();
}

Board *Game::GetP1Board() {
	return P2Board;
}
Board *Game::GetP2Board() {
	return P1Board;
}

void Game::Delete() {
	delete P1Board;
	delete P2Board;
}

void Game::SetPlayer1(Player *p1) {
	P1 = p1;
}

void Game::SetPlayer2(Player *p2) {
	P2 = p2;
}

GameResult Game::PlayGame() {
	P1->PlacePieces();
	P2->PlacePieces();
	while (true) {
		Coordinate P1move = P1->GetMove();
		P1Hits.push_back(P1move);
		if (GetResult() != InProgress) {
			if (GetResult() == Lose) {
				return Lose;
			}
			else {
				return Win;
			}
		}

	}
}

GameResult Game::GetResult() {
	if(P1->)
}
#pragma endregion

#pragma region PlayerCode
void Player::setPlayerBoard(Board *pb) {
	PlayerBoard = pb;
}

void Player::setHits(vector<Coordinate> *oh, vector<Coordinate> *ph) {
	hitsToOpponent = oh;
	hitsToPlayer = ph;
}
#pragma endregion


#pragma region UserPlayer
Coordinate UserPlayer::GetMove() {

}
void UserPlayer::TakeMoveResult(MoveResult mr){
}
GameResult UserPlayer::GetResult(){

}
void UserPlayer::PlacePieces() {

}

#pragma endregion
