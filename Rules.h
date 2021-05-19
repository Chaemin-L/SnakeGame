#ifndef __RULES_H_
#define __RULES_H_


class Head {
    int y, x;
public:
    Head();

    int getY() { return y; }
    int getX() { return x; }

    void setposition(int i, int j);
    void show();
};


#define MAXLEN 50
class Body {
public:
    int len = 2; int x[MAXLEN] = { 0 }, y[MAXLEN] = { 0 };
    Body();

    void setposition(int i, int j);
    void show();

    void IncBody();
    void DecBody();

    void del();

};


class Snake {
    Head hd; Body bd; time_t t;
    static bool GameOver;
public:
    Snake();

    void move();
    void keyIn(int y, int x);

    int delay(float secs);
    void failed();

    void makeItem();

    static void setGameStatus(bool b);

    void itemRule();
};

#endif
