#include "curses.h"
#include "UI.h"
#include "GameLogic.h"


#pragma region MenuCode


void UI::DisplayTitleScreen() {
	WINDOW* wnd = initscr();
	curs_set(0);
	//checking for colors
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		return;
	}
	start_color();

	//Title screen
	mvwprintw(wnd, 4, 15, "                             /|");
	mvwprintw(wnd, 5, 15, "                            | |");
	mvwprintw(wnd, 6, 15, "         _________/--|_|/___|_|____\\");
	mvwprintw(wnd, 7, 15, "___---__/0 0 0 0 |ZX__/_/_/_/__|------\\______________");
	mvwprintw(wnd, 8, 15, "|0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0  /");
	mvwprintw(wnd, 9, 15, "|________________________________________________/");
	//ASCII-ART name
	mvwprintw(wnd, 11, 18, "   ___       _   _   _      __ _     _       ");
	mvwprintw(wnd, 12, 18, "  / __\\ __ _| |_| |_| | ___/ _\\ |__ (_)_ __  ");
	mvwprintw(wnd, 13, 18, " /__\\/// _` | __| __| |/ _ \\ \\| '_ \\| | '_ \\ ");
	mvwprintw(wnd, 14, 18, "/ \\/  \\ (_| | |_| |_| |  __/\\ \\ | | | | |_) |");
	mvwprintw(wnd, 15, 18, "\\_____/\\__,_|\\__|\\__|_|\\___\\__/_| |_|_| .__/ ");
	mvwprintw(wnd, 16, 18, "                                      |_|    ");
	mvwprintw(wnd, 18, 27, "Press any key to continue...");
	mvwprintw(wnd, 24, 32, "2015 Mark Beznos");
	getch();
	refresh();
	endwin();
	return;
}

int UI::StartMenu() {
	bool PlayGame = false;
	int current = 0;
	WINDOW* wnd = initscr();
	curs_set(0);
	keypad(wnd, TRUE);
	mvwprintw(wnd, 5, 18, "   ___       _   _   _      __ _     _       ");
	mvwprintw(wnd, 6, 18, "  / __\\ __ _| |_| |_| | ___/ _\\ |__ (_)_ __  ");
	mvwprintw(wnd, 7, 18, " /__\\/// _` | __| __| |/ _ \\ \\| '_ \\| | '_ \\ ");
	mvwprintw(wnd, 8, 18, "/ \\/  \\ (_| | |_| |_| |  __/\\ \\ | | | | |_) |");
	mvwprintw(wnd, 9, 18, "\\_____/\\__,_|\\__|\\__|_|\\___\\__/_| |_|_| .__/ ");
	mvwprintw(wnd, 10, 18, "                                      |_|    ");
	mvwprintw(wnd, 24, 32, "2015 Mark Beznos");
	while (true) {
		//clear existing text
		SetColor(2, COLOR_WHITE, COLOR_BLACK);
		mvwprintw(wnd, 15, 30, "                   ");
		mvwprintw(wnd, 17, 35, "                    ");
		//print current text
		mvwprintw(wnd, 15, 35, "Play Game");
		mvwprintw(wnd, 17, 38, "Quit");
		SetColor(1, COLOR_RED, COLOR_BLACK);
		if (current == 0) {
			mvwprintw(wnd, 15, 33, ">>");
			mvwprintw(wnd, 15, 44, "<<");
		}
		else {
			mvwprintw(wnd, 17, 36, ">>");
			mvwprintw(wnd, 17, 42, "<<");
		}
		//
		char ckey = getch();
		//if (ckey == KEY_UP || ckey == KEY_DOWN)
		if (ckey == '\x3' || ckey == '\x2') {
			current = (current == 0) ? 1 : 0;
		}
		//ckey == KEY_ENTER
		else if (ckey == '\n') {
			endwin();
			return current;
		}
	}
}

