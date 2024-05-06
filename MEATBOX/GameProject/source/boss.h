#pragma once

#define TENTACLE_MAX 4
#define TENTACLE_ATTACK_ROW 8

// ボスの構造体
struct Boss {
	// ボスのマップチップ座標
	int x, y;
	// アニメーションカウント
	int animCnt;
	// アニメーション速度
	int animSpeed;
};

// 触手の構造体
struct Tentacle {
	// この要素を使用しているか
	int use;
	// 触手の根元の座標
	int x, y;
	// 攻撃方向（触手の向き）
	int direction;
	// 攻撃範囲
	int range;
	// 攻撃する列
	int row;

	// 攻撃待機かどうか（次に攻撃する触手は1、それ以外は0）
	int isReady;
	// ステージ上に留まっているか（攻撃状態かどうか）（0：留まっていない、1：留まっている）
	int isRemain;

	// アニメーションカウント
	int animCnt;
	// アニメーション速度
	int animSpeed;
};

// AOE（攻撃予兆範囲）の構造体
struct AOE {
	// この要素を使用しているか
	int use;
	// マップチップ座標
	int x, y;

	// アニメーションカウント
	int animCnt;
	// アニメーション速度
	int animSpeed;
	// 画像の枚数
	int sheets;
};

// ボスの初期化
void BossInit();
// 触手構造体の初期化
void TentacleInit(Tentacle[]);
// AOE構造体の初期化
void AOEInit(AOE[]);
// 触手を攻撃待機状態にする
void SetTentacleReady(Tentacle[], AOE[]);
// AOEを設定する
//ボスの攻撃範囲を数ターン前に表示する
void SetBossAOE(Tentacle[], AOE[]);
// ボスの攻撃処理
void BossAttack(Tentacle[]);
// 触手を消す処理（プレイヤーから触手への攻撃）
void DeleteTentacle(Tentacle[]);