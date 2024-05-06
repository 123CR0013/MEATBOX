#include "DxLib.h"
#include "gamemain.h"
#include "scene.h"
#include "map.h"
#include "resource.h"
#include "player.h"
#include "enemy.h"
#include "effect.h"
#include "boss.h"
#include "box.h"

#include "fps.h"


//
// グローバル変数宣言
//

int gScene = SCENE_TITLE;

// ゲーム情報
int gKey;			// キー入力の情報
int gTrg;			// トリガ入力の情報
int gStageNo;		// ステージ番号
int gViewClearCnt;	// ステージクリア表示カウンタ

int boxAnimCnt;

int tentacleMoveCnt;


int bgmHandle;

//矢印を出すためのフラグ
//移動したタイミングで1, 矢印をセットしたら0に
int moveCnt; 

Player player;
Effect effect[EFFECT_MAX];

Enemy enemy[ENEMY_MAX];

//このルートを順番に通る
//移動先に障害物があったら折り返して、逆順に最初の地点まで行く
EnemyRoute enemyRoute[ENEMY_TOMATO_MAX][ROUTE_MAX]{
	//stage 0
	//stage 1
	//stage 2
	{
		{ 9, 4},
		{ 10, 4},
		{-1},
	},
	//stage 4
	{
		{20, 7},
		{20, 6},
		{19, 6},
		{19, 7},
		{-1},
	},
	//stage 5
	{
		{11, 8},
		{12, 8},
		{13, 8},
		{12, 8},
		{11, 8},
		{-1},
	},
	//stage 6（追加）
   {
	   {21, 6},
	   {21, 5},
	   {-1},
   },
	//stage 7
	{
		{16,11},
		{17,11},
		{17,10},
		{17, 9},
		{17, 8},
		{18, 8},
		{19, 8},
		{20, 8},
		{-1},
	},
	//stage 8
	
};

Boss boss;
Tentacle tentacle[4];
AOE aoe[8];

//
//初期化処理
//

// アプリの初期化
// 起動時に1回だけ実行される
void AppInit() {
	ResourceInit();

	SceneInit();
	bgmHandle = bgm[4];
	PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);
}

void GameInit() {
	// ステージデータ初期化
	gStageNo = 0;
	StageInit(gStageNo);

	enemyTomatoCnt = 0;
	EnemyInit(enemy, enemyRoute);
}

// ステージデータ初期化
void StageInit(int stageNo) {
	int x, y;
	MapInit(stageNo, &x, &y); //x, yにプレイヤーの開始地点の座標が入る
	PlayerInit(&player, x, y);

	EffectInit(effect);
	boxAnimCnt = 0;
	gViewClearCnt = 0;
	player.sound_cnt = 0;
	moveCnt = 1;

	player.stepCnt = 5;

	switch(gStageNo) {
	case 0:
		break;
	case 1:
		player.stepCnt = 15;
		break;
	case 2:
		player.stepCnt = 40;
		break;
	case 3:
		player.stepCnt = 40;
		break;
	case 4:
		player.stepCnt = 110;
		break;
	case 5:
		player.stepCnt = 135;
		break;
	case 6:
		player.stepCnt = 99;
		break;
	case 7:
		player.stepCnt = 41;
		break;
	case 8:
		player.stepCnt = 99;
		break;
	case 9:
		player.stepCnt = 30;

		BossInit();

		if (bgmHandle != bgm[5]) {
			StopSoundMem(bgmHandle);
			bgmHandle = bgm[5];
			PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);
		}
		break;
	}

	//ボスステージの場合
	if (gStageNo == BOSS_STAGE) {
		for (int i = 0; i < 4; i++) {
			AddBox(12, 9, 17, 10, player.x, player.y);
		}		
		TentacleInit(tentacle);
		tentacleMoveCnt = 0;
	}
}


// アプリの解放
// 終了時に1回だけ実行される
void AppRelease() {
}





//
// フレーム処理。1フレームに1回ずつ実行される
//

// フレーム処理：入力
void FrameInput() {
	// キーの入力、トリガ入力を得る
	int keyold = gKey;
	gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// キー入力を取得
	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
	gTrg = (gKey ^ keyold) & gKey;
}


