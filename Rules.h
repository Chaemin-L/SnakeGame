// 새게임 시작할 때 설정
bool GameOver = false;
int item = 0;

class Head {
    int y, x;
public:
    Head();

    int getY() { return y; }
    int getX() { return x; }

    void setposition(int i, int j) { y += i, x += j; }
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
    Head hd; Body bd;
public:
    void move();
    void keyIn(int y, int x);

    int delay(float secs);
    void failed();

    void makeItem();
};