#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include "Rules.h"
#include "Item.h"
using namespace std;

Growth::Growth(Head &head, Body &body) : hd(&head), bd(&body) {
	// �����Լ��� x, y ���ؼ� if������ snake ���̶� ������ �ٽ� (���̶� �����۳����� �� ��ġ��)
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
	if (time(NULL) - t > 10) {
		mvprintw(y, x, " ");
		refresh();
		return -1;
	}
	// ������ũ�� ������ �ʿ��� ������
	if (x == hd->getX() && y == hd->getY()) {
		mvprintw(y, x, " ");

		// ������ũ �ٵ� 1 ����
		bd->IncBody();
		return -1;
	}
	return 0;
}


Poison::Poison(Head &head, Body &body) : hd(&head), bd(&body) {
	//��, body���� �� ����
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
	if (time(NULL) - t > 10) {
		mvprintw(y, x, " ");
		refresh();
		return -1;
	}
	// ������ũ�� ������ �ʿ��� ������
	if (x == hd->getX() && y == hd->getY()) {
		mvprintw(y, x, " ");

		// ������ũ �ٵ� 1 ����
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