Difficulty UI::SelectDifficulty() {
	int selected = 0;
	WINDOW* wnd = initscr();
	keypad(wnd, TRUE);
	SetColor(1, COLOR_WHITE, COLOR_BLACK);
	mvwprintw(wnd, 24, 32, "2015 Mark Beznos");
	mvwprintw(wnd, 2, 20, "Select a difficulty(use arrow keys & enter):");
	while (true) {
		SetColor(1, COLOR_WHITE, COLOR_BLACK);
		//Clear lines
		mvwprintw(wnd, 4, 20, "                          ");
		mvwprintw(wnd, 7, 20, "                          ");
		mvwprintw(wnd, 10, 20, "                          ");
		//Print
		mvwprintw(wnd, 4, 39, "Easy");
		mvwprintw(wnd, 5, 33, "Just random hits");
		mvwprintw(wnd, 7, 38, "Medium");
		mvwprintw(wnd, 8, 22, "Random hits with intent to finish ships");
		mvwprintw(wnd, 10, 39, "Hard");
		mvwprintw(wnd, 11, 25, "Advance AI that will challenge you");
		//Print cursor
		SetColor(2, COLOR_RED, COLOR_BLACK);
		if (selected == 0) {
			mvwprintw(wnd, 4, 37, ">>");
			mvwprintw(wnd, 4, 43, "<<");
		}
		else if (selected == 1) {
			mvwprintw(wnd, 7, 36, ">>");
			mvwprintw(wnd, 7, 44, "<<");
		}
		else {
			mvwprintw(wnd, 10, 37, ">>");
			mvwprintw(wnd, 10, 43, "<<");
		}
		//update cursor position
		char ckey = getch();
		//ckey == up arrow
		if (ckey == '\x3') {
			selected = (selected == 0) ? 2 : selected - 1;
		}
		//ckey == downarrow
		else if (ckey == '\x2') {
			selected = (selected == 2) ? 0 : selected + 1;
		}
		//ckey == KEY_ENTER
		else if (ckey == '\n') {
			endwin();
			return static_cast<Difficulty>(selected);
		}
	}
}

UI::UI()
{
	game = 0;
}

void UI::StartUI() {
	DisplayTitleScreen();
	int result = StartMenu();
	//Means quit game
	if (result == 1) {
		return;
	}
	Difficulty aidiff = SelectDifficulty();
	//CurrentGame = Game();
	PlacePieces(CurrentGame.GetP1Board());
	return;
}
//Finish later
GameResult UI::PlayGame() {
	return InProgress;
}