// 指定した範囲内にミートボックスをランダムに追加する処理
// 左上・右下を指定し、その矩形の中を出現範囲とする
// プレイヤーの座標にはミートボックスを出現させない
void AddBox(int left, int top, int right, int bottom, int playerX, int playerY) {

	int rx, ry;
	while (1) {
		// ランダムに座標を決める
		rx = (rand() % (right - left + 1)) + left;
		ry = (rand() % (bottom - top + 1)) + top;

		// ランダムに決定した座標に既にミートボックスがない、かつ、プレイヤーの座標でない場合にループを抜ける
		if (box[ry * MAP_W + rx] != 1) {
			if (playerX != rx || playerY != ry) {
				break;
			}
		}
	}
	// box[] にミートボックスを追加
	box[ry * MAP_W + rx] = 1;

	// エフェクトをセット
	SetEffect(effect, rx, ry, EFFECT_TYPE_IMPACT);
}

int alphaFrag;

void SetArrowEffect() {
	if (moveCnt == 1) {	
		alphaFrag = 0;

		//一度現在表示されている矢印を消す
		for (int i = 0; i < EFFECT_MAX; i++) {
			if (effect[i].use == 1) {
				if (effect[i].type == EFFECT_TYPE_ARROW_YELLOW || effect[i].type == EFFECT_TYPE_ARROW_RED) {
					effect[i].use = 0;
				}
			}
		}

		//次の移動先の座標を取得して矢印をセットする
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (enemy[i].use == 1 && enemy[i].type == ENEMY_TYPE_TOMATO) {
				//移送先の情報を仮で入れる
				int x, y, n, order;
				n = enemy[i].moveCnt + enemy[i].moveOrder;
				x = enemyRoute[enemy[i].routeNum][n].x;
				y = enemyRoute[enemy[i].routeNum][n].y;
				order = enemy[i].moveOrder;

				//enemyRouteの終端にいたら、折り返し先の座標を取得する
				if (x == -1 || n == -1) { 				
					order *= -1;
					n = enemy[i].moveCnt + order;
					x = enemyRoute[enemy[i].routeNum][n].x;
					y = enemyRoute[enemy[i].routeNum][n].y;			
				
				}

				//敵が移動できない場合は矢印を表示しない
				if (map[y * MAP_W + x] == 1 || box[y * MAP_W + x] == 1) { 
					alphaFrag = 1;
					//break; 
				
				}

				//敵が動くまで2ターンあったら黄色い矢印をセットする
				if (player.moveCnt == 0) {
					//黄色
					if (enemy[i].x > x) {
						//左
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_YELLOW, ARROW_LEFT);
					}
					else if (enemy[i].x < x) {
						//右
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_YELLOW, ARROW_RIGHT);
					}
					else if (enemy[i].y > y) {
						//上
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_YELLOW, ARROW_UP);
					}
					else if (enemy[i].y < y) {
						//上
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_YELLOW, ARROW_DOWN);
					}
				}
				//敵が次のターンに移動するなら赤い矢印をセットする
				else if (player.moveCnt == 1) {
					//赤
					if (enemy[i].x > x) {
						//左
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_RED, ARROW_LEFT);
					}
					else if (enemy[i].x < x) {
						//右
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_RED, ARROW_RIGHT);
					}
					else if (enemy[i].y > y) {
						//上
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_RED, ARROW_UP);
					}
					else if (enemy[i].y < y) {
						//上
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_RED, ARROW_DOWN);
					}
				}

			}
		}

		moveCnt = 0;
	}
}



