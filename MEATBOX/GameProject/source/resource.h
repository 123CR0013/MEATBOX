#pragma once
#include "gamemain.h"


#define EFFECT_TYPE_MAX	10
#define EFFECT_SHEETS_MAX 10

#define EFFECT_TYPE_MOVE 0
#define EFFECT_TYPE_IMPACT 1
#define EFFECT_TYPE_HATENA 2
#define EFFECT_TYPE_ARROW_YELLOW 3
#define EFFECT_TYPE_ARROW_RED 4

#define EFFECT_TYPE_EXPLOSION_EYE_1 (5)
#define EFFECT_TYPE_EXPLOSION_EYE_2 (6)

#define EFFECT_TYPE_EXPLOSION_MEAT (7)
#define EFFECT_TYPE_EXPLOSION_BLOOD (8)

#define ARROW_DOWN 0
#define ARROW_UP 1
#define ARROW_LEFT 2
#define ARROW_RIGHT 3


// 画像データ
int cgChipBase[][10];		// 床チップ画像（配列）
int cgChipWall[][10];		// 壁チップ画像（配列）
int cgPlayer[][3];			// プレイヤー
int cgBox[];		// 箱
int cgEffect[][EFFECT_SHEETS_MAX];

int cgEnemy[][4];		//敵
int cgBoss[];
int cgTentacle[][6]; //ボスの触手

int cgCount[];
int cgLevel[];
extern int cgMeatCount;
extern int cgStageLevel;
extern int cgStageClear;


//音声データ
int sound[];
int bgm[];

int cgAOE[];

int cgCharaTalk[];

void ResourceInit();