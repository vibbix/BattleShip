#include <curses.h>
#include <panel.h>
#include "UI.h"
//Game loop implemented here
int main() {
	UI gameui = UI();
	gameui.StartUI();
	return 0;
}