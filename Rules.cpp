#include <ncurses.h>
#include <cstdlib>
#include "Rules.h"
#include "Item.h"
#include "Gate.h"
#include "Map.h"

vector<Item> item;
Gate gate;

Head::Head() {
    init();
}

void Head::init() {
    y = HEIGHT/2; x = WIDTH/2;
    show();
}


void Head::setposition(int i, int j) { y += i, x += j; }

void Head::show() {
    attron(COLOR_PAIR(3)); // head color on
    mvprintw(y, x, "3");
    attroff(COLOR_PAIR(3)); //  off
}


Body::Body() {
    init();
}

void Body::init() {
    len = 2; std::fill_n(x, MAXLEN, 0); std::fill_n(y, MAXLEN, 0);
    y[0] = y[1] = HEIGHT/2; x[0] = WIDTH/2+1; x[1] = x[0]+1;
    show();
}

// head에 종속적이므로, head의 위치를 인자로 받아 첫번째 body원소를 head의 위치로 이동
// 나머지 body들은 앞의 body위치로 이동
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
    attron(COLOR_PAIR(8));  //  body color
    for (int i = 0; i < len; i++) {
        mvprintw(y[i], x[i], "4");
    }
    attroff(COLOR_PAIR(8)); //  off
}

// increase body length
void Body::IncBody() {
    // y[len-1]-y[len] = y[len-2]-y[len-1] 임을 이용하여
    // len번째 배열에 새로이 좌표를 추가한다.
    y[len] = 2 * y[len - 1] - y[len - 2];
    x[len] = 2 * x[len - 1] - x[len - 2];
    len++;
}

// decrease body length
void Body::DecBody() {
    mvprintw(y[len - 1], x[len - 1], " ");
    y[len - 1] = 0; x[len - 1] = 0; len--;

    if (len < 2) { Snake::fail(); }
}

// 지나간 자취 삭제
void Body::del() {
    mvprintw(y[len - 1], x[len - 1], " ");
}



bool Snake::GameOver = false;

Snake::Snake(){
  UpdateBoard(score, state);
  ti = time(NULL);
  tg = time(NULL);
  move();
}

void Snake::move() {
  while (!GameOver) {
      // 3초가 지날 때마다 아이템이 생성됨(3개 이하)
      makeItem();

      if(state[0]>state[4]) UpdateBoard(score, state);

      // 게이트 통과할 때 알맞은 방향으로 진행되도록 하는 함수
      if(passtime == 1) {
      	keyIn(gate.keyinyx[0], gate.keyinyx[1]);
        moveControl(0.4);
        continue;
      }

      // 10초마다 검사하여 게이트가 존재하지 않으면 게이트를 생성함
      makeGate();

      // 키보드 입력이 없을 때, 헤드랑 제일 가까운 body 반대방향으로 진행.
      // Head의 y좌표==Body[0]의 y좌표일 경우 서로 수평을 이루므로 x좌표 값만 변화.
      if(hd.getY()==bd.y[0]){
        if(hd.getX()>bd.x[0]) {
          keyIn(0,1);
          moveControl(0.4);
        }
        else {
          keyIn(0,-1);
          moveControl(0.4);
        }
      }
      // Head의 x좌표==Body[0]의 x좌표일 경우 서로 수직을 이루므로 y좌표 값만 변화.
      else{
        if(hd.getY()>bd.y[0]) {
          keyIn(1,0);
          moveControl(0.4);
        }
        else {
          keyIn(-1,0);
          moveControl(0.4);
        }
      }

      // body까지 모두 Gate를 지나면 Gate 초기화
      if(passtime >= bd.len+1) {
          gate.clear();
          passingGate = false;
          isGate = false;
          passtime = 0;
          tg = time(NULL);
          plusGate();
          checkMission();
      }

      if(levelUp){
        // 4단계 모두 통과시
        if(level==4) {
          theEnd();
          return;
        }
        level++;
        succeed();
        reset();

      }

    } //while (GameOver!=false)
 level = 1;
} // move()

void Snake::keyIn(int y, int x) {
    // 진행방향 반대로 이동하려 하거나 body에 부딪힐때, fail 창을 띄운다.
    for (int i = 0; i < bd.len; i++) {
        if (((hd.getY() + y) == bd.y[i]) && ((hd.getX() + x) == bd.x[i])) {
            fail(); return;
        }
    }
    // 벽에 닿으면 fail
    if ((mvinch(hd.getY() + y, hd.getX() + x) & A_CHARTEXT) == '1' || hd.getY() + y < 0 || hd.getY() + y > HEIGHT-1 || hd.getX() + x < 0 || hd.getX() + x > WIDTH-1) {
      beep(); fail(); return;
      }

    bd.setposition(hd.getY(), hd.getX());
    hd.setposition(y, x);

    itemRule();
    isPassingGate();
    if(passingGate){ passtime++; }

    hd.show(); bd.show();
    refresh();
}

