#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "Rules.h"
#include "Item.h"

// constructor : print the Head
Head::Head() {
    y = 10; x = 30;
    show();
}

void Head::show() {
    attron(COLOR_PAIR(3)); // head color on
    mvprintw(y, x, "3");
    attroff(COLOR_PAIR(3)); //  off
}



// constructor : print the body
Body::Body() {
    y[0] = y[1] = 10;  x[0] = 31; x[1] = 32;
    show();
}

// head�� �������̹Ƿ�, head�� ��ġ�� ���ڷ� �޾� ù��° body���Ҹ� head�� ��ġ�� �̵�
// ������ body���� ���� body��ġ�� �̵�
void Body::setposition(int i, int j) {
    del();
    int by, bx, py, px;   //before (y,x)position, present (y,x)position
    by = y[0]; bx = x[0];
    y[0] = i; x[0] = j;
    for (int l = 1; l < len; l++) {
        py = y[l]; px = x[l];
        y[l] = by; x[l] = bx;
        by = py; bx = px;
    }
}

void Body::show() {
    attron(COLOR_PAIR(2));  //  body color
    for (int i = 0; i < len; i++) {
        mvprintw(y[i], x[i], "4");
    }
    attroff(COLOR_PAIR(2)); //  off
}

// increase body length
void Body::IncBody() {
    // y[len-1]-y[len] = y[len-2]-y[len-1] ���� �̿�.
    y[len] = 2 * y[len - 1] - y[len - 2];
    x[len] = 2 * x[len - 1] - x[len - 2];
    len++;
}

// decrease body length
void Body::DecBody() {
    y[len - 1] = 0; x[len - 1] = 0;
    mvprintw(y[len - 1], x[len - 1], " "); len--;

    if (len < 2) { Snake::setGameStatus(true); }
}

// ������ ���� ����
void Body::del() {
    mvprintw(y[len - 1], x[len - 1], " ");
}



bool Snake::GameOver = false;
int Snake::item = 0;
void Snake::move() {
      while (GameOver != true) {
          if(time(NULL) - t > 5) {
            makeItem();
            t = time(NULL);
          }

      // 키보드 입력이 없을 때, 헤드랑 제일 가까운 body 반대방향으로 진행.
      // Head의 y좌표==Body[0]의 y좌표일 경우 서로 수평을 이루므로 x좌표 값만 변화.
      if(hd.getY()==bd.y[0]){
        if(hd.getX()>bd.x[0]) {
          keyIn(0,1);
          delay(0.5);
        }
        else {
          keyIn(0,-1);
          delay(0.5);
        }
      }
      // Head의 x좌표==Body[0]의 x좌표일 경우 서로 수직을 이루므로 y좌표 값만 변화.
      else{
        if(hd.getY()>bd.y[0]) {
          keyIn(1,0);
          delay(0.5);
        }
        else {
          keyIn(-1,0);
          delay(0.5);
        }
      }
    } //while (GameOver!=false)
} // move()

void Snake::keyIn(int y, int x) {
    // �������� �ݴ��� �̵��Ϸ� �ϰų� body�� �ε�����, failed â�� ������.
    for (int i = 0; i < bd.len; i++) {
        if (((hd.getY() + y) == bd.y[i]) && ((hd.getX() + x) == bd.x[i])) {
            failed(); return;
        }
    }
    // ���� �ε��� �� fail
    if (((hd.getY() + y) == 0) || ((hd.getY() + y) == 20) || ((hd.getX() + x) == 0) || ((hd.getX() + x) == 59)) {
        failed(); return;
    }

    bd.setposition(hd.getY(), hd.getX());
    hd.setposition(y, x);
    hd.show(); bd.show();
    refresh();
}

// delay �Լ� ����
int Snake::delay(float secs) {
    clock_t delay = secs * CLOCKS_PER_SEC;
    clock_t start = clock();
    while ((clock() - start) < delay){
      char key;
      if(key=getch()){
        switch(key){
          case 'w':
            keyIn(-1,0);
            break;
          case 's':
            keyIn(1,0);
            break;
          case 'd':
            keyIn(0,1);
            break;
          case 'a':
            keyIn(0,-1);
            break;
      }
    }
  }
    return 0;
}

// failed ����
void Snake::failed() {
    mvprintw(20, 30, "FAILED");
    refresh();
    Snake::GameOver = true;
}

// Item
void Snake::makeItem() {
    if (item < 3) {
        srand(time(NULL));
        if (rand() % 2) Growth(hd, bd);
        else Poison(hd, bd);
    }
}
