#include <ncurses.h>
#include <iostream>
#include "Rules.h"
#include "Item.h"
#include "Gate.h"
#include "Map.h"


int main()
{
	setBase();
	theStart();	// 이거 왜 작동 안하는지...
	DrawMap(1);
	Snake snk;
	if(isEnd==true) return 0;
	char a = getch();
	while(a != 'q') {
		if(a == 'r') {
			snk.reset();
			snk.move();
			if(isEnd==true) return 0;
		}
		a = getch();
	}
	endwin();
	return 0;
}
