#pragma once
#define EFFECT_MAX	10 //EFFECT構造体配列の最大要素数

struct Effect
{
	int x, y;	//エフェクトを再生する座標
	int cx, cy;
	int Cnt;	//
	int use;	//この配列要素を使用しているか
	int type;	//エフェクトの種類
	int speed;	//エフェクトの再生速度
	int sheets;	//画像の枚数

	int arrowDirection; //矢印エフェクトの方向
};


void EffectInit(Effect[]);

void SetEffect(Effect[], int, int, int, int arrowDirection = -1);

void EffectProcess(Effect[]);