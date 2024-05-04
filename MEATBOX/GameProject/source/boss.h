#pragma once

#define TENTACLE_MAX 4
#define TENTACLE_ATTACK_ROW 8

struct Boss {
	int x, y;
	int animCnt;
	int animSpeed;
};

struct Tentacle {
	int use;
	int x, y;		//触手の根元の座標
	int direction;	//攻撃方向（触手の向き）
	int range;		//攻撃範囲
	int row; //攻撃する列

	int isReady;	//攻撃待機かどうか（次に攻撃する触手が1）

	int isRemain;	//ステージ上に留まっているか

	int animCnt;
	int animSpeed;
};

struct AOE {
	int x, y;
	int use;

	int animCnt;
	int animSpeed;
	int sheets;
};

void BossInit();

void TentacleInit(Tentacle[]);
void AOEInit(AOE[]);
void SetTentacleReady(Tentacle[], AOE[]);
void SetBossAOE(Tentacle[], AOE[]);
void BossAttack(Tentacle[]);
void DeleteTentacle(Tentacle[]);