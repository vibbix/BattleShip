#include "GameLogic.h"

Game::Game() {
	gameAI = AI();
}

Game::Game(Difficulty AIDifficulty){
	//Initlialize boards
	EnemyBoard = new Board();
	PlayerBoard = new Board();
	//Initliaze AI
	gameAI = AI(AIDifficulty, EnemyBoard);
}
Board *Game::GetEnemyBoard() {
	return EnemyBoard;
}
Board *Game::GetPlayerBoard(){
	return PlayerBoard;
}

void Game::Delete() {
	delete PlayerBoard;
	delete EnemyBoard;
}