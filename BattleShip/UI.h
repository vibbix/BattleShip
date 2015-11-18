#pragma once
#include "GameLogic.h"
#include "AI.h"

#pragma message ("UI object is defined")
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
	void PlacePieces(Board *b);
	//Play Game
	GameResult PlayGame();
private:
	Board *UserBoard;
	Board *AIBoard;
	Game CurrentGame;
};
void SetColor(short num, short text, short backround);
void SetColor(short num);