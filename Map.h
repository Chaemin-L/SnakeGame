#include <ncurses.h>

// 충돌할까봐 써둔 ifndef-endif 인데 안써도 노상관..이었다.
//#ifndef __MAP__H
//#define __MAP__H

#define HEIGHT 20
#define WIDTH 60
//int HEIGHT, WIDTH;

// set the game base settings
void setBase();
// clear and the draw the map
void DrawMap(int level=1);

//#endif
