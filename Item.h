#include "Rules.h"

class Growth {
	int x, y;

public:
	// ������(������ ����)
	Growth(Head &hd, Body &bd);

	int getX() { return x; }
	int getY() { return y; }

	void GrowthRule(Head &hd, Body &bd);
};

class Poison {
	int x, y;

public:
	// ������(������ ����)
	Poison(Head &hd, Body &bd);

	int getX() { return x; }
	int getY() { return y; }

	void PoisonRule(Head &hd, Body &bd);
};