void PlayerMove() {
	int IsMove = 0;
	// 移動前の場所を取っておく
	int old_x = player.x;
	int old_y = player.y;

	// 移動方向用変数
	int move_x = 0;
	int move_y = 0;
	
	//移動キー
	if (gTrg & (PAD_INPUT_LEFT + PAD_INPUT_RIGHT + PAD_INPUT_UP + PAD_INPUT_DOWN)) { //すべて加算した後に（2進数で表現した時に繰り上げがない）gTrgと排他的論理和
		PlaySoundMem(sound[0], DX_PLAYTYPE_BACK);

		if (gStageNo != BOSS_STAGE) {
			player.stepCnt--;
		}
		else {
			tentacleMoveCnt++;
		}		
	}
			
	// キー入力を判定して、主人公を移動させる
	if(gTrg & PAD_INPUT_LEFT) {
		player.x--;
		move_x = -1;
		player.moveCnt++;
		player.arrow = 0;
		IsMove = 1;
		moveCnt = 1;
	}
	if(gTrg & PAD_INPUT_RIGHT) {
		player.x++;
		move_x = 1;
		player.moveCnt++;
		player.arrow = 1;
		IsMove = 1;
		moveCnt = 1;
	}
	if (move_x == 0) {	// 斜め移動しないように、横移動を優先
		if (gTrg & PAD_INPUT_UP) { 
			player.y--; 
			move_y = -1; 
			player.moveCnt++;
			IsMove = 1;
			moveCnt = 1;
		}
		if (gTrg & PAD_INPUT_DOWN) { 
			player.y++; 
			move_y = 1; 
			player.moveCnt++;
			IsMove = 1;
			moveCnt = 1;
		}
	}

	// 移動した先が壁か？
	if (map[player.y * MAP_W + player.x] >= 50 || map[player.y * MAP_W + player.x] == -1)
	{
		// 移動した先が壁だったので、移動前の場所に戻す
		player.x = old_x;
		player.y = old_y;
		IsMove = 0;
	}

	//プレイヤーと敵がぶつかったらゲームオーバー
	if (enemyMap[player.y * MAP_W + player.x] != 0) {
		
		gScene = SCENE_GAMEOVER;
	}

	// 移動した先に箱はあるか？
	if (box[player.y * MAP_W + player.x] == 1)
	{
		// 移動した先に箱があった。
		// 押せるかどうか調べたい
		int push_ok = 1;

		// さらに同じ方向のその先の座標を求める（移動方向用変数を足す）
		int next_x = player.x + move_x;
		int next_y = player.y + move_y;

		// その先に、壁があるかを調べる
		if (map[next_y * MAP_W + next_x] >= 50 || map[next_y * MAP_W + next_x] == -1)
		{
			// 壁があるので押せない
			push_ok = 0;
			IsMove = 0;
		}

		// その先に、箱があるかを調べる
		if (box[next_y * MAP_W + next_x] == 1)
		{
			// 箱があるので押せない
			push_ok = 0;
			IsMove = 0;
		}

		int crush_ok = 0;

		//押しつぶし
		if (enemyMap[next_y * MAP_W + next_x] != 0) {
			if (map[(next_y + move_y) * MAP_W + (next_x + move_x)] >= 50 || box[(next_y + move_y) * MAP_W + (next_x + move_x)] == 1 || map[(next_y + move_y) * MAP_W + (next_x + move_x)] == -1) {
				push_ok = 1;
				crush_ok = 1;
			}
			else {
				push_ok = 0;
				IsMove = 0;
				SetEffect(effect, old_x, old_y, EFFECT_TYPE_HATENA);
			}
		}

		// 調べた結果、押せる？
		if (push_ok == 1)
		{
			// 押せる。箱の位置を移動する
			// まず、プレイヤーが乗った箱を消し、
			box[player.y * MAP_W + player.x] = 0;

			// 移動先に箱を書き込む
			box[next_y * MAP_W + next_x] = 1;

			SetEffect(effect, next_x, next_y, EFFECT_TYPE_IMPACT);
			PlaySoundMem(sound[2], DX_PLAYTYPE_BACK);

			if (crush_ok == 1) {
				if (gStageNo != BOSS_STAGE) {
					enemyMap[next_y * MAP_W + next_x] = 0;

					for (int i = 0; i < ENEMY_MAX; i++) {
						if (next_x == enemy[i].x && next_y == enemy[i].y) {
							enemy[i].use = 0;
							PlaySoundMem(sound[1], DX_PLAYTYPE_BACK);

							SetEffect(effect, next_x - (480 / CHIP_W), next_y - (270 / CHIP_H), EFFECT_TYPE_EXPLOSION_EYE_1);
							SetEffect(effect, 480 / CHIP_W, 580 / CHIP_H, EFFECT_TYPE_EXPLOSION_EYE_2);

							SetEffect(effect, next_x - (480 / CHIP_W), next_y - (270 / CHIP_H), EFFECT_TYPE_EXPLOSION_MEAT);
							SetEffect(effect, next_x - (480 / CHIP_W), next_y - (270 / CHIP_H), EFFECT_TYPE_EXPLOSION_BLOOD);
						}
					}
				}
				else {
					PlaySoundMem(sound[1], DX_PLAYTYPE_BACK);

					SetEffect(effect, next_x - (480 / CHIP_W), next_y - (270 / CHIP_H), EFFECT_TYPE_EXPLOSION_MEAT);
					SetEffect(effect, next_x - (480 / CHIP_W), next_y - (270 / CHIP_H), EFFECT_TYPE_EXPLOSION_BLOOD);
					DeleteTentacle(tentacle);
				}
				
				
			}
		}
		else
		{
			// 押せないので、プレイヤーの位置を移動前の場所に戻す
			player.x = old_x;
			player.y = old_y;
		}
	}
	if (IsMove == 1) {
		SetEffect(effect, old_x, old_y, 0);
	}
}

