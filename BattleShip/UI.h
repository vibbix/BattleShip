#pragma once
#include "GameLogic.h"
#include "AI.h"
#include "curses.h"

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
	UI(UI &&){}
	//Starts the UI Thread
	void StartUI();
	//Starts the title screen
	void DisplayTitleScreen();
	//Displays the main menu, 1 to quit, 0 to play
	int StartMenu();
	//Select the difficulty
	Difficulty SelectDifficulty();
	//Places pieces for player board, 0 for stop, 1 for continue
	int PlacePieces(Board *b);
	//Play Game
	GameResult PlayGame();
private:
	Difficulty CAI;
	Board *UserBoard;
	Board *AIBoard;
	Game CurrentGame;
	//Render's piece to grid
	void RenderToGrid(WINDOW* wnd, Piece pc, char* l = "X");
	void RenderToGrid(WINDOW* wnd, vector<Coordinate> ls, char* l = "X");
	int game;
};
bool ConfirmDialog(char* text);

void SetColor(short num, short text, short backround, bool isInit=true);
void SetColor(short num);
void SetColor(WINDOW* win, short num, short text, short backround, bool isInit = true);
void SetColor(WINDOW* win, short num);