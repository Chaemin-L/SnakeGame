#ifndef __RULES_H_
#define __RULES_H_

#include <vector>

class Head {
    int y, x;
public:
    // 생성자 : 화면의 중앙에서 나타나도록 한다.
    Head();
    void init();

    int getY() { return y; }
    int getX() { return x; }

    // 상하좌우 방향을 입력 받아 위치를 바꾼다.
    void setposition(int i, int j);
    void show();
};


#define MAXLEN 100
class Body {
public:
    int len; int x[MAXLEN] = { 0 }, y[MAXLEN] = { 0 };
    Body();
    void init();

    void setposition(int i, int j);
    void show();

    void IncBody();
    void DecBody();

    void del();

};


class Snake {
    Head hd; Body bd;
    time_t ti; time_t tg;
    static bool GameOver;
  	bool isGate = false; bool passingGate = false;
    int passtime = 0;
    std::vector<int> state = {3,0,0,0,3};
     int level = 1;
     bool levelUp = false;
public:
    Snake();

    void move();
    void keyIn(int y, int x);

    int moveControl(float secs);
    static void fail();
    static void succeed();

    void makeItem();
    void itemRule();

    void makeGate();
    void isPassingGate();

    // 현재 Snake의 미션 진행률에 따른 값 변화.
    void plusBody() { state[0]++; }
    void minusBody() { state[0]--; }
    void plusItem(){ state[1]++; }
    void plusPoison() { state[2]++; }
    void plusGate() { state[3]++; }
    void checkMission();
    void reset();
};

#endif
