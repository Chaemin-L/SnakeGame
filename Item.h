#ifndef __ITEM_H_
#define __ITEM_H_

#include "Rules.h"

class Growth {
	int x, y;

public:
	// ������(������ ����)
	Growth(Head &hd, Body &bd);

	int getX() { return x; }
	int getY() { return y; }

	void GrowthRule(Head &hd, Body &bd, time_t);
};

class Poison {
	int x, y;

public:
	// ������(������ ����)
	Poison(Head &hd, Body &bd);

	int getX() { return x; }
	int getY() { return y; }

	void PoisonRule(Head &hd, Body &bd, time_t);
};

#endif
