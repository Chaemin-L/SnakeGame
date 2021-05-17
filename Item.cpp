#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Item.h"
#include "Rules.h"
using namespace std;

Growth::Growth(Head &hd, Body &bd) {
	srand(time(NULL));
	// 랜덤함수로 x, y 구해서 if문으로 snake 값이랑 같으면 다시 (벽이랑 아이템끼리도 안 겹치게)
	while (x == hd.getX() || y == hd.getY()) {
		x = rand();
		y = rand();
	}

	attron(COLOR_PAIR(4));  // item color on
	mvprintw(x, y, "5");
	attroff(COLOR_PAIR(4)); // off

	item++;
	GrowthRule(hd, bd);
}

void Growth::GrowthRule(Head &hd, Body &bd) {
	// 스네이크와 만나면 맵에서 사라짐
	if (x == hd.getX() && y == hd.getY()) {
		mvprintw(x, y, " ");
		item--;

		// 스네이크 바디 1 증가
		bd.setposition(hd.getY(), hd.getX());
		bd.IncBody();
		hd.setposition(-1, 0);
		hd.show(); bd.show();
	}
}


Poison::Poison(Head &hd, Body &bd) {
	time_t t = time(NULL);
	srand(t);

	//벽, body랑도 안 닿게
	while (!(x == hd.getX()) || !(y == hd.getY())) {
		x = rand();
		y = rand();
	}

	attron(COLOR_PAIR(5));  // item color on
	mvprintw(x, y, "6");
	attroff(COLOR_PAIR(5)); // off

	item++;
	PoisonRule(hd, bd);
}

void Poison::PoisonRule(Head &hd, Body &bd) {
	// 스네이크와 만나면 맵에서 사라짐
	if (x == hd.getX() && y == hd.getY()) {
		mvprintw(x, y, " ");
		item--;

		// 스네이크 바디 1 감소
		bd.setposition(hd.getY(), hd.getX());
		bd.DecBody();
		hd.setposition(-1, 0);
		hd.show(); bd.show();
	}
}

/*
if (time(NULL) - t > 10초) {
	mvprintw(x, y, " ");
	item--;
}
*/