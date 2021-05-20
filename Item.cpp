#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include "Rules.h"
#include "Item.h"
using namespace std;

Growth::Growth(Head &head, Body &body) : hd(&head), bd(&body) {
	// snake, 벽, 이미 생성된 아이템 자리 제외하고 랜덤으로 x, y 받아서 아이템 생성
	do {
	srand(time(NULL));
		x = rand()%58+1;
		y = rand()%19+1;
	}
	while (x == hd->getX() || y == hd->getY());

	attron(COLOR_PAIR(4));  // item color on
	mvprintw(y, x, "5");
	attroff(COLOR_PAIR(4)); // off
	refresh();

	t = time(NULL);
}

int Growth::GrowthRule() {
	// 생성 후 10초가 지나면 아이템 사라짐
	if (time(NULL) - t > 10) {
		mvprintw(y, x, " ");
		refresh();
		return -1;
	}
	// snake head와 만나면 아이템 사라짐
	if (x == hd->getX() && y == hd->getY()) {
		mvprintw(y, x, " ");

		// snake body 1 증가
		bd->IncBody();
		return -1;
	}
	return 0;
}


Poison::Poison(Head &head, Body &body) : hd(&head), bd(&body) {
	// snake, 벽, 이미 생성된 아이템 자리 제외하고 랜덤으로 x, y 받아서 아이템 생성
	do {
	srand(time(NULL));
		x = rand()%58+1;
		y = rand()%19+1;
	}
	while (x == hd->getX() || y == hd->getY());

	attron(COLOR_PAIR(5));  // item color on
	mvprintw(y, x, "6");
	attroff(COLOR_PAIR(5)); // off
	refresh();

	t = time(NULL);
}

int Poison::PoisonRule() {
	// 생성 후 10초가 지나면 아이템 사라짐
	if (time(NULL) - t > 10) {
		mvprintw(y, x, " ");
		refresh();
		return -1;
	}
	// snake head와 만나면 아이템 사라짐
	if (x == hd->getX() && y == hd->getY()) {
		mvprintw(y, x, " ");

		// snake body 1 감소
		bd->DecBody();
		return -1;
	}
	return 0;
}


Item::Item(Growth g){ growp = g; }

Item::Item(Poison p){ poisp = p; }

int Item::rule(){
		if (growp.getX()) { return growp.GrowthRule(); }
		else{ return poisp.PoisonRule(); }
}
