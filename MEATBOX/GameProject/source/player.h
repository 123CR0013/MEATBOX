#pragma once


// プレイヤー情報
struct Player
{
	int x, y; // 座標（チップ単位）
	int moveCnt;

	int animCnt;
	int animSpeed;
	int IsSound;
	int sound_cnt;

	int stepCnt;
	int arrow;
};



void PlayerInit(Player *, int, int);