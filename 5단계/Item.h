#ifndef __ITEM_H_
#define __ITEM_H_
#include <ctime>
#include "Rules.h"

class Growth {
	int x = 0, y = 0;
	Head *hd = nullptr; Body *bd = nullptr;
	char pos;
	time_t t;

	// 해당 아이템의 획득 여부를 외부에 전달할 수 있는 변수
	bool ItemState = false;

public:
	Growth() {}
	Growth(Head &head, Body &body);

	int getX() { return x; }
	int getY() { return y; }

	int GrowthRule();

	bool getItemState(){ return ItemState;};
	void setItemState(bool b){ ItemState = b; };
};


class Poison {
	int x = 0, y = 0;
	Head *hd = nullptr; Body *bd = nullptr;
	char pos;
	time_t t;
	// 해당 아이템의 획득 여부를 외부에 전달할 수 있는 변수
	bool ItemState = false;
	// 만난 아이템이 성장 아이템인지(1), 독 아이템인지(0)를 판별하여 외부에 전달하는 변수
	bool isGrowth = false;

public:
	Poison() {}
	Poison(Head &head, Body &body);

	int getX() { return x; }
	int getY() { return y; }

	int PoisonRule();

	bool getItemState(){ return ItemState;};
	void setItemState(bool b){ ItemState = b; };
	};


class Item {
	Growth growp;
	Poison poisp;

public:
	Item(Growth g);
	Item(Poison p);

	int rule();
	void clear();

	// 아무 아이템을 얻지 못한 경우(0), 성장 아이템 획득 시 (1), 독 아이템 획득시(2) 출력.
	// 모든 처리 방식이 private 변수 Growth와 Poison 클래스 내부에서 이루어지므로,
	// 이 결과값을 외부로 전달하기 위한 함수
	int CheckItem();

};



#endif
