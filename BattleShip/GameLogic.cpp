#include "GameLogic.h"
#include <vector>
#pragma region GameLogicClass
Game::Game() {
	gameAI = AI();
}

Game::Game(Difficulty AIDifficulty) {
	//Initlialize boards
	P1Board = new Board();
	P2Board = new Board();

	//Initliaze AI
	gameAI = AI(AIDifficulty, P2Board);
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

}
#pragma endregion

#pragma region PlayerCode
void Player::setPlayerBoard(Board *pb) {
	PlayerBoard = pb;
}

void Player::initHits() {
	opponentHits = vector<Coordinate>();
	playerHits = vector<Coordinate>();
}
#pragma endregion