int UI::PlacePieces(Board *b) {
	//Create windows
	//navigate piece placement using arrow keys
	//Select 'W' & 'S' to select which ship you want to select
	//user 'Q' & 'E' to rotate the ship CCW & CW
	//Select delete over a selected ship to remove it from the
	initscr();
	if (!b->BoardisValid()) {
		b->ClearBoard();
	}
	//new win(int height, int width, int starty, int startx)
	//gameboard
	WINDOW *winboard = newwin(23, 24, 1, 1);
	//selection * instructions
	//WINDOW *wnd = subwin(mwnd, 25, 52, 0, 25);
	WINDOW *wnd = newwin(25, 52, 0, 25);
	wborder(winboard, '|', '|', '-', '-', '+', '+', '+', '+');
	noecho();
	//cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);
	SetColor(winboard, 1, COLOR_WHITE, COLOR_BLACK, false); //Text
	SetColor(winboard, 2, COLOR_BLUE, COLOR_BLACK); //Water
	SetColor(winboard, 3, COLOR_RED, COLOR_BLACK);	//placed ships
	SetColor(winboard, 4, COLOR_YELLOW, COLOR_BLACK);//Highligted ships
	SetColor(winboard, 5, COLOR_GREEN, COLOR_BLACK); //???
	SetColor(wnd, 1, COLOR_WHITE, COLOR_BLACK, false); //Text
	SetColor(wnd, 2, COLOR_YELLOW, COLOR_BLACK); //Highlighted text
	SetColor(wnd, 3, COLOR_RED, COLOR_BLACK); //Cursor
	int selected = 0; //Currently selected ship [0 to 4]
	Piece tempship = Piece();
	tempship.piecelength = 0;
	tempship.CenterAxis.x = 8;
	tempship.CenterAxis.y = 8;
	tempship.orientation = ZeroDegrees;
	tempship.isValid = true;
	while (true) {
		//render current view
		SetColor(winboard, 1);
		//draw backround of battle square
		mvwprintw(winboard, 1, 4, "A B C D E F G H I J");
		for (int i = 0; i < 22; i+=2) {
			SetColor(winboard, 2);
			string gletter = std::to_string(i/2);
			SetColor(winboard, 2);
			mvwprintw(winboard, i + 3, 4, "0 0 0 0 0 0 0 0 0 0");
			SetColor(winboard, 1);
			if (i % 2 == 0) {
				SetColor(winboard, 1);
				mvwprintw(winboard, i + 1, 1, gletter.c_str());
			}
		}
		//Draw ships
		SetColor(winboard, 3);
		for (auto ship : b->BoardPieces) {
			vector<Coordinate> ls;
			ls = ship.GetOccupiedSpace();
			for (int i = 0; i < getPieceLength(ship.Type); i++) {
				mvwprintw(winboard, ls[i].x + 3, ls[i].y + 4, "X");
			}
			
		}
		//Print ship names
		SetColor(wnd, (short)1, COLOR_WHITE, COLOR_BLACK);
		(b->IsPieceOnBoard(AircraftCarrier)) ? SetColor(wnd, 2) : SetColor(wnd, 1);
		mvwprintw(wnd, 1, 15, "Aircraft Carrier");
		mvwprintw(wnd, 2, 20, "XXXXX");
		(b->IsPieceOnBoard(Battleship)) ? SetColor(wnd, 2) : SetColor(wnd, 1);
		mvwprintw(wnd, 4, 18, "BattleShip");
		mvwprintw(wnd, 5, 21, "XXXX");
		(b->IsPieceOnBoard(Submarine)) ? SetColor(wnd, 2) : SetColor(wnd, 1);
		mvwprintw(wnd, 7, 18, "Submarine");
		mvwprintw(wnd, 8, 21, "XXX");
		(b->IsPieceOnBoard(Cruiser)) ? SetColor(wnd, 2) : SetColor(wnd, 1);
		mvwprintw(wnd, 10, 19, "Cruiser");
		mvwprintw(wnd, 11, 21, "XXX");
		(b->IsPieceOnBoard(Destroyer)) ? SetColor(wnd, 2) : SetColor(wnd, 1);
		mvwprintw(wnd, 13, 18, "Destroyer");
		mvwprintw(wnd, 14, 22, "XX");
		mvwprintw(wnd, 16, 6, "Navigate piece placement using arrow keys");
		mvwprintw(wnd, 17, 10, "Use 'W' & 'S' to select the ship");
		mvwprintw(wnd, 18, 3, "Use 'Q' & 'E' to rotate the ship CCW & CW");
		mvwprintw(wnd, 19, 1, "Press 'Del' over a ship to remove it from the grid");
		mvwprintw(wnd, 20, 9, "Press enter to add ship/proceed");
		refresh();
		wrefresh(winboard);
		wrefresh(wnd);
		
		//what to print
		//Cursor
		bool highlightship = false;
		vector<Coordinate> ls;
		PieceType cpt = static_cast<PieceType>(selected);
		//if already placed
			//turn the temp ship to "invalid" so it won't be rendered.
			//render the ship using "yellow" hit markers
			//break;
		//if the current piece isn't this type, make it so
			//find a valid spot for it
		if (b->IsPieceOnBoard(cpt)) {
			tempship.isValid = false;
			highlightship = true;
			break;
		}
		else if(tempship.Type != cpt) {
			tempship.Type = cpt;
			//Let's hope this doesnt crash anything at runtime
			b->NextValidPieceSpot(&tempship, ShipChange);
		}
		//Render the current ship, or highlight
		if (highlightship) {
			if (!b->IsPieceOnBoard(cpt)) {
				break;
			}
			SetColor(winboard, 4);
			int pos = b->GetPieceOnBoard(cpt);
			if (pos == -1) {
				break;
			}
			ls = b->BoardPieces.at(pos).GetOccupiedSpace();
			SetColor(wnd, 2);
			for (int i = 0; i < getPieceLength(cpt); i++) {
				mvwprintw(winboard, ls[i].x + 3, ls[i].y + 4, "X");
			}
			
		}
		else {
			if (b->IsPieceOnBoard(cpt)) {
				break;
			}
			SetColor(winboard, 4);
			int pos = b->GetPieceOnBoard(cpt);
			if (pos == -1) {
				break;
			}
			ls = b->BoardPieces.at(pos).GetOccupiedSpace();
			for (int i = 0; i < getPieceLength(cpt); i++) {
				mvwprintw(winboard, ls[i].x + 3, ls[i].y + 4, "O");
			}
			
		}
		//paint cursor
		SetColor(wnd, 3);
		switch (static_cast<PieceType>(selected))
		{
		case AircraftCarrier:
			mvwprintw(wnd, 1, 13, ">>");
			mvwprintw(wnd, 1, 20, "<<");
			break;
		case Battleship:
			mvwprintw(wnd, 3, 13, ">>");
			mvwprintw(wnd, 3, 20, "<<");
			break;
		case Submarine:
			mvwprintw(wnd, 5, 13, ">>");
			mvwprintw(wnd, 5, 20, "<<");
			break;
		case Cruiser:
			mvwprintw(wnd, 7, 13, ">>");
			mvwprintw(wnd, 7, 20, "<<");
			break;
		case Destroyer:
			mvwprintw(wnd, 9, 13, ">>");
			mvwprintw(wnd, 9, 20, "<<");
			break;
		default:
			break;
		}
		char ckey = getch();
		switch (ckey)
		{
		//Attempt to move piece up
		case KEY_UP:
			if (tempship.isValid) {
				b->NextValidPieceSpot(&tempship, Up);
			}
			break;
		//Attempt to move piece down
		case KEY_DOWN:
			if (tempship.isValid) {
				b->NextValidPieceSpot(&tempship, Down);
			}
			break;
		//Attempt to move piece down
		case KEY_LEFT:
			if (tempship.isValid) {
				b->NextValidPieceSpot(&tempship, Left);
			}
			break;
		//Attempt to move piece Right
		case KEY_RIGHT:
			if (tempship.isValid) {
				b->NextValidPieceSpot(&tempship, Right);
			}
			break;
		//Attempt to rotate right
		case 'q':
			if (tempship.isValid) {
				b->NextValidPieceSpot(&tempship, CounterClockwise);
			}
			break;
		//Attempt to rotate left
		case 'e':
			if (tempship.isValid) {
				b->NextValidPieceSpot(&tempship, CounterClockwise);
			}
			break;
		//Move cursor up
		case 'w':
			(selected == 0) ? (selected = 4) : (selected--);
			//setup ship info
			//piece already exists
			if (b->IsPieceOnBoard(static_cast<PieceType>(selected))) {
				tempship.isValid = false;
			}
			else
			{
				//doesnt exist
				tempship.isValid = true;
				b->NextValidPieceSpot(&tempship, ShipChange);
			}
			break;
		//Move cursor down
		case 's':
			(selected == 4) ? (selected = 0) : (selected++);
			//setup ship info
			if (b->IsPieceOnBoard(static_cast<PieceType>(selected))) {
				tempship.isValid = false;
			}
			else
			{
				//doesnt exist, yet
				tempship.isValid = true;
				b->NextValidPieceSpot(&tempship, ShipChange);
			}
			break;
		/*
		Attempt to place piece.
		If already selected, ignore.
		if all pieces placed, start game
		*/
		case KEY_ENTER:
			//already piece on board
			if (b->IsPieceOnBoard(static_cast<PieceType>(selected))) {
				if (b->BoardisValid()) {
					bool result = ConfirmDialog("Would you like to continue?");
					if (result) {
						return 1;
					}
					else {
						break;
					}
				}
			}
			//Add to board if possible
			//ship is valid, not a duplicate, 
			else {
				if (b->ValidPieceSpot(tempship)) {
					b->BoardPieces.push_back(tempship);
				}
			}
			break;
		//If piece is already placed down, remove it
		case KEY_DL:
			if (b->IsPieceOnBoard(static_cast<PieceType>(selected))) {
				int pos = b->GetPieceOnBoard(static_cast<PieceType>(selected));
				if (pos == -1) {
					break;
				}
				Piece px = b->BoardPieces.at(pos);
				if (b->ValidPieceSpot(px)) {
					tempship.CenterAxis = px.CenterAxis;
					tempship.orientation = px.orientation;
					tempship.isValid = true;
					tempship.Type = px.Type;
					b->PopPieceFromBoard(static_cast<PieceType>(selected));
				}
			}
			break;
		//clears board, and returns to main menu
		case KEY_EXIT:
		{
				bool result = ConfirmDialog("Would you like to quit?");
				if (result) {
					b->ClearBoard();
					return 0;
				}
				else {
					break;
				}
				//Confirm dialog!
				break;
			}
		default:
			break;
		}
	}
	endwin();
	return 1;
}
#pragma endregion


