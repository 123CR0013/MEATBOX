#pragma once
#define EFFECT_MAX	10 //EFFECT構造体配列の最大要素数

// エフェクト構造体
struct Effect
{
	// この配列要素を使用しているか
	int use;
	// エフェクトの種類
	int type;

	// エフェクトを再生するマップチップ座標
	int x, y;
	// 再生位置をずらすための値（ピクセル）
	int cx, cy;

	// アニメーションカウント
	int animationCnt;
	// アニメーションの再生速度
	int speed;
	// アニメーション画像の枚数
	int sheets;	//画像の枚数

	// 矢印エフェクトの方向（他のエフェクトでは使用しない）
	// 0:下 1:上 2:左 3:右
	int arrowDirection;
};

// エフェクト構造体配列の初期化
void EffectInit(Effect effect[]);
// エフェクトのセット
// x, y: エフェクトを再生するマップチップ座標
// type: エフェクトの種類
// arrowDirection: 矢印エフェクトの方向（他のエフェクトでは使用しない）
void SetEffect(Effect effect[], int x, int y, int type, int arrowDirection = -1);
// エフェクトのアニメーションカウントを進める処理
void EffectProcess(Effect effect[]);