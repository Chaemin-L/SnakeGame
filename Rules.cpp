#include <ncurses.h>
#include <ctime>



class Head{
  int y, x; const char *ch;
public:
  // constructor : print the Head
  Head(){
    y=10; x=30;
    const char c = '3';
    ch = &c;
    show();
  }
  int getY(){return y;}
  int getX(){return x;}
  // head는 현재 있는 위치 기준으로 i, j만큼 움직임.
  void setposition(int i, int j){ y+=i, x+=j; }
  void show(){
    attron(COLOR_PAIR(3)); // head color on
    mvprintw(y, x, ch);
    attroff(COLOR_PAIR(3)); //  off
  }
};

#define MAXLEN 50
class Body{
private:
  const char*ch;

public:
  int len = 2; int x[MAXLEN] = {0}, y[MAXLEN]= {0};
  // constructor : print the body
  Body(){
     y[0] = y[1] = 10;  x[0] = 31; x[1] = 32;
    const char c = '4';
    ch = &c;
    show();
  }

  // head에 종속적이므로, head의 위치를 인자로 받아 첫번째 body원소를 head의 위치로 이동
  // 나머지 body들은 앞의 body위치로 이동
  void setposition(int i, int j){
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
      mvprintw(y[i], x[i], ch);
    }
    attroff(COLOR_PAIR(2)); //  off

  }

  // increase body length
  void IncBody(){
    // y[len-1]-y[len] = y[len-2]-y[len-1] 임을 이용.
    y[len] = 2*y[len-1]-y[len-2];
    x[len] = 2*x[len-1]-x[len-2];
    len++;}
  // decrease body length
  void DecBody(){
    y[len-1] = 0; x[len-1] = 0;
    mvprintw(y[len-1], x[len-1] , " "); len--;}

    //if(len<3) GameOver = 1;

};


class Snake{
  Head hd; Body bd; bool GameOver = false;
public:
  void move(){
    while(GameOver != true){
      // 키보드 입력이 없을 때, 헤드랑 제일 가까운 body 반대방향으로 진행.
  /*  if (kbhit()){
      if(hd.getY()==bd.y[0])
        if(hd.getX()>bd.y[0]) {
          hd.setposition(0,1);
          hd.show();
          bd.show();
          delay();
        }
        else {
          hd.setposition(0,-1);
          hd.show(); bd.show();
          delay();
        }
      }
  */
    // 키보드 입력이 있을 때
    //else{
    char key;
    key = getch();
    switch(key){
      case 'w':
      // 진행방향 반대로 이동하려 하거나 body에 부딪힐때, failed 창을 띄운다.
      for(int i=0; i<bd.len; i++){
        if(((hd.getY()-1) == bd.y[i])&&(hd.getX() == bd.x[i])) {
          failed(); return;
        }
      }
      bd.setposition(hd.getY(), hd.getX());
      hd.setposition(-1, 0);
      hd.show(); bd.show();
      refresh();
      delay(0.5);
      break;
        // head position (y, x) => (y--, x)
        // , followed body.
      case 's':
      for(int i=0; i<bd.len; i++){
        if(((hd.getY()+1) == bd.x[i])&&(hd.getX() == bd.x[i])) {
          failed();  break;
        }
      }
      bd.setposition(hd.getY(), hd.getX());
      hd.setposition(1, 0);
      hd.show(); bd.show();
      refresh();
      delay(0.5);
      break;
      // head position (y, x) => (y++, x)
      // , followed body.
      case 'd':
      for(int i=0; i<bd.len; i++){
        if(((hd.getX()+1) == bd.x[i])&&(hd.getY() == bd.y[i])) {
          failed();  break;
        }
      }
      bd.setposition(hd.getY(), hd.getX());
      hd.setposition(0, 1);
      hd.show(); bd.show();
      refresh();
      delay(0.5);
      break;
      // head position (y, x) => (y, x++)
      // , followed body.
      case 'a':
      for(int i=0; i<bd.len; i++){
        if(((hd.getX()-1) == bd.x[i])&&(hd.getY() == bd.y[i])){
        failed();  break;
        }
      }
      bd.setposition(hd.getY(), hd.getX());
      hd.setposition(0, -1);
      hd.show(); bd.show();
      refresh();
      delay(0.5);
      break;
        // head position (y, x) => (y, x--)
        // , followed body.

      }
    //} //else 입력이 있을때.

  } //while (GameOver!=false)
} // move()
// delay 함수 구현

int delay(float secs){
  clock_t delay = secs * CLOCKS_PER_SEC;
  clock_t start = clock();
  while((clock()-start) < delay) ;
  return 0;
}
// failed 출력
void failed(){
  mvprintw(20, 30, "FAILED");
  refresh();
}

};
