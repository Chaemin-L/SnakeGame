#include <ncurses.h>
#include <iostream>
#include <string>
using namespace std;

class Snake{


public:
	int body = 2;
};

int main()
{

  initscr();
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_YELLOW); // background color
  init_pair(2, COLOR_RED, COLOR_GREEN); // wall color
  init_pair(3,COLOR_YELLOW, COLOR_RED);  //head color
  bkgd(COLOR_PAIR(1));
  resize_term(21, 60);
  attron(COLOR_PAIR(2));  // border color on
  border('1','1','1','1','2','2','2','2');
  attroff(COLOR_PAIR(2)); // off
  attron(COLOR_PAIR(3)); // head color on
  Snake snk;
  mvprintw(10,30, "3");
  attroff(COLOR_PAIR(3)); //  off
  attron(COLOR_PAIR(2));  //  tail color
  for(int i =0; i<snk.body; i++)
	mvprintw(10,31+i, "4");
  attroff(COLOR_PAIR(2)); //  off
  refresh();
  getch();
  endwin();
  return 0;
}
