#include "DxLib.h"
#include "boss.h"
#include "map.h"
#include "resource.h"

void BossInit() {
	//
	// ボス
	//

	// 一度フィルターをかけると戻せないので，この関数でbossステージ開始時に毎回読み込みをする

	for (int i = 0; i < 16; i++) {
		DeleteGraph(cgBoss[i]);
	}

	cgBoss[0] = LoadGraph("res/enemy/boss/boss1.png");
	cgBoss[1] = LoadGraph("res/enemy/boss/boss2.png");
	cgBoss[2] = LoadGraph("res/enemy/boss/boss3.png");
	cgBoss[3] = LoadGraph("res/enemy/boss/boss4.png");
	cgBoss[4] = LoadGraph("res/enemy/boss/boss5.png");
	cgBoss[5] = LoadGraph("res/enemy/boss/boss6.png");
	cgBoss[6] = LoadGraph("res/enemy/boss/boss7.png");
	cgBoss[7] = LoadGraph("res/enemy/boss/boss8.png");
	cgBoss[8] = LoadGraph("res/enemy/boss/boss9.png");
	cgBoss[9] = LoadGraph("res/enemy/boss/boss10.png");
	cgBoss[10] = LoadGraph("res/enemy/boss/boss11.png");
	cgBoss[11] = LoadGraph("res/enemy/boss/boss12.png");
	cgBoss[12] = LoadGraph("res/enemy/boss/boss13.png");
	cgBoss[13] = LoadGraph("res/enemy/boss/boss14.png");
	cgBoss[14] = LoadGraph("res/enemy/boss/boss15.png");
	cgBoss[15] = LoadGraph("res/enemy/boss/boss16.png");
}

//触手の初期化（tentacle構造体配列）
void TentacleInit(Tentacle tentacle[]) {
	int x, y;
	x = 10;
	y = 8;
	for (int i = 0; i < TENTACLE_MAX; i++) {
		if (i % 2 == 0) {
			tentacle[i].x = x;
			tentacle[i].direction = 1;
		}else{
			tentacle[i].x = 29 - x;
			tentacle[i].direction = -1;
		}
		tentacle[i].use = 1;
		tentacle[i].y = y + i;
		tentacle[i].range = 8;
		tentacle[i].row = -1;

		tentacle[i].isReady = 0;
		tentacle[i].isRemain = 0;

		tentacle[i].animCnt = 0;
		tentacle[i].animSpeed = 16;
	}
}

//攻撃予兆範囲の初期化（AOE構造体配列）
void AOEInit(AOE aoe[]) {
	for (int i = 0; i < 8; i++) {
		aoe[i].use = 0;
		aoe[i].animCnt = 0;
		aoe[i].animSpeed = 8;
		aoe[i].sheets = 2;
	}
}

//触手を攻撃待機状態にする
void SetTentacleReady(Tentacle tentacle[], AOE aoe[]) {
	//AOE構造体の初期化
	AOEInit(aoe);

	//現在攻撃中の触手の状態を初期化（非攻撃状態に）
	for (int i = 0; i < TENTACLE_MAX; i++) {
		if (tentacle[i].isRemain == 1) {
			tentacle[i].isRemain = 0;
			for (int j = 1; j <= tentacle[i].range; j++) {
				enemyMap[(tentacle[i].row + TENTACLE_ATTACK_ROW) * MAP_W + tentacle[i].x + (tentacle[i].direction * j)] = 0;
			}
		}
	}

	int remainTentacle = 0;
	for (int i = 0; i < TENTACLE_MAX; i++) {
		if (tentacle[i].use == 1) {
			remainTentacle = 1;
		}
	}

	if (remainTentacle == 1) {

		//次に攻撃する触手をランダムに決定
		int r;
		while (1) { //すでに倒された触手が選ばれないようにする
			r = rand() % TENTACLE_MAX;
			if (tentacle[r].use != 0) break; //まだ残っている触手が選ばれたらループを抜ける
		}
		tentacle[r].isReady = 1;
		tentacle[r].row = rand() % 4;
	}
}

//ボスの攻撃範囲を数ターン前に表示する
void SetBossAOE(Tentacle tentacle[], AOE aoe[]) {
	for (int i = 0; i < TENTACLE_MAX; i++) {

		//攻撃待機状態の触手の攻撃範囲にAOEをセットする
		if (tentacle[i].isReady == 1) {
			for (int j = 1; j <= tentacle[i].range; j++) {
				aoe[j - 1].x = tentacle[i].x + (tentacle[i].direction * j);
				aoe[j - 1].y = tentacle[i].row + TENTACLE_ATTACK_ROW;
				aoe[j - 1].use = 1;
			}
			break;
		}

	}
}

//触手の攻撃
void BossAttack(Tentacle tentacle[]) {
	for (int i = 0; i < TENTACLE_MAX; i++) {
		if (tentacle[i].isReady == 1) {

			//攻撃処理
			for (int j = 1; j <= tentacle[i].range; j++) {
				//攻撃範囲内の箱を壊す
				box[(tentacle[i].row + TENTACLE_ATTACK_ROW) * MAP_W + tentacle[i].x + (tentacle[i].direction * j)] = 0;
				//攻撃範囲内に敵がいる判定をつける
				enemyMap[(tentacle[i].row + TENTACLE_ATTACK_ROW) * MAP_W + tentacle[i].x + (tentacle[i].direction * j)] = 9;
			}

			//攻撃待機状態の解除
			tentacle[i].isReady = 0;
			//攻撃状態の設定
			tentacle[i].isRemain = 1;

			PlaySoundMem(sound[4], DX_PLAYTYPE_BACK);
			break;
		}
	}
}

//触手を消す（プレイヤーから触手への攻撃）
void DeleteTentacle(Tentacle tentacle[]) {
	for (int i = 0; i < TENTACLE_MAX; i++) {

		//触手をつぶす		
		if (tentacle[i].isRemain == 1) {
			//攻撃状態の触手を消す
			tentacle[i].use = 0;

			//攻撃範囲内の敵がいる判定を消す
			for (int j = 1; j <= tentacle[i].range; j++) {
				enemyMap[(tentacle[i].row + TENTACLE_ATTACK_ROW) * MAP_W + tentacle[i].x + (tentacle[i].direction * j)] = 0;
			}
			break;
		}
	}
}
