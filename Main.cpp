#include <ncurses.h>
#include <iostream>
#include "Rules.cpp"



int main()
{
  initscr();
  curs_set(0);  // invisible cursor
  noecho();     // invisible keypad input
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_YELLOW); // background color
  init_pair(2, COLOR_RED, COLOR_GREEN); // wall color
  init_pair(3,COLOR_YELLOW, COLOR_RED);  //head color
  bkgd(COLOR_PAIR(1));
  resize_term(21, 60);
  attron(COLOR_PAIR(2));  // border color on
  border('1','1','1','1','2','2','2','2');
  attroff(COLOR_PAIR(2)); // off
  Snake snk;
  snk.move();
  refresh();
  getch();
  endwin();
  return 0;
}