int bossDraw_cx = 0;
int bossDraw_cy = 0;

 
// フレーム処理：計算
void FrameProcess() {
	if (player.stepCnt == 0) {
		gScene = SCENE_GAMEOVER;
	}
	boxAnimCnt++;
	boss.animCnt++;
	
	
	// 敵をすべて倒したか
	int all_get = 1;	
	
	//BOSSステージ以外なら
	if(gStageNo != BOSS_STAGE){
		// 全部調べて1のままなら、全部倒した
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (enemy[i].use == 1) {
				enemy[i].animCnt++;
				all_get = 0;
			}
		}
	}
	else if(gStageNo == BOSS_STAGE){
		// 全部調べて1のままなら、全部倒した
		for (int i = 0; i < TENTACLE_MAX; i++) {
			if (tentacle[i].use == 1) {
				tentacle[i].animCnt++;
				all_get = 0;
			}
		}
	}

		


	player.animCnt++;
	EffectProcess(effect);

	// 敵が残っていたら、ゲームの処理をする
	if (all_get == 0)
	{
		PlayerMove();
		
		if (gStageNo == BOSS_STAGE) {
			if (player.stepCnt == 0) { gScene = SCENE_GAMECLEAR; return; }
			switch (tentacleMoveCnt % 9)
			{
			case 0:
				SetTentacleReady(tentacle, aoe);

				int x, y, n;
				n = 0;
				for (y = 0; y < MAP_H; y++) {
					for (x = 0; x < MAP_W; x++) {
						// box[] から、チップ番号を取り出す
						int chip_no = box[y * MAP_W + x];
						if (chip_no != 0)
						{
							n++;
						}
					}
				}
				while (n < 4) {
					AddBox(12, 9, 17, 10, player.x, player.y);
					n++;
				}

				tentacleMoveCnt++;
				break;
			case 3:
				SetBossAOE(tentacle, aoe);
				break;
			case 5:
				BossAttack(tentacle);
				AOEInit(aoe);
				tentacleMoveCnt++;
				break;

			}
		}
		

		if (player.moveCnt == 0) {
			SetArrowEffect();
		}else if (player.moveCnt == 1) {
			SetArrowEffect();
		}else if (player.moveCnt == 2) { //プレイヤーが2歩動くたびに、敵が1歩動く
			EnemyMove(enemy, enemyRoute);
			player.moveCnt = 0;
		}

		
		// ステージデータリセット（やり直し）
		if (gTrg & PAD_INPUT_1) {	// [z]
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (enemy[i].type == ENEMY_TYPE_TOMATO) {
					enemyTomatoCnt--;
				}
			}
			StageInit(gStageNo);
			EnemyInit(enemy, enemyRoute);
		}
		








		// 開発用。次のステージへ
		if (gTrg & PAD_INPUT_7) { // [q] キー
			if (gStageNo + 1 < STAGE_MAX) {
				gStageNo++;
				/*if(gStageNo == 7) {
					gStageNo = BOSS_STAGE;
				}*/
				StageInit(gStageNo);
				EnemyInit(enemy, enemyRoute);
			}
		}

		//開発用 ボスステージへ
		if (gTrg & PAD_INPUT_8) { // [w] キー
			if (gStageNo + 1 < STAGE_MAX) {
				gStageNo = BOSS_STAGE;
				StageInit(gStageNo);
				EnemyInit(enemy, enemyRoute);
			}
		}



