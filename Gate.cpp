#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include "Gate.h"
#include "Map.h"
extern vector<array<int, 2>> wall;

Gate::Gate(Head &head, Body &body) : hd(&head), bd(&body) {}

Gate& Gate::operator=(const Gate& g){
	hd = g.hd; bd = g.bd;
	init();
	return *this;
}

void Gate::init() {
		srand(time(NULL));
		int i = rand()%wall.size();
		int j = rand()%wall.size();
		x1 = wall[i][1], x2 = wall[j][1];
		y1 = wall[i][0], y2 = wall[j][0];
		mvprintw(y1, x1, "7");
		while (y2 == y1 || x2 == x1) {
			srand(time(NULL));
			j = rand()%wall.size();
			x2 = wall[j][1];
			y2 = wall[j][0];
		}
		mvprintw(y2, x2, "7");
		refresh();
}

void Gate::clear() {
	attron(COLOR_PAIR(2));
	mvprintw(y1, x1, "1");
	mvprintw(y2, x2, "1");
	attroff(COLOR_PAIR(2));
	refresh();
}

int Gate::passHead() {
	int y = hd->getY(); int x = hd->getX();
	// 게이트가 가장자리에 있을 때
	if(y == y1 && x == x1){
		if (y2 == 0) hd->setposition(-y+y2+1, -x+x2);
		else if (y2 == HEIGHT-1) hd->setposition(-y+y2-1, -x+x2);
		else if (x2 == 0) hd->setposition(-y+y2, -x+x2+1);
		else if (x2 == WIDTH-1) hd->setposition(-y+y2, -x+x2-1);
		return -1;

	}
	else if(y == y2 && x == x2){
		if (y1 == 0) hd->setposition(-y+y1+1, -x+x1);
		else if (y1 == HEIGHT-1) hd->setposition(-y+y1-1, -x+x1);
		else if (x1 == 0) hd->setposition(-y+y1, -x+x1+1);
		else if (x1 == WIDTH-1) hd->setposition(-y+y1, -x+x1-1);
		return -1;
	}
	// 게이트의 위치가 가장자리가 아니고 진행방향이 벽에 의해 막혀있을 때
//	else if()
	return 0;
}
