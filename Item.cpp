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
//		bd->setposition(hd->getY(), hd->getX());
		bd->IncBody();
//		hd->setposition(-1, 0);
	//	hd->show(); bd->show();
	//	refresh();
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
	//	bd->setposition(hd->getY(), hd->getX());
		bd->DecBody();
	//	hd->setposition(-1, 0);
	///	hd->show(); bd->show();
//		refresh();
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


//bd가 연동이안되고 snk가 새로 생기는 문제-해결
//아이템먹으면 위로감(방향이바뀜) 그리고 하나올라가면서 추가/삭제됨-해
//먹자마자 안 되고 먹고 하나 다음에 추가/삭제