#ifdef _DEBUG
		//if (gTrg & PAD_INPUT_1) {	// [v]
		//	AddBox(12, 9, 17, 10, player.x, player.y);
		//}

#endif // _DEBUG


	}
	else {
		// すべての敵を倒した
		gScene = SCENE_GAME;
		if (gViewClearCnt == 0) {
			// ステージクリア表示へ
			gViewClearCnt = 120;		// 表示フレーム数

			if (gStageNo == BOSS_STAGE) {
				PlaySoundMem(sound[3], DX_PLAYTYPE_BACK);
				gViewClearCnt = 150;		// 表示フレーム数

				for (int i = 0; i < 16; i++) {
					if (i % 4 < 2) {
						GraphFilter(cgBoss[i], DX_GRAPH_FILTER_HSB, 0, 0, 0, 255);
					}
				}
			}
		}
		else {
			

			

			if (gStageNo == BOSS_STAGE) {
				if (gViewClearCnt % 60 == 0) {
					//PlaySoundMem(sound[1], DX_PLAYTYPE_BACK);

					int x = 8;
					int y = 3;

					SetEffect(effect, x, y, EFFECT_TYPE_EXPLOSION_MEAT);
					SetEffect(effect, x, y, EFFECT_TYPE_EXPLOSION_BLOOD);



				}

				if (gViewClearCnt % 10 >= 4) {
					bossDraw_cx = 20;				
				}
				else {
					bossDraw_cx = -20;
				}				

				if (gViewClearCnt % 10 == 0) {
					bossDraw_cy += 2;
				}
			}
			// 表示フレームを減らす
			gViewClearCnt--;

			if (gViewClearCnt == 0) {
				if (gStageNo == BOSS_STAGE) {
					gScene = SCENE_GAMECLEAR;

					StopSoundMem(bgmHandle);
					bgmHandle = bgm[6];
					PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);
				}
				else {

					// 減らしきったら次のステージへ
					if (gStageNo + 1 < STAGE_MAX) {



						gStageNo++;

						StageInit(gStageNo);
						EnemyInit(enemy, enemyRoute);
					}

				}
			}
		}
	}
}



