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
		attron(COLOR_PAIR(6));
		mvprintw(y1, x1, "7");
		while (i == j) {
			srand(time(NULL));
			j = rand()%wall.size();
			x2 = wall[j][1];
			y2 = wall[j][0];
		}
		mvprintw(y2, x2, "7");
		attroff(COLOR_PAIR(6));
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
	int hy = hd->getY(); int hx = hd->getX();
	int by = bd->y[0]; int bx = bd->x[0];
	int y = hy-by; int x = hx-bx;
	if(hy == y1 && hx == x1){
		// 게이트가 가장자리에 있을 때
		if (y2 == 0) hd->setposition(-hy+y2+1, -hx+x2);
		else if (y2 == HEIGHT-1) hd->setposition(-hy+y2-1, -hx+x2);
		else if (x2 == 0) hd->setposition(-hy+y2, -hx+x2+1);
		else if (x2 == WIDTH-1) hd->setposition(-hy+y2, -hx+x2-1);
		// 게이트가 가장자리에 있지 않을 때
		// snake가 위아래로 진행중일 때
		else if(y){
			// 진행방향
			if ((mvinch(y2+y, x2+x) & A_CHARTEXT) != '1') hd->setposition(-hy+y2+y, -hx+x2+x);
			// 벽에 막혀있으면 진행방향의 시계방향
			else if ((mvinch(y2-x, x2-y) & A_CHARTEXT) != '1') hd->setposition(-hy+y2-x, -hx+x2-y);
			// 벽에 막혀있으면 진행방향의 역시계방향
			else if ((mvinch(y2+x, x2+y) & A_CHARTEXT) != '1') hd->setposition(-hy+y2+x, -hx+x2+y);
			// 벽에 막혀있으면 진행방향의 반대방향 (아래도 모두 동일)
			else hd->setposition(-hy+y2-y, -hx+x2-x);
		}
		// snake가 좌우로 진행중일 때
		else{
			if ((mvinch(y2+y, x2+x) & A_CHARTEXT) != '1') hd->setposition(-hy+y2+y, -hx+x2+x);
			else if ((mvinch(y2+x, x2+y) & A_CHARTEXT) != '1') hd->setposition(-hy+y2+x, -hx+x2+y);
			else if ((mvinch(y2-x, x2-y) & A_CHARTEXT) != '1') hd->setposition(-hy+y2-x, -hx+x2-y);
			else hd->setposition(-hy+y2-y, -hx+x2-x);
		}
		keyinyx[0] = hd->getY()-y2;
		keyinyx[1] = hd->getX()-x2;
		return -1;
	}
	else if(hy == y2 && hx == x2){
		// 게이트가 가장자리에 있을 때
		if (y1 == 0) hd->setposition(-hy+y1+1, -hx+x1);
		else if (y1 == HEIGHT-1) hd->setposition(-hy+y1-1, -hx+x1);
		else if (x1 == 0) hd->setposition(-hy+y1, -hx+x1+1);
		else if (x1 == WIDTH-1) hd->setposition(-hy+y1, -hx+x1-1);
		// 게이트가 가장자리에 있지 않을 때
		// snake가 위아래로 진행중일 때
		else if(y){
			if ((mvinch(y1+y, x1+x) & A_CHARTEXT) != '1') hd->setposition(-hy+y1+y, -hx+x1+x);
			else if ((mvinch(y1-x, x1-y) & A_CHARTEXT) != '1') hd->setposition(-hy+y1-x, -hx+x1-y);
			else if ((mvinch(y1+x, x1+y) & A_CHARTEXT) != '1') hd->setposition(-hy+y1+x, -hx+x1+y);
			else hd->setposition(-hy+y1-y, -hx+x1-x);
		}
		// snake가 좌우로 진행중일 때
		else{
			if ((mvinch(y1+y, x1+x) & A_CHARTEXT) != '1') hd->setposition(-hy+y1+y, -hx+x1+x);
			else if ((mvinch(y1+x, x1+y) & A_CHARTEXT) != '1') hd->setposition(-hy+y1+x, -hx+x1+y);
			else if ((mvinch(y1-x, x1-y) & A_CHARTEXT) != '1') hd->setposition(-hy+y1-x, -hx+x1-y);
			else hd->setposition(-hy+y1-y, -hx+x1-x);
		}
		keyinyx[0] = hd->getY()-y1;
		keyinyx[1] = hd->getX()-x1;
		return -1;
	}
	return 0;
}
