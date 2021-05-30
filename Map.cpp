#include <ncurses.h>
#include <string>
#include <vector>
#include "Map.h"

// Gate가 생길 수 있는 wall 좌표들을 모아놓은 벡터
vector<array<int, 2>> wall;

bool isEnd = false;

// 점수를 기록하는 window(score, mission)
WINDOW *score = newwin(9, 30, 1, 65);;
WINDOW *mission;
// 미션으로 주어지는 수(bdoy length, item, poision, gate)들이 담긴 벡터
vector<int> missions;


void theStart(){
  mvprintw(10, 30, "Press the any key to start game.");
  refresh();
  int key = getch();
  while(key=='\0'){}
  // 시작을 위해 키를 입력 받을때까지 기다리게 하고,
  // 이후에는 원활한 움직임 제어를 위해 getch()의 delay를 없앤다.
  nodelay(stdscr, 1);

}


void theEnd(){
  delwin(score);
  delwin(mission);
  clear();
  mvprintw(9, 20, "Thank you for playing this game.*^^*");
  mvprintw(10, 20, "This game was made by Jaemin-Sim and Chaemin-Lee.");
  mvprintw(11, 20, "KMU - Science of Software");
  refresh();
  isEnd = true;
  clock_t delay = 3 * CLOCKS_PER_SEC;
  clock_t start = clock();
  while ((clock() - start) < delay){}
  endwin();
}

// set the game base settings
void setBase(){
  initscr();
  curs_set(0);  // invisible cursor
  noecho();     // invisible keypad input
  start_color();
	init_pair(1, COLOR_BLUE, COLOR_YELLOW); // background color
	init_pair(2, COLOR_RED, COLOR_GREEN); // wall color
	init_pair(3, COLOR_YELLOW, COLOR_RED);  //head color
	init_pair(4, COLOR_BLACK, COLOR_CYAN); // growth item color
  init_pair(5, COLOR_CYAN, COLOR_MAGENTA); // poison item color
	init_pair(6, COLOR_WHITE, COLOR_BLACK); // gate color
  init_pair(7, COLOR_BLACK, COLOR_WHITE); // scoreboard color

	bkgd(COLOR_PAIR(1));
}

void DrawMap(int level){
  // initialize the window
  clear();
  wall.clear();
  attron(COLOR_PAIR(2));
  // according to level
  switch(level){
    // level 1 : draw number 1
    case 1:
      for(int i=6; i<14; i++){
        mvprintw(i, 10, "1");
        mvprintw(i, 49, "1");
      }
      missions = {3, 1, 0, 1};
      break;
    // level 2 : draw number 2
    case 2:
      for(int i=6; i<18; i+=4){
        for(int j=6; j<16; j++){
          mvprintw(i, j, "1");
        }
        for(int j=44; j<54; j++){
          mvprintw(i, j, "1");
        }
      }

      for(int i=7; i<10; i++){
        mvprintw(i, 15, "1");
        mvprintw(i, 53, "1");
      }
      for(int i=11; i<14; i++){
        mvprintw(i, 6, "1");
        mvprintw(i, 44, "1");
      }
      missions = {3, 1, 1, 0};
      break;
    // level 3 : draw number 3
    case 3:
      for(int i=6; i<18; i+=4){
        for(int j=6; j<16; j++){
          mvprintw(i, j, "1");
        }
        for(int j=44; j<54; j++){
          mvprintw(i, j, "1");
        }
      }
      for(int i=7; i<14; i++){
        mvprintw(i, 15, "1");
        mvprintw(i, 53, "1");
      }
      missions = {3, 0, 1, 1};
      break;

    // level 4 : draw number 4
    case 4:
      for(int i=6; i<16; i++){
          mvprintw(11, i, "1");
      }
      for(int i=44; i<54; i++){
          mvprintw(11, i, "1");
      }
      for(int i=6; i<11; i++){
        mvprintw(i, 6, "1");
        mvprintw(i, 13, "1");
        mvprintw(i, 44, "1");
        mvprintw(i, 51, "1");
      }
      mvprintw(11, 13, "2");
      mvprintw(11, 51, "2");
      for(int i=12; i<14; i++){
        mvprintw(i, 13, "1");
        mvprintw(i, 51, "1");
      }
      missions = {3, 1, 1, 1};
      break;
  }
    attroff(COLOR_PAIR(2));
//  	resize_term(HEIGHT, WIDTH);
    // Game border
    attron(COLOR_PAIR(2));  // border color on
    for(int i=0; i<HEIGHT; i++){
      mvprintw(i, 0, "1");
      mvprintw(i, WIDTH-1, "1");
    }
    for(int i=0; i<WIDTH; i++){
      if((i==0)||(i==(WIDTH-1))){
        mvprintw(0, i, "2");
        mvprintw(HEIGHT-1, i, "2");
        continue;
      }
      mvprintw(0, i, "1");
      mvprintw(HEIGHT-1, i, "1");
    }

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
    DrawBoard();
    UpdateBoard(mission, missions);
}

// Draw Score & Mission board
void DrawBoard(){
  //score board
  score = newwin(9, 30, 1, 65);
  wbkgd(score, COLOR_PAIR(7));
  mvwprintw(score, 3, 6, "/   (Max Body Length)");
  makeFrame(score, "Score Board");
  // mission board
  mission = newwin(9, 30, 10, 65);
  wbkgd(mission, COLOR_PAIR(6));
  for(int i=3; i<7; i++){
    mvwprintw(mission, i, 7, "( )");
  }
  makeFrame(mission, "Mission");

}

// board(Score & Mission) Frame 생성.
void makeFrame(WINDOW *win, const char *ch){
  wborder(win, '|','|','-','-','*','*','*','*');
  mvwprintw(win, 1, 1, ch);
  mvwprintw(win, 3, 1, "B:");
  mvwprintw(win, 4, 1, "+:");
  mvwprintw(win, 5, 1, "-:");
  mvwprintw(win, 6, 1, "G:");
  wrefresh(win);
}

// board의 적절한 위에 인자로 들어온 벡터 출력 (board의 상태를 업데이트 할때 사용)
void UpdateBoard(WINDOW *board, const vector<int> &v){
    mvwprintw(board, 3, 5, " ");
    const char* body = to_string(v[0]).c_str();
    mvwprintw(board, 3, 4, body);
    const char* plus = to_string(v[1]).c_str();
    mvwprintw(board, 4, 4, plus);
    const char* minus = to_string(v[2]).c_str();
    mvwprintw(board, 5, 4, minus);
    const char* gate = to_string(v[3]).c_str();
    mvwprintw(board, 6, 4, gate);
    // state 벡터의 경우, 진행 중 최대 길이도 출력해야하므로.
    if(v.size()>4){
      const char* Maxbody = to_string(v[4]).c_str();
      mvwprintw(board, 3, 8, Maxbody);
    }

    wrefresh(board);

}