void GameDraw() {
	// 画像表示 ////////////////////////////////////////

	if(gStageNo == BOSS_STAGE) {
		//ボス
		

		//if (gViewClearCnt != 0) {
		//	if (gViewClearCnt % 20 < 10 ) {
		//		/*SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		//		DrawGraph((SCREEN_W / 2) - 128 + bossDraw_cx, 3 * CHIP_H, cgBoss[(boss.animCnt / 8) % 16], TRUE);
		//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);*/
		//		GraphFilter(cgBoss[(boss.animCnt / 8) % 16], DX_GRAPH_FILTER_HSB, 0, 0, 0, 255);
		//	}
		//}


		DrawGraph((SCREEN_W / 2) - 128 + bossDraw_cx, 3 * CHIP_H + bossDraw_cy, cgBoss[(boss.animCnt / 8) % 16], TRUE);
	}

	// マップチップを for ループでひとつひとつ描画する
	int x, y;
	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			// map[] から、チップ番号を取り出す
			int chip_no = map[y * MAP_W + x];

			if (chip_no != -1) {
				// チップ番号に合わせた画像を、マス目に沿って描画する
				if (chip_no < 50) {
					DrawGraph(x * CHIP_W, y * CHIP_H, cgChipBase[chip_no][0], FALSE);
				}
				else {
					if((54 <= chip_no && chip_no <= 59) || chip_no == 67) {

						int n = 0;
						while (cgChipWall[chip_no - 50][n] != -1) { n++; }
						DrawGraph(x * CHIP_W, y * CHIP_H, cgChipWall[chip_no - 50][(boxAnimCnt / 12) % n], FALSE);
					}
					else {
						DrawGraph(x * CHIP_W, y * CHIP_H, cgChipWall[chip_no - 50][0], FALSE);
					}
					
				}
				
			}			
		}
	}

	// 箱もforループで描画する
	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			// box[] から、チップ番号を取り出す
			int chip_no = box[y * MAP_W + x];
			if (chip_no != 0)
			{
				int animTbl[] = { 0, 1, 2, 2, 2, 1, 0};
				DrawGraph(x * CHIP_W, y * CHIP_H - CHIP_H / 10, cgBox[animTbl[(boxAnimCnt / 12) % 7]], TRUE);
			}
		}
	}


	//敵の描画
	int tomatoAnimTbl[] = { 0, 1, 2, 1 };
	int namakoAnimTbl[] = { 0, 1, 2, 1 };

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i].use == 1) {
			if (enemy[i].type == ENEMY_TYPE_TOMATO) {
				if (enemy[i].animCnt <= 16 * 4) {
					DrawGraph(enemy[i].x * CHIP_W, enemy[i].y * CHIP_H - CHIP_H / 4, cgEnemy[enemy[i].type][3], TRUE);
				}
				else {
					DrawGraph(enemy[i].x * CHIP_W, enemy[i].y * CHIP_H - CHIP_H / 4, cgEnemy[enemy[i].type][tomatoAnimTbl[(enemy[i].animCnt / enemy[i].animSpeed) % 4]], TRUE);

				}
			}
			else {
				DrawGraph(enemy[i].x * CHIP_W, enemy[i].y * CHIP_H - 10, cgEnemy[enemy[i].type][namakoAnimTbl[(enemy[i].animCnt / enemy[i].animSpeed) % 4]], TRUE);
			}

		}
	}


	
	

	

	// プレイヤー
	int animTbl[] = { 0, 1, 2, 2, 2 ,1 };
	DrawGraph(player.x* CHIP_W, player.y* CHIP_H - CHIP_H / 4, cgPlayer[player.arrow][animTbl[(player.animCnt / player.animSpeed) % 6]], TRUE);

	if(gStageNo == BOSS_STAGE) {
		//触手
		for(int i = 0; i < TENTACLE_MAX; i++) {
			if(tentacle[i].use == 1) {


				if(tentacle[i].direction == 1) { //左
					if(tentacle[i].isRemain == 0) {
						//待機
						DrawGraph((tentacle[i].x - 1) * CHIP_W, tentacle[i].y * CHIP_H - 96, cgTentacle[0][(tentacle[i].animCnt / tentacle[i].animSpeed) % 2], TRUE);
					}
					else {
						//攻撃
						DrawGraph((tentacle[i].x + 1) * CHIP_W - CHIP_W / 2, (tentacle[i].row + TENTACLE_ATTACK_ROW)* CHIP_H, cgTentacle[0][((tentacle[i].animCnt / tentacle[i].animSpeed) % 2) + 4], TRUE);
					}
				}




				else { //右
					if(tentacle[i].isRemain == 0) {
						//待機
						DrawGraph((tentacle[i].x + 1) * CHIP_W - 450, tentacle[i].y * CHIP_H - 96, cgTentacle[1][(tentacle[i].animCnt / tentacle[i].animSpeed) % 2], TRUE);
					}
					else {
						//攻撃
						DrawGraph((tentacle[i].x - 1) * CHIP_W - 450 + CHIP_W / 2, (tentacle[i].row + TENTACLE_ATTACK_ROW) * CHIP_H, cgTentacle[1][((tentacle[i].animCnt / tentacle[i].animSpeed) % 3) + 3], TRUE);
					}
				}
			}
		}
	}

	//エフェクト
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].use == 1) {
			if (effect[i].type == EFFECT_TYPE_ARROW_RED || effect[i].type == EFFECT_TYPE_ARROW_YELLOW) {
				if (alphaFrag == 1) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 140);
				}
				DrawGraph(effect[i].x * CHIP_W, effect[i].y * CHIP_H, cgEffect[effect[i].type][effect[i].arrowDirection], TRUE);
				
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			}
			else {
				DrawGraph(effect[i].x * CHIP_W + effect[i].cx, effect[i].y * CHIP_H + effect[i].cy, cgEffect[effect[i].type][(effect[i].Cnt / effect[i].speed) % effect[i].sheets], TRUE);
			}
		}
	}

	//ボスステージ
	if (gStageNo == BOSS_STAGE) {
		//AOE
		for (int i = 0; i < 8; i++) {
			if (aoe[i].use == 1) {
				DrawGraph(aoe[i].x * CHIP_W, aoe[i].y * CHIP_H, cgAOE[(aoe[i].animCnt / aoe[i].animSpeed) % aoe[i].sheets], TRUE);
				aoe[i].animCnt++;
			}
		}
	}


	//歩数カウンター
	DrawGraph(0, 0, cgMeatCount, TRUE);
	if (gStageNo != BOSS_STAGE) {
		//歩数が3桁の場合
		if (player.stepCnt >= 100) {
			DrawGraph(180, 180, cgCount[player.stepCnt / 100], TRUE);
			DrawGraph(220, 180, cgCount[(player.stepCnt / 10) % 10], TRUE);
			DrawGraph(260, 180, cgCount[player.stepCnt % 10], TRUE);
		}
		//歩数が2桁の場合
		else if (player.stepCnt > 9) {
			DrawGraph(189, 180, cgCount[player.stepCnt / 10], TRUE);
			DrawGraph(249, 180, cgCount[player.stepCnt % 10], TRUE);
		}
		//歩数が1桁の場合
		else if (player.stepCnt <= 9) {
			DrawGraph(220, 180, cgCount[player.stepCnt % 10], TRUE);
		}
	}
	else {
		//∞

		if (gStageNo == BOSS_STAGE) {

			int stepX = 205;
			int stepY = 195;

			int stepW = 67;
			int stepH = 37;

			DrawModiGraph(
				stepX, stepY + stepH,
				stepX, stepY,
				stepX + stepW, stepY,
				stepX + stepW, stepY + stepH,
				cgCount[8], TRUE
			);
		}


	}


	//ステージ番号表示
	DrawGraph(0, 0, cgStageLevel, TRUE);

	if(gStageNo <= 10) {
		DrawGraph(1706, 914, cgLevel[gStageNo % 10], TRUE);
	}

	int  h = 1;
	int line = 10;
	DrawString(SCREEN_W - 250, h *(16 + line), "[矢印] キーで移動", GetColor(255, 255, 255));			 h++;
	DrawString(SCREEN_W - 250, h *(16 + line), "[Z] キーでリトライ", GetColor(255, 255, 255));			 h++;
	DrawString(SCREEN_W - 250, h *(16 + line), "[esc] キーでゲーム終了", GetColor(255, 255, 255));	 h++;



	// クリア表示
	if(gViewClearCnt != 0) {
		if (gStageNo != BOSS_STAGE) {
			if (gViewClearCnt <= 90) {
				DrawGraph(0, 0, cgStageClear, TRUE);
			}
		}
	}


