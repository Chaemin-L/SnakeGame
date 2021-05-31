#include <ncurses.h>
#include "Map.h"

// Gate가 생길 수 있는 wall 좌표들을 모아놓은 벡터
vector<array<int, 2>> wall;

// set the game base settings
void setBase(){
  initscr();
  curs_set(0);  // invisible cursor
  noecho();     // invisible keypad input
  nodelay(stdscr, 1);
  start_color();
	init_pair(1, COLOR_BLUE, COLOR_YELLOW); // background color
	init_pair(2, COLOR_RED, COLOR_GREEN); // wall color
	init_pair(3, COLOR_YELLOW, COLOR_RED);  //head color
	init_pair(4, COLOR_BLACK, COLOR_CYAN); // growth item color
  init_pair(5, COLOR_CYAN, COLOR_MAGENTA); // poison item color
	init_pair(6, COLOR_WHITE, COLOR_BLACK); // gate color
	bkgd(COLOR_PAIR(1));
}

void DrawMap(int level){
  // initialize the window
  clear();
  wall.clear();
  // according to level
  switch(level){
    case 1:
      //HEIGHT = 20; WIDTH = 60;
      break;
    case 2:
      //HEIGHT = 20; WIDTH = 60;
      attron(COLOR_PAIR(2));
      for(int i=0; i<HEIGHT/2; i++){
        mvprintw(i, 20, "1");
      }
      attroff(COLOR_PAIR(2));
      break;

    case 3:
      //
    case 4:
      //
      break;
  }
  	resize_term(HEIGHT, WIDTH);
    attron(COLOR_PAIR(2));  // border color on
  	border('1', '1', '1', '1', '2', '2', '2', '2');
  	attroff(COLOR_PAIR(2)); // off
    // Gate가 생길 수 있는 wall 좌표들을 벡터에 추가
    for(int i = 0; i < HEIGHT; i++) {
      for(int j = 0; j < WIDTH; j++)
        if((mvinch(i, j) & A_CHARTEXT) == '1') {
          array<int, 2> a = {i, j};
          wall.emplace_back(a);
        }
    }
    refresh();
}
