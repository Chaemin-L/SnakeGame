#ifndef __RULES_H_
#define __RULES_H_


class Head {
    int y, x;
public:
    Head();
    void init();

    int getY() { return y; }
    int getX() { return x; }

    void setposition(int i, int j);
    void show();
};


#define MAXLEN 50
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
    Head hd; Body bd; time_t ti; time_t tg;
    static bool GameOver;
  	bool isGate = false; bool passingGate = false;
    int passtime = 0;
public:
    Snake();

    void move();
    void keyIn(int y, int x);

    int delay(float secs);
    static void failed();

    void makeItem();
    void itemRule();

    void makeGate();
    void isPassingGate();

//    void setGameStatus(bool b);

    void newGame();
};

#endif
