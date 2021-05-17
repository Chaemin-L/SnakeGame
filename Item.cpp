#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Item.h"
#include "Rules.h"
using namespace std;

Growth::Growth(Head &hd, Body &bd) {
	srand(time(NULL));
	// �����Լ��� x, y ���ؼ� if������ snake ���̶� ������ �ٽ� (���̶� �����۳����� �� ��ġ��)
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
	// ������ũ�� ������ �ʿ��� �����
	if (x == hd.getX() && y == hd.getY()) {
		mvprintw(x, y, " ");
		item--;

		// ������ũ �ٵ� 1 ����
		bd.setposition(hd.getY(), hd.getX());
		bd.IncBody();
		hd.setposition(-1, 0);
		hd.show(); bd.show();
	}
}


Poison::Poison(Head &hd, Body &bd) {
	time_t t = time(NULL);
	srand(t);

	//��, body���� �� ���
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
	// ������ũ�� ������ �ʿ��� �����
	if (x == hd.getX() && y == hd.getY()) {
		mvprintw(x, y, " ");
		item--;

		// ������ũ �ٵ� 1 ����
		bd.setposition(hd.getY(), hd.getX());
		bd.DecBody();
		hd.setposition(-1, 0);
		hd.show(); bd.show();
	}
}

/*
if (time(NULL) - t > 10��) {
	mvprintw(x, y, " ");
	item--;
}
*/