#include <ncurses.h>
#include <iostream>
#include "Rules.h"
#include "Item.h"



int main()
{
	initscr();
	curs_set(0);  // invisible cursor
	noecho();     // invisible keypad input
	nodelay(stdscr, 1);
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_YELLOW); // background color
	init_pair(2, COLOR_RED, COLOR_GREEN); // wall color
	init_pair(3, COLOR_YELLOW, COLOR_RED);  //head color
	init_pair(4, COLOR_YELLOW, COLOR_BLUE); // growth item color
	init_pair(5, COLOR_GREEN, COLOR_MAGENTA); // poison item color
	bkgd(COLOR_PAIR(1));
	resize_term(21, 60);
	attron(COLOR_PAIR(2));  // border color on
	border('1', '1', '1', '1', '2', '2', '2', '2');
	attroff(COLOR_PAIR(2)); // off
	Snake snk;
//	refresh();
	char a = getch();
	while(a != 'q') {
		if(a == 'r') {
			snk.newGame();
//			refresh();
		}
		a = getch();
	}
	endwin();
	return 0;
}