// moveControl 함수 구현 & 지연되는 시간동안 키 입력이 들어오면 움직임 제어.
int Snake::moveControl(float secs) {
    clock_t moveControl = secs * CLOCKS_PER_SEC;
    clock_t start = clock();
    while ((clock() - start) < moveControl){
      makeItem();
      if(GameOver == true) break;
      char key;
      if(key=getch()){
        switch(key){
          case 'w':
            keyIn(-1,0);
            start = clock();
            break;
          case 's':
            keyIn(1,0);
            start = clock();
            break;
          case 'd':
            keyIn(0,1);
            start = clock();
            break;
          case 'a':
            keyIn(0,-1);
            start = clock();
            break;
      }
      key = '\0';
    }
  }
    return 0;
}

// fail 출력
void Snake::fail() {
    beep();
    mvprintw(HEIGHT-3, WIDTH/2-2, "Fail");
    mvprintw(HEIGHT-2, WIDTH/2-5, "Try again!");
    attron(A_BLINK);
    mvprintw(HEIGHT-2, WIDTH-20, "R(restart)/Q(quit)");
    attroff(A_BLINK);

    refresh();
    GameOver = true;
}

// fail 출력
void Snake::succeed() {
    beep();
    mvprintw(HEIGHT-3, WIDTH/2-2, "Success!");
    mvprintw(HEIGHT-2, WIDTH/2-9, "~Next Stage Loading~");
    attron(A_BLINK);
    mvprintw(HEIGHT-2, WIDTH-15, "N(next level)");
    attroff(A_BLINK);
    refresh();
    char k = getch();
    while(k !='n'){ k= getch();}
    nodelay(stdscr, 1);

    GameOver = false;
}

// Item 생성 함수
void Snake::makeItem() {
    if(time(NULL) - ti > 3) {

      if (item.size() < 3) {
          srand(time(NULL));
          if (rand() % 2) {
            Growth g(hd, bd);
            Item i(g);
            item.emplace_back(i);
          }
          else {
            Poison p(hd, bd);
            Item i(p);
            item.emplace_back(i);
          }
      }
    ti = time(NULL);
  }
}

void Snake::itemRule(){
      for(int i = item.size()-1; i >=0; i--) {
        if(item[i].rule() == -1){
          if(item[i].CheckItem()==1) {
            plusBody(); plusItem();
            checkMission();
          }
          else if(item[i].CheckItem()==2) {
            minusBody(); plusPoison();
            checkMission();
          }
          item.erase(item.begin() + i);
        }
      }
}

// Gate 생성 함수
void Snake::makeGate() {
  if(time(NULL) - tg > 10) {
      if (isGate) return;
      gate = Gate(hd, bd);
      isGate = true;
      tg = time(NULL);
  }
}

void Snake::isPassingGate() {
    if(!isGate || passtime) return;

    int n = gate.passHead();
    if(n == 1) {
      isGate = false;
      gate.clear();
      tg = time(NULL);
      return;
    }
    if(n == -1) {
      passingGate = true;
      return;
    }
}

// 미션 통과시 V 표시 출력
void Snake::checkMission(){
  if(state[0]>state[4]) state[4] = state[0];
  UpdateBoard(score, state);
  int cnt=0;
  if(state[4]>=missions[0]){
    mvwprintw(mission, 3, 8, "V");
    cnt++;
  }
  for(int i=1; i<4; i++){
    if(state[i] >= missions[i]) {
      mvwprintw(mission, 3+i, 8, "V");
      cnt++;
    }
  }
  wrefresh(mission);
  if(cnt==4) {
    levelUp = true;
  }
}


void Snake::reset(){
  for(int i = item.size()-1; i >=0; i--) {
    item[i].clear();
    item.erase(item.begin() + i);
  }
  gate.clear();
  isGate = false;
  passingGate = false;
  passtime = 0;

  // clear and initiailize the screen
  DrawMap(level);
  state = {3, 0, 0, 0, 3};
  UpdateBoard(score, state);
  hd.init(); bd.init();

  GameOver = false;
  levelUp = false;
  ti = time(NULL);
  tg = time(NULL);
}
