#ifndef __MAP_H_
#define __MAP_H_
#include <array>
#include <vector>
using namespace std;

#define HEIGHT 20
#define WIDTH 60

// 최종단계까지 진행되었을 경우, 이를 외부에 알릴 수 있도록 전달하는 인자.
extern bool isEnd;
// 점수를 기록하는 window(scoreboard, mission)
extern WINDOW *score;
extern WINDOW *mission;
// 미션으로 주어지는 수(body length, item, poision, gate)들이 담긴 벡터
extern vector<int> missions;


// 실행시 바로 뜨는 창. 아무 키만 누르면 게임이 시작된다.
void theStart();
// 4단계 완료 후 최종 창. 이후 자동 종료한다.
void theEnd();
// set the game base settings
void setBase();
// 기존 창을 지우고, 새로운 맵을 그린다.
void DrawMap(int level=1);
// score와 mission의 창을 생성한다.
void DrawBoard();
// score와 mission을 나타내는 창의 공통된 내부 양식을 만든다.
void makeFrame(WINDOW *win, const char *ch);
// 화면(점수 창과 미션 창)을 업데이트한다.
void UpdateBoard(WINDOW *board, const vector<int> &v);
#endif
