#pragma once


#define SCENE_TITLE 0
#define SCENE_GAME 1
#define SCENE_GAMEOVER 2

#define SCENE_GAMECLEAR 3

#define SCENE_CHARATALK 4


extern int talkNum;

void SceneInit();
// シーンの切り替え処理
// 引数：scene 描画するシーンの番号
// 0:タイトル画面 1:ゲーム画面 2:ゲームオーバー画面 3:ゲームクリア画面
void SceneManage(int);
//void ChangeScene(int*);

void TitleDraw();
void GameOverDraw();
void GameClearDraw();

void CharaTalkDraw();