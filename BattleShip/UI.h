#pragma once
#include "AI.h"
#include "GameLogic.h"
/*Implements the UI
-board display
-main menu
-board functions
	-View user board
	-Place pieces
	-View enemy board(show only hit/miss pieces)
	*/
class UI {
public:
	UI();
	//Starts the UI Thread
	void StartUI();
	//Starts the title screen
	void DisplayTitleScreen();
	//Displays the main menu, 1 to quit, 0 to play
	int StartMenu();
	//Select the difficulty
	Difficulty SelectDifficulty();
	//Places pieces for player board
	Board *PlacePieces();
	//Play Game
	GameResult PlayGame();
private:
	AI OpponentAI;
	Game CurrentGame;
};
void SetColor(short num, short text, short backround);
void SetColor(short num);