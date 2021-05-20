#ifndef __ITEM_H_
#define __ITEM_H_
#include <ctime>
#include "Rules.h"

class Growth {
	int x = 0, y = 0;
	Head *hd = nullptr; Body *bd = nullptr;
	time_t t;

public:
	Growth() {}
	Growth(Head &head, Body &body);

	int getX() { return x; }
	int getY() { return y; }

	int GrowthRule();
};


class Poison {
	int x = 0, y = 0;
	Head *hd = nullptr; Body *bd = nullptr;
	time_t t;

public:
	Poison() {}
	Poison(Head &head, Body &body);

	int getX() { return x; }
	int getY() { return y; }

	int PoisonRule();
};


class Item {
	Growth growp;
	Poison poisp;

public:
	Item(Growth g);
	Item(Poison p);

	int rule();
	void clear();
};



#endif
