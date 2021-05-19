#ifndef __ITEM_H_
#define __ITEM_H_
#include <ctime>
#include "Rules.h"

class Growth {
	int x, y;
	Head *hd; Body *bd;
	time_t t;

public:
	// ������(������ ����)
	Growth() { x=0; }
	Growth(Head &head, Body &body);

	int getX() { return x; }
	int getY() { return y; }

	int GrowthRule();
};


class Poison {
	int x, y;
	Head *hd; Body *bd;
	time_t t;

public:
	// ������(������ ����)
	Poison(){ x=0; }
	Poison(Head &head, Body &body);

	int getX() { return x; }
	int getY() { return y; }

	int PoisonRule();
};


class Item {
		Growth growp ;
		Poison poisp ;

public:
	Item(Growth g);
	Item(Poison p);

	int rule();
};



#endif
