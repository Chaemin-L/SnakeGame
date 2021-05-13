#include <ncurses.h>
#include <iostream>
#include "Rules.cpp"
/*
class Snake{
protected:
  int y, x;
  const char *ch;
public:
  Snake(int yp = 10, int xp = 30, const char *c = nullptr):  y(yp), x(xp), ch(c){}
  int getY(){return y;}
  int getX(){return x;}

  int setY(int i){return y+i;}
  int setX(int i){return x+i;}
  void setposition(int i, int j){ mvprintw(y+=i, x+=j, ch); }
};

Body(){
  for(int i=0; i<len; i++)
    bd[i] = new int[MAXLEN];
  bd[0][0] = bd[1][0] = 10;
  bd[0][1] = 31; bd[1][1] = 32;
  const char c = '4';
  ch = &c;
  show();
}

~Body(){
  for(int i=0; i<MAXLEN; i++){
    delete[] bd[i];
  }
  delete[] bd;
}


*/


int main()
{
  initscr();
  curs_set(0);  // invisible cursor
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
