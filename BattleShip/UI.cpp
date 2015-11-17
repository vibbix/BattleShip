#include "curses.h"
#include "UI.h"

UI::UI() {}

void UI::StartUI() {
	DisplayTitleScreen();
	int result = StartMenu();
	//Means quit game
	if (result == 1) {
		return;
	}
	Difficulty aidiff = SelectDifficulty();
	CurrentGame = Game(aidiff);
	return;
}
#pragma region MenuCode
void UI::DisplayTitleScreen() {
	WINDOW* wnd = initscr();
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
#pragma endregion

#pragma region ColorCommands
void SetColor(short num, short text, short backround) {
	if (has_colors() == FALSE)
	{
		return;
	}
	start_color();
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
#pragma endregion

