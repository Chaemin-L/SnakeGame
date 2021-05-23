#include <ncurses.h>
#include <iostream>
#include "Rules.h"
#include "Item.h"
#include "Map.h"


int main()
{
	setBase();
	DrawMap(2);
	Snake snk;
	char a = getch();
	while(a != 'q') {
		if(a == 'r') {
			snk.newGame();
		}
		a = getch();
	}
	endwin();
	return 0;
}
