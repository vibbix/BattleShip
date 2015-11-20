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
	CAI = SelectDifficulty();
	//CurrentGame = Game();
	PlacePieces(CurrentGame.GetP1Board());
	return;
}
//Finish later
GameResult UI::PlayGame() {
	//create two grids: Player & enemy
	Channel<MoveResult> *mr = new Channel<MoveResult>();
	Channel<Coordinate> *cs = new Channel<Coordinate>();
	CurrentGame.SetP1(&UserPlayer(mr, cs));
	CurrentGame.SetP2(&AI(CAI));
	initscr();
	WINDOW *PlayerBoard = newwin(23, 24, 1, 1);
	WINDOW *AIBoard = newwin(23, 24, 1, 30);
	WINDOW *EntryArea = newwin(3, 3, 15, 20);
	SetColor(PlayerBoard, 1, COLOR_WHITE, COLOR_BLACK);
	SetColor(AIBoard, 1, COLOR_WHITE, COLOR_BLACK);
	SetColor(PlayerBoard, 2, COLOR_RED, COLOR_BLACK);
	SetColor(AIBoard, 2, COLOR_RED, COLOR_BLACK);
	wborder(PlayerBoard, '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(AIBoard, '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(EntryArea, '|', '|', '-', '-', '+', '+', '+', '+');
	noecho();
	//cbreak();
	curs_set(0);
	UserPlayer up;
	keypad(stdscr, TRUE);
	std::thread cg(&Game::PlayGame, &CurrentGame);
	while (true) {
		RenderToGrid(PlayerBoard, CurrentGame.GetP1Board()->Hits);
		RenderToGrid(AIBoard, CurrentGame.GetP2Board()->Hits);
		//render playerboard
		mvwprintw(PlayerBoard, 1, 4, "A B C D E F G H I J");
		for (int i = 0; i < 22; i += 2) {
			SetColor(PlayerBoard, 2);
			string gletter = std::to_string(i / 2);
			SetColor(PlayerBoard, 2);
			mvwprintw(PlayerBoard, i + 3, 4, "0 0 0 0 0 0 0 0 0 0");
			SetColor(PlayerBoard, 1);
			if (i % 2 == 0) {
				SetColor(PlayerBoard, 1);
				mvwprintw(PlayerBoard, i + 3, 1, gletter.c_str());
			}
		}
		//render ai board
		mvwprintw(AIBoard, 1, 4, "A B C D E F G H I J");
		for (int i = 0; i < 22; i += 2) {
			SetColor(AIBoard, 2);
			string gletter = std::to_string(i / 2);
			SetColor(AIBoard, 2);
			mvwprintw(AIBoard, i + 3, 4, "0 0 0 0 0 0 0 0 0 0");
			SetColor(AIBoard, 1);
			if (i % 2 == 0) {
				SetColor(AIBoard, 1);
				mvwprintw(AIBoard, i + 3, 1, gletter.c_str());
			}
		}
		//
		char ychar = getchar();
		while (ychar < 'A' || ychar > 'J') {
			ychar = getchar();
			mvwprintw(EntryArea, 2, 2, &ychar);
		}
		int y = ychar - 'A';

		char xchar = getchar();
		while (xchar < '0' || xchar > '9') {
			xchar = getchar();
			mvwprintw(EntryArea, 2, 2, &xchar);
		}
		cs->put(Coordinate{ xchar,ychar });
		MoveResult cmr;
		mr->get(cmr);
		if (cmr == Quit) {
			break;
		}
	}
	cg.join();
	return Win;
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
		wclear(winboard);
		wclear(wnd);
		wborder(winboard, '|', '|', '-', '-', '+', '+', '+', '+');
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
			/*vector<Coordinate> ls;
			ls = ship.GetOccupiedSpace();
			for (int i = 0; i < getPieceLength(ship.Type); i++) {
				mvwprintw(winboard, ls[i].x + 3, ls[i].y + 4, "X");
			}*/
			RenderToGrid(winboard, ship);
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
		mvwprintw(wnd, 19, 0, "Press 'backspace' to remove a selected ship");
		mvwprintw(wnd, 20, 9, "Press enter to add ship/proceed");
		//refresh();
		//wrefresh(winboard);
		//wrefresh(wnd);
		//
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
			//break;
		}
		else if(tempship.Type != cpt) {
			tempship.Type = cpt;
			//Let's hope this doesnt crash anything at runtime
			b->NextValidPieceSpot(&tempship, ShipChange);
		}
		//Render the current ship, or highlight
		if (highlightship) {
			if (b->IsPieceOnBoard(cpt)) {
				SetColor(winboard, 4);
				int pos = b->GetPieceOnBoard(cpt);
				if (pos != -1) {
					SetColor(wnd, 2);
					RenderToGrid(winboard, b->BoardPieces.at(pos));
				}
			}
		}
		else {
			//piece is not on board, so render as a sort of 'overlay'
			if (!b->IsPieceOnBoard(cpt)) {
				SetColor(winboard, 4);
				int pos = b->GetPieceOnBoard(cpt);
				if (pos == -1) {
					RenderToGrid(winboard, tempship, "O");
				}
			}
		}//clear cursor
		mvwprintw(wnd, 1, 13, "  ");
		mvwprintw(wnd, 1, 31, "  ");
		mvwprintw(wnd, 4, 16, "  ");
		mvwprintw(wnd, 4, 28, "  ");
		mvwprintw(wnd, 7, 16, "  ");
		mvwprintw(wnd, 7, 27, "  ");
		mvwprintw(wnd, 10, 17, "  ");
		mvwprintw(wnd, 10, 26, "  ");
		mvwprintw(wnd, 13, 16, "  ");
		mvwprintw(wnd, 13, 27, "  ");
		//paint cursor
		SetColor(wnd, 3);
		switch (static_cast<PieceType>(selected))
		{
		case AircraftCarrier:
			mvwprintw(wnd, 1, 13, ">>");
			mvwprintw(wnd, 1, 31, "<<");
			break;
		case Battleship:
			mvwprintw(wnd, 4, 16, ">>");
			mvwprintw(wnd, 4, 28, "<<");
			break;
		case Submarine:
			mvwprintw(wnd, 7, 16, ">>");
			mvwprintw(wnd, 7, 27, "<<");
			break;
		case Cruiser:
			mvwprintw(wnd, 10, 17, ">>");
			mvwprintw(wnd, 10, 26, "<<");
			break;
		case Destroyer:
			mvwprintw(wnd, 13, 16, ">>");
			mvwprintw(wnd, 13, 27, "<<");
			break;
		default:
			break;
		}
		SetColor(wnd, 1);
		refresh();
		wrefresh(winboard);
		wrefresh(wnd);
		char ckey = getch();
		switch (ckey)
		{
		//Attempt to move piece up
		case '\x3':
			if (tempship.isValid) {
				b->NextValidPieceSpot(&tempship, Up);
			}
			break;
		//Attempt to move piece down
		case '\x2':
			if (tempship.isValid) {
				b->NextValidPieceSpot(&tempship, Down);
			}
			break;
		//Attempt to move piece down
		case '\x4':
			if (tempship.isValid) {
				b->NextValidPieceSpot(&tempship, Left);
			}
			break;
		//Attempt to move piece Right
		case '\x5':
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
				tempship.Type = static_cast<PieceType>(selected);
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
				tempship.Type = static_cast<PieceType>(selected);
				b->NextValidPieceSpot(&tempship, ShipChange);
			}
			break;
		/*
		Attempt to place piece.
		If already selected, ignore.
		if all pieces placed, start game
		*/
		case '\n':
			//already piece on board
			if (b->IsPieceOnBoard(static_cast<PieceType>(selected))) {
				if (b->BoardisValid()) {
					bool result = ConfirmDialog("Would you like to continue?");
					if (result) {
						return 1;
					}
				}
			}
			//Add to board if possible
			//ship is valid, not a duplicate, 
			else {
				if (b->ValidPieceSpot(tempship)) {
					b->BoardPieces.push_back(tempship);
					tempship.isValid = false;
				}
			}
			break;
		//If piece is already placed down, remove it
		case '\b':
			if (b->IsPieceOnBoard(static_cast<PieceType>(selected))) {
				int pos = b->GetPieceOnBoard(static_cast<PieceType>(selected));
				if (pos != -1) {
					Piece px = b->BoardPieces.at(pos);
					//if (b->ValidPieceSpot(px)) {
						tempship.CenterAxis = px.CenterAxis;
						tempship.orientation = px.orientation;
						tempship.isValid = true;
						tempship.Type = px.Type;
						b->PopPieceFromBoard(static_cast<PieceType>(selected));
					//}
				}
			}
			break;
		//clears board, and returns to main menu
		case '\x1b':
		{
				bool result = ConfirmDialog("Would you like to quit?");
				if (result) {
					b->ClearBoard();
					return 0;
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

void UI::RenderToGrid (WINDOW* wnd, Piece pc, char* l) {
	vector<Coordinate> ls = pc.GetOccupiedSpace();
	//
	for (auto c: ls) {
		if (c.x < 0 || c.x > 9 || c.y < 0 || c.y > 9) {
			break;
		}
		else {
			mvwprintw(wnd, (c.x * 2) + 3, (c.y * 2) + 4, l);
		}
	}
}

void UI::RenderToGrid(WINDOW* wnd, vector<Coordinate> ls, char* l) {
	for (auto c : ls) {
		if (c.x < 0 || c.x > 9 || c.y < 0 || c.y > 9) {
			break;
		}
		else {
			mvwprintw(wnd, (c.x * 2) + 3, (c.y * 2) + 4, l);
		}
	}
}


bool ConfirmDialog(char* text) {
	//newwin:(height, width, starty,startx)
	WINDOW *winexit = newwin(7,35, 8,25);
	SetColor(winexit, 1, COLOR_BLACK, COLOR_WHITE, false);
	//wbkgdset(winexit, COLOR_PAIR(1));
	wborder(winexit, '|', '|', '-', '-', '+', '+', '+', '+');
	int c = 0;
	while (true) {
		SetColor(winexit, 1);
		mvwprintw(winexit, 1, 5, text);
		mvwprintw(winexit, 4, 3, "Press Enter to continue");
		mvwprintw(winexit, 5, 1, "Press Escape to close dialog");
		wrefresh(winexit);
		//render cursor
		char cu = ' ';
		while (cu != '\n' || cu != '\x1b') {
			cu = getch();
			//enter
			if (cu == '\n') {
				delwin(winexit);
				return true;
			}
			//escape
			else if (cu == '\x1b' ){
				delwin(winexit);
				clear();
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

