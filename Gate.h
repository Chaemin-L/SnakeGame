#include "Rules.h"

#ifndef __GATE_H_
#define __GATE_H_

class Gate {
	Head *hd = nullptr; Body *bd = nullptr;
	int x1, x2, y1, y2;

public:
	int keyinyx[2];
	Gate() {};
	Gate(Head &head, Body &body);

	Gate& operator=(const Gate& g);

	void init();
	void clear();

	int passHead();

};

#endif
