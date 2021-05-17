#include <ncurses.h>
#include <ctime>

class Head{
  int y, x;
public:
  // 생성자 : 게임 시작시 Head를 화면 중앙에 띄운다.
  Head(){
    y=10; x=30;
    show();
  }
  int getY(){return y;}
  int getX(){return x;}
  // head는 현재 있는 위치 기준으로 i, j만큼 움직임.
  void setposition(int i, int j){ y+=i, x+=j; }
  void show(){
    attron(COLOR_PAIR(3)); // head color on
    mvprintw(y, x, "3");
    attroff(COLOR_PAIR(3)); //  off
  }
};

#define MAXLEN 50
class Body{
public:
  int len = 2; int x[MAXLEN] = {0}, y[MAXLEN]= {0};
  // 생성자 : 게임 시작시 Body를 화면 중앙에 띄운다.
  Body(){
     y[0] = y[1] = 10;  x[0] = 31; x[1] = 32;
    show();
  }

  // head에 종속적이므로, head의 위치를 인자로 받아 첫번째 body원소를 head의 위치로 이동
  // 나머지 body들은 앞의 body위치로 이동
  void setposition(int i, int j){
    del();
    int by, bx, py, px;   //before (y,x)position, present (y,x)position
    by = y[0]; bx = x[0];
    y[0] = i; x[0] = j;
    for(int l=1; l<len; l++){
      py = y[l]; px = x[l];
      y[l] = by; x[l] = bx;
      by = py; bx = px;
    }
  }
  void show(){
    attron(COLOR_PAIR(2));  //  body color
    for(int i=0; i<len; i++){
      mvprintw(y[i], x[i], "4");
    }
    attroff(COLOR_PAIR(2)); //  off

  }

  // Body 길이(len)가 1만큼 증가함에 따라 x, y 배열에 새로 생성되는 Body위치 할당.
  void IncBody(){
    // y[len-1]-y[len] = y[len-2]-y[len-1] 임을 이용.
    y[len] = 2*y[len-1]-y[len-2];
    x[len] = 2*x[len-1]-x[len-2];
    len++;}

  // Body 길이(len)가 1만큼 감소함에 따라 x, y 배열에서 해당 값 초기화
  void DecBody(){
    y[len-1] = 0; x[len-1] = 0;
    mvprintw(y[len-1], x[len-1] , " "); len--;}

    //if(len<3) GameOver = 1;

    // 지나간 자취 삭제
    void del(){
      mvprintw(y[len-1], x[len-1], " ");
    }

};


class Snake{
  Head hd; Body bd; bool GameOver = false;
public:
  // 입력받은 방향으로 이동하는 메서드
  void move(int dirY, int dirX){
    // 진행방향 반대로 이동하려 하거나 body에 부딪힐때, failed 창을 띄운다.
    for(int i=0; i<bd.len; i++){
      if(((hd.getY()+dirY) == bd.y[i])&&(hd.getX() == bd.x[i])) {
        failed(); GameOver = true; return;
      }
    }
    bd.setposition(hd.getY(), hd.getX());
    hd.setposition(dirY, dirX);
    hd.show(); bd.show();
    refresh();
  }

  // 게임이 진행되는 동안 작동하는 메인 알고리즘
  // : 키입력에 따라 움직임을 제어한다.
  void move(){
    while(GameOver != true){

    // 키보드 입력이 없을 때, 헤드랑 제일 가까운 body 반대방향으로 진행.
    // Head의 y좌표==Body[0]의 y좌표일 경우 서로 수평을 이루므로 x좌표 값만 변화.
    if(hd.getY()==bd.y[0]){
      if(hd.getX()>bd.x[0]) {
        move(0,1);
        delay(0.3);
      }
      else {
        move(0,-1);
        delay(0.3);
      }
    }
    // Head의 x좌표==Body[0]의 x좌표일 경우 서로 수직을 이루므로 y좌표 값만 변화.
    else{
      if(hd.getY()>bd.y[0]) {
        move(1,0);
        delay(0.3);
      }
      else {
        move(-1,0);
        delay(0.3);
      }
    }

  } //while (GameOver!=false)

  // 이 곳에 GameOver = true 일때의 화면을 제어할 부분 구현 필요.

} // move()

// delay 함수 구현 & 지연되는 시간동안 키 입력이 들어오면 움직임 제어.
int delay(float secs){
  clock_t delay = secs * CLOCKS_PER_SEC;
  clock_t start = clock();
  while((clock()-start) < delay) {
    char key;
    if(key=getch()){
      switch(key){
        case 'w':
          move(-1,0);
          break;
        case 's':
          move(1,0);
          break;
        case 'd':
          move(0,1);
          break;
        case 'a':
          move(0,-1);
          break;
      }
    }
  }
  return 0;
}

// failed 출력
void failed(){
  mvprintw(20, 30, "FAILED");
  refresh();
}

};
