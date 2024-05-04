#pragma once


#define SCENE_TITLE 0
#define SCENE_GAME 1
#define SCENE_GAMEOVER 2

#define SCENE_GAMECLEAR 3

#define SCENE_CHARATALK 4


extern int talkNum;

void SceneInit();
void SceneManage(int);
//void ChangeScene(int*);

void TitleDraw();
void GameOverDraw();
void GameClearDraw();

void CharaTalkDraw();