#ifdef _DEBUG

	////以下開発用
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "gScene %d", gScene);

	////エフェクト
	//for (int i = 0; i < EFFECT_MAX; i++) {
	//	DrawFormatString(0, 100 + 16 * i, GetColor(255, 255, 255), "use %d, x %d, y %d, Cnt %d", effect[i].use, effect[i].x, effect[i].y, effect[i].Cnt);
	//}

	// プレイヤー
	//DrawFormatString(500, 100 - 16, GetColor(255, 255, 255), "x %d, y %d, moveCnt %d", player.x, player.y, player.moveCnt);

	//敵
	//for (int i = 0; i < ENEMY_MAX; i++) {
	//	DrawFormatString(500, 100 + 16 * i, GetColor(255, 255, 255), "enemy_no: %d, use %d, x %d, y %d, moveCnt %d, moveOrder %d Cnt %d type %d animCnt %d", i, enemy[i].use, enemy[i].x, enemy[i].y, enemy[i].moveCnt, enemy[i].moveOrder, enemy[i].routeNum, enemy[i].type, enemy[i].animCnt);
	//}

	//触手
	/*DrawFormatString(100, 100, GetColor(255, 255, 255), "tentacleMoveCnt: %d",tentacleMoveCnt % 9);

	for (int i = 0; i < TENTACLE_MAX; i++) {
		DrawFormatString(100, 100 + 16 * (20+i), GetColor(255, 255, 255), "tentacle_no: %d, use %d, x %d, y %d, dir %d, isReady %d, isRemain %d", i, tentacle[i].use, tentacle[i].x, tentacle[i].y, tentacle[i].direction, tentacle[i].isReady, tentacle[i].isRemain);
	}*/

	//AOE
	//for (int i = 0; i < 8; i++) {
	//	DrawFormatString(500, 100 + 16 * (30 + i), GetColor(255, 255, 255), "AOE_no: %d, use %d, x %d, y %d", i, aoe[i].use, aoe[i].x, aoe[i].y);
	//}

	//DrawFormatString(100, 100 - 16, GetColor(255, 255, 255), "boxAnimCnt %d,", boxAnimCnt);