bool ConfirmDialog(char* text) {
	int s = 0;
	WINDOW *winexit = newwin(5, 15, 20, 20);
	SetColor(winexit, 1, COLOR_BLACK, COLOR_WHITE, false);
	SetColor(winexit, 2, COLOR_RED, COLOR_WHITE);
	int c = 0;
	while (true) {
		SetColor(winexit, 1);
		mvwprintw(winexit, 1, 4, text);
		mvwprintw(winexit, 1, 4, "Yes");
		mvwprintw(winexit, 1, 9, "No");
		wrefresh(winexit);
		//render cursor
		char cu = getch();
		if (cu == KEY_LEFT || cu == KEY_RIGHT) {
			s = (s) ? false : true;
		}
		else if (cu == '/n') {
			//selected no
			if (s == 1) {
				delwin(winexit);
				return true;
			}
			//selected yes
			else {
				delwin(winexit);
				return false;
			}
		}
	}
}
#pragma region ColorCommands
void SetColor(short num, short text, short backround, bool isInit) {
	if (has_colors() == FALSE)
	{
		return;
	}
	if (!isInit) {
		start_color();
	}
	init_pair(num, text, backround);
	attron(COLOR_PAIR(num));
}
void SetColor(short num) {
	if (has_colors() == FALSE)
	{
		return;
	}
	attron(COLOR_PAIR(num));
}

void SetColor(WINDOW* win, short num, short text, short backround, bool isInit) {
	if (has_colors() == FALSE)
	{
		return;
	}
	if (!isInit) {
		start_color();
	}
	init_pair(num, text, backround);
	wattron(win, COLOR_PAIR(num));
}
void SetColor(WINDOW* win, short num) {
	if (has_colors() == FALSE)
	{
		return;
	}
	wattron(win, COLOR_PAIR(num));
}
#pragma endregion

