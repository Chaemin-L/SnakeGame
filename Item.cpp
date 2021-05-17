#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Rules.h"
#include "Item.h"
using namespace std;

Growth::Growth(Head &hd, Body &bd) {
	srand(time(NULL));
		x = rand()%58+1;
		y = rand()%19+1;
	// �����Լ��� x, y ���ؼ� if������ snake ���̶� ������ �ٽ� (���̶� �����۳����� �� ��ġ��)
	while (x == hd.getX() || y == hd.getY()) {
		srand(time(NULL));

			x = rand()%58+1;
			y = rand()%19+1;
	}

	attron(COLOR_PAIR(4));  // item color on
	mvprintw(y, x, "5");
	attroff(COLOR_PAIR(4)); // off
	refresh();

	time_t t = time(NULL);
	Snake::setItemNum(1);
	GrowthRule(hd, bd, t);
}

void Growth::GrowthRule(Head &hd, Body &bd, time_t t) {
	if (time(NULL) - t > 10) {
		mvprintw(y, x, " ");
		Snake::setItemNum(-1);
	}
	// ������ũ�� ������ �ʿ��� ������
	if (x == hd.getX() && y == hd.getY()) {
		mvprintw(y, x, " ");
		Snake::setItemNum(-1);

		// ������ũ �ٵ� 1 ����
		bd.setposition(hd.getY(), hd.getX());
		bd.IncBody();
		hd.setposition(-1, 0);
		hd.show(); bd.show();
		refresh();
	}
}


Poison::Poison(Head &hd, Body &bd) {
	srand(time(NULL));
		x = rand()%58+1;
		y = rand()%19+1;

	//��, body���� �� ����
	while ((x == hd.getX()) || (y == hd.getY())) {
		srand(time(NULL));
			x = rand()%58+1;
			y = rand()%19+1;
	}

	attron(COLOR_PAIR(5));  // item color on
	mvprintw(y, x, "6");
	attroff(COLOR_PAIR(5)); // off
	refresh();

	time_t t = time(NULL);
	Snake::setItemNum(1);
	PoisonRule(hd, bd, t);
}

void Poison::PoisonRule(Head &hd, Body &bd, time_t t) {
	if (time(NULL) - t > 10) {
		mvprintw(y, x, " ");
		Snake::setItemNum(-1);
	}
	// ������ũ�� ������ �ʿ��� ������
	if (x == hd.getX() && y == hd.getY()) {
		mvprintw(y, x, " ");
		Snake::setItemNum(-1);

		// ������ũ �ٵ� 1 ����
		bd.setposition(hd.getY(), hd.getX());
		bd.DecBody();
		hd.setposition(-1, 0);
		hd.show(); bd.show();
		refresh();
	}
}