#endif
}


// フレーム処理：描画
void FrameDraw() {

	ClearDrawScreen();						// 画面を初期化する

	SceneManage(gScene);
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "gScene %d", gScene);

	

#ifdef _DEBUG
	draw_fps(0, 0);
#endif

	ScreenFlip();							// 裏画面の内容を表画面に反映させる
}

int scene_key = 0;
int scene_trg = 0;

void GameMain()
{
	//キーが押されるまで無限ループ

	AppInit();	// 初期化

	// 1フレームループを組む ----------------------------------------------------------
	while (ProcessMessage() == 0)		// プログラムが終了するまでループ
	{
		//int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		// キーの入力、トリガ入力を得る
		int scene_keyold = scene_key;
		scene_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// キー入力を取得
		// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
		int scene_trg = (scene_key ^ scene_keyold) & scene_key;

		switch (gScene)
		{
		case SCENE_TITLE: //タイトル画面
			if ((scene_trg & PAD_INPUT_10) || (scene_trg & PAD_INPUT_1)) { //スペースか zキー
				gScene = SCENE_CHARATALK;				
				talkNum = 0;
			}
			break;
		case SCENE_GAME: //ゲーム画面
			FrameInput();	// 入力
			FrameProcess();	// 計算
			break;
		case SCENE_GAMEOVER: //ゲームオーバー画面
			if ((scene_trg & PAD_INPUT_10) || (scene_trg & PAD_INPUT_1)) {
				gScene = SCENE_GAME;
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (enemy[i].type == ENEMY_TYPE_TOMATO) {
						enemyTomatoCnt--;
					}
				}
				StageInit(gStageNo);
				EnemyInit(enemy, enemyRoute);
			}
			break;
		case SCENE_GAMECLEAR: //ゲームクリア画面
			if ((scene_trg & PAD_INPUT_10) || (scene_trg & PAD_INPUT_1)) {
				gScene = SCENE_TITLE;

				StopSoundMem(bgmHandle);
				bgmHandle = bgm[4];
				PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);
			}
			break;

		case SCENE_CHARATALK: //キャラ会話

			//if((scene_trg & PAD_INPUT_10) || (scene_trg & PAD_INPUT_2)) { //スペースか xキー（Bボタン）
			//	talkNum++;
			//}

			//if(talkNum > 16) {
			//	gScene = SCENE_GAME;
			//	GameInit();
			//}


			if ((scene_trg & PAD_INPUT_10) || (scene_trg & PAD_INPUT_1)) {
				talkNum++;				
			}

			if (talkNum >= 2) {
				gScene = SCENE_GAME;
				GameInit();
			}

			break;

		}
		
		
		FrameDraw();	// 描画


		// フレームレートの固定
		fps_wait();




		if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)	// ESCAPEキーが押されているかを調べる
			break;			// 押されていたらメインループを抜ける
	}

	AppRelease();	// 解放
}
