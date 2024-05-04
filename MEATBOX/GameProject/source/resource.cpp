#include "DxLib.h"
#include "resource.h"
#include "enemy.h"
#include "effect.h"



// 画像データ
int cgChipBase[50][10];		// 床チップ画像（配列）
int cgChipWall[50][10];		// 壁チップ画像（配列）
int cgPlayer[2][3];		// プレイヤー
int cgBox[3];		// 箱
int cgEffect[EFFECT_TYPE_MAX][EFFECT_SHEETS_MAX];

int cgEnemy[ENEMY_TYPE_MAX][4];		//敵
int cgBoss[16];
int cgTentacle[2][6];

int cgCount[10];
int cgLevel[10];
int cgMeatCount;
int cgStageLevel;
int cgStageClear;

//音声データ
int sound[10];
int bgm[10];

int cgAOE[2];

int cgCharaTalk[17];


void ResourceInit() {

	//
	// マップチップ
	//

	//床
	cgChipBase[0][0] = LoadGraph("res/bg/base/blue simple tile.png");
	cgChipBase[1][0] = LoadGraph("res/bg/base/simpletile down 1.png");
	cgChipBase[2][0] = LoadGraph("res/bg/base/simpletile down 2.png");
	cgChipBase[3][0] = LoadGraph("res/bg/base/simpletile down 3.png");
	cgChipBase[4][0] = LoadGraph("res/bg/base/simpletile down 4.png");

	cgChipBase[10][0] = LoadGraph("res/bg/base/blue tile.png");
	cgChipBase[11][0] = LoadGraph("res/bg/base/tile down 1.png");
	cgChipBase[12][0] = LoadGraph("res/bg/base/tile down 2.png");
	cgChipBase[13][0] = LoadGraph("res/bg/base/tile down 3.png");
	cgChipBase[14][0] = LoadGraph("res/bg/base/tile down 4.png");

	cgChipBase[20][0] = LoadGraph("res/bg/base/drain.png");
	cgChipBase[21][0] = LoadGraph("res/bg/base/drain down 1.png");
	cgChipBase[22][0] = LoadGraph("res/bg/base/drain down 2.png");
	cgChipBase[23][0] = LoadGraph("res/bg/base/drain down 3.png");
	cgChipBase[24][0] = LoadGraph("res/bg/base/drain down 4.png");

	cgChipBase[30][0] = LoadGraph("res/bg/base/escape.png");

	cgChipBase[40][0] = LoadGraph("res/bg/base/BOSS simple tile.png");
	cgChipBase[41][0] = LoadGraph("res/bg/base/boss tile.png");

	cgChipBase[42][0] = LoadGraph("res/bg/base/meat piece drain.png");
	cgChipBase[43][0] = LoadGraph("res/bg/base/meat piece simple.png");
	cgChipBase[44][0] = LoadGraph("res/bg/base/meat piece tile.png");

	//壁
	cgChipWall[0][0] = LoadGraph("res/bg/wall/wall1.png");
	cgChipWall[1][0] = LoadGraph("res/bg/wall/wall2.png");

	cgChipWall[2][0] = LoadGraph("res/bg/wall/holewall1.png");
	cgChipWall[3][0] = LoadGraph("res/bg/wall/holewall2.png");

	cgChipWall[4][0] = LoadGraph("res/bg/wall/danger1.png");
	cgChipWall[4][1] = LoadGraph("res/bg/wall/danger2.png");
	cgChipWall[4][2] = -1;

	cgChipWall[5][0] = LoadGraph("res/bg/wall/liquid holewall1.png");
	cgChipWall[5][1] = LoadGraph("res/bg/wall/liquid holewall2.png");
	cgChipWall[5][2] = LoadGraph("res/bg/wall/liquid holewall3.png");
	cgChipWall[5][3] = LoadGraph("res/bg/wall/liquid holewall4.png");
	cgChipWall[5][4] = LoadGraph("res/bg/wall/liquid holewall5.png");
	cgChipWall[5][5] = -1;

	cgChipWall[6][0] = LoadGraph("res/bg/wall/brain1.png");
	cgChipWall[6][1] = LoadGraph("res/bg/wall/brain2.png");
	cgChipWall[6][2] = LoadGraph("res/bg/wall/brain3.png");
	cgChipWall[6][3] = LoadGraph("res/bg/wall/brain4.png");
	cgChipWall[6][4] = LoadGraph("res/bg/wall/brain5.png");
	cgChipWall[6][5] = -1;

	cgChipWall[7][0] = LoadGraph("res/bg/wall/table meat eye1 .png");
	cgChipWall[7][1] = LoadGraph("res/bg/wall/table meat eye2 .png");
	cgChipWall[7][2] = LoadGraph("res/bg/wall/table meat eye3 .png");
	cgChipWall[7][3] = LoadGraph("res/bg/wall/table meat eye4 .png");
	cgChipWall[7][4] = LoadGraph("res/bg/wall/table meat eye5 .png");
	cgChipWall[7][5] = LoadGraph("res/bg/wall/table meat eye6 .png");
	cgChipWall[7][6] = LoadGraph("res/bg/wall/table meat eye7 .png");
	cgChipWall[7][7] = LoadGraph("res/bg/wall/table meat eye8 .png");
	cgChipWall[7][8] = -1;

	cgChipWall[8][0] = LoadGraph("res/bg/wall/table meat and knife 1 .png");
	cgChipWall[8][1] = LoadGraph("res/bg/wall/table meat and knife 2.png");
	cgChipWall[8][2] = LoadGraph("res/bg/wall/table meat and knife 3.png");
	cgChipWall[8][3] = -1;

	cgChipWall[9][0] = LoadGraph("res/bg/wall/danger1 diagonal connection.png");
	cgChipWall[9][1] = LoadGraph("res/bg/wall/danger2 diagonal connection.png");
	cgChipWall[9][2] = -1;


	cgChipWall[10][0] = LoadGraph("res/bg/wall/left1.png");
	cgChipWall[11][0] = LoadGraph("res/bg/wall/left2.png");
	cgChipWall[12][0] = LoadGraph("res/bg/wall/left3.png");
	cgChipWall[13][0] = LoadGraph("res/bg/wall/left4.png");
	cgChipWall[14][0] = LoadGraph("res/bg/wall/leftwall outside 1.png");
	cgChipWall[15][0] = LoadGraph("res/bg/wall/leftwall outside 2.png");
	cgChipWall[16][0] = LoadGraph("res/bg/wall/leftwall outside 3 connection.png");

	cgChipWall[17][0] = LoadGraph("res/bg/wall/up danger1.png");
	cgChipWall[17][1] = LoadGraph("res/bg/wall/up danger2.png");
	cgChipWall[17][2] = -1;

	cgChipWall[20][0] = LoadGraph("res/bg/wall/right1.png");
	cgChipWall[21][0] = LoadGraph("res/bg/wall/right2.png");
	cgChipWall[22][0] = LoadGraph("res/bg/wall/right3.png");
	cgChipWall[23][0] = LoadGraph("res/bg/wall/right4.png");
	cgChipWall[24][0] = LoadGraph("res/bg/wall/rightwall outside 1.png");
	cgChipWall[25][0] = LoadGraph("res/bg/wall/rightwall outside 2.png");
	cgChipWall[26][0] = LoadGraph("res/bg/wall/rightwall outside 3 connection.png");

	cgChipWall[27][0] = LoadGraph("res/bg/wall/rightwall outside 3 connection.png");
	cgChipWall[28][0] = LoadGraph("res/bg/wall/rightwall outside 3 connection.png");
	cgChipWall[29][0] = LoadGraph("res/bg/wall/rightwall outside 3 connection.png");


	cgChipWall[30][0] = LoadGraph("res/bg/wall/right diagonal connection.png");
	cgChipWall[31][0] = LoadGraph("res/bg/wall/left diagonal down 2.png");
	cgChipWall[32][0] = LoadGraph("res/bg/wall/left diagonal up.png");
	cgChipWall[33][0] = LoadGraph("res/bg/wall/left diagonal down 1.png");

	cgChipWall[40][0] = LoadGraph("res/bg/wall/right diagonal down 1.png");
	cgChipWall[41][0] = LoadGraph("res/bg/wall/up.png");
	cgChipWall[42][0] = LoadGraph("res/bg/wall/left diagonal connection.png");

	cgChipWall[43][0] = LoadGraph("res/bg/wall/beside obstacle wall left.png");
	cgChipWall[44][0] = LoadGraph("res/bg/wall/beside obstacle wall right.png");

	cgChipWall[45][0] = LoadGraph("res/bg/wall/wall1 diagonal connection.png");
	cgChipWall[46][0] = LoadGraph("res/bg/wall/wall2 diagonal connection.png");

	cgChipWall[47][0] = LoadGraph("res/bg/wall/obstacle wall down.png");
	cgChipWall[48][0] = LoadGraph("res/bg/wall/obstacle wall.png");
	cgChipWall[49][0] = LoadGraph("res/bg/wall/obstacle wall up.png");

	//
	//プレイヤー
	//

	cgPlayer[0][0] = LoadGraph("res/player/charaleft_a.png");
	cgPlayer[0][1] = LoadGraph("res/player/charaleft_b.png");
	cgPlayer[0][2] = LoadGraph("res/player/charaleft_c.png");

	cgPlayer[1][0] = LoadGraph("res/player/chararight_a.png");
	cgPlayer[1][1] = LoadGraph("res/player/chararight_b.png");
	cgPlayer[1][2] = LoadGraph("res/player/chararight_c.png");


	//
	// エフェクト
	// 

	//プレイヤー移動砂埃
	cgEffect[EFFECT_TYPE_MOVE][0] = LoadGraph("res/effect/moveffect/dust_a.png");
	cgEffect[EFFECT_TYPE_MOVE][1] = LoadGraph("res/effect/moveffect/dust_b.png");
	cgEffect[EFFECT_TYPE_MOVE][2] = LoadGraph("res/effect/moveffect/dust_c.png");
	cgEffect[EFFECT_TYPE_MOVE][3] = LoadGraph("res/effect/moveffect/dust_d.png");
	cgEffect[EFFECT_TYPE_MOVE][4] = LoadGraph("res/effect/moveffect/dust_e.png");
	cgEffect[EFFECT_TYPE_MOVE][5] = LoadGraph("res/effect/moveffect/dust_f.png");

	//箱を押す
	cgEffect[EFFECT_TYPE_IMPACT][0] = LoadGraph("res/effect/crush/impact_a.png");
	cgEffect[EFFECT_TYPE_IMPACT][1] = LoadGraph("res/effect/crush/impact_b.png");
	cgEffect[EFFECT_TYPE_IMPACT][2] = LoadGraph("res/effect/crush/impact_c.png");
	cgEffect[EFFECT_TYPE_IMPACT][3] = LoadGraph("res/effect/crush/impact_d.png");
	cgEffect[EFFECT_TYPE_IMPACT][4] = LoadGraph("res/effect/crush/impact_e.png");
	cgEffect[EFFECT_TYPE_IMPACT][5] = LoadGraph("res/effect/crush/impact_f.png");
	cgEffect[EFFECT_TYPE_IMPACT][6] = LoadGraph("res/effect/crush/impact_g.png");

	//黄色い矢印
	cgEffect[EFFECT_TYPE_ARROW_YELLOW][ARROW_DOWN] = LoadGraph("res/effect/arrow/yellow/yellow_down.png");
	cgEffect[EFFECT_TYPE_ARROW_YELLOW][ARROW_UP] = LoadGraph("res/effect/arrow/yellow/yellow_up.png");
	cgEffect[EFFECT_TYPE_ARROW_YELLOW][ARROW_LEFT] = LoadGraph("res/effect/arrow/yellow/yellow_left.png");
	cgEffect[EFFECT_TYPE_ARROW_YELLOW][ARROW_RIGHT] = LoadGraph("res/effect/arrow/yellow/yellow_right.png");

	//赤い矢印
	cgEffect[EFFECT_TYPE_ARROW_RED][ARROW_DOWN] = LoadGraph("res/effect/arrow/red/red_down.png");
	cgEffect[EFFECT_TYPE_ARROW_RED][ARROW_UP] = LoadGraph("res/effect/arrow/red/red_up.png");
	cgEffect[EFFECT_TYPE_ARROW_RED][ARROW_LEFT] = LoadGraph("res/effect/arrow/red/red_left.png");
	cgEffect[EFFECT_TYPE_ARROW_RED][ARROW_RIGHT] = LoadGraph("res/effect/arrow/red/red_right.png");


	//破裂
	//目
	cgEffect[EFFECT_TYPE_EXPLOSION_EYE_1][0] = LoadGraph("res/effect/explosion/me1.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_EYE_1][1] = LoadGraph("res/effect/explosion/me2.png");

	cgEffect[EFFECT_TYPE_EXPLOSION_EYE_2][0] = -1;
	cgEffect[EFFECT_TYPE_EXPLOSION_EYE_2][1] = -1;
	cgEffect[EFFECT_TYPE_EXPLOSION_EYE_2][2] = LoadGraph("res/effect/explosion/me3.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_EYE_2][3] = LoadGraph("res/effect/explosion/me4.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_EYE_2][4] = LoadGraph("res/effect/explosion/me5.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_EYE_2][5] = LoadGraph("res/effect/explosion/me6.png");

	//肉片
	cgEffect[EFFECT_TYPE_EXPLOSION_MEAT][0] = LoadGraph("res/effect/explosion/nikuhen1.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_MEAT][1] = LoadGraph("res/effect/explosion/nikuhen2.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_MEAT][2] = LoadGraph("res/effect/explosion/nikuhen3.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_MEAT][3] = LoadGraph("res/effect/explosion/nikuhen4.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_MEAT][4] = LoadGraph("res/effect/explosion/nikuhen5.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_MEAT][5] = LoadGraph("res/effect/explosion/nikuhen6.png");

	//血
	cgEffect[EFFECT_TYPE_EXPLOSION_BLOOD][0] = LoadGraph("res/effect/explosion/chi1.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_BLOOD][1] = LoadGraph("res/effect/explosion/chi2.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_BLOOD][2] = LoadGraph("res/effect/explosion/chi3.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_BLOOD][3] = LoadGraph("res/effect/explosion/chi4.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_BLOOD][4] = LoadGraph("res/effect/explosion/chi5.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_BLOOD][5] = LoadGraph("res/effect/explosion/chi6.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_BLOOD][6] = LoadGraph("res/effect/explosion/chi7.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_BLOOD][7] = LoadGraph("res/effect/explosion/chi8.9.png");
	cgEffect[EFFECT_TYPE_EXPLOSION_BLOOD][8] = cgEffect[EFFECT_TYPE_EXPLOSION_BLOOD][7];

	//はてなマーク
	cgEffect[EFFECT_TYPE_HATENA][0] = LoadGraph("res/effect/hatena/hatena.png");

	//
	// 箱
	// 

	cgBox[0] = LoadGraph("res/meetbox/meet_a.png");
	cgBox[1] = LoadGraph("res/meetbox/meet_b.png");
	cgBox[2] = LoadGraph("res/meetbox/meet_c.png");

	//
	// 敵
	// 

	cgEnemy[ENEMY_TYPE_TOMATO][0] = LoadGraph("res/enemy/tomato_a.png");
	cgEnemy[ENEMY_TYPE_TOMATO][1] = LoadGraph("res/enemy/tomato_b.png");
	cgEnemy[ENEMY_TYPE_TOMATO][2] = LoadGraph("res/enemy/tomato_c.png");
	cgEnemy[ENEMY_TYPE_TOMATO][3] = LoadGraph("res/enemy/tomato_d.png");

	cgEnemy[ENEMY_TYPE_NAMAKO][0] = LoadGraph("res/enemy/namako_a.png");
	cgEnemy[ENEMY_TYPE_NAMAKO][1] = LoadGraph("res/enemy/namako_b.png");
	cgEnemy[ENEMY_TYPE_NAMAKO][2] = LoadGraph("res/enemy/namako_c.png");

	//
	// ボス
	//

	// BossInit()で読み込みを行う

	//cgBoss[0] = LoadGraph("res/enemy/boss/boss1.png");
	//cgBoss[1] = LoadGraph("res/enemy/boss/boss2.png");
	//cgBoss[2] = LoadGraph("res/enemy/boss/boss3.png");
	//cgBoss[3] = LoadGraph("res/enemy/boss/boss4.png");
	//cgBoss[4] = LoadGraph("res/enemy/boss/boss5.png");
	//cgBoss[5] = LoadGraph("res/enemy/boss/boss6.png");
	//cgBoss[6] = LoadGraph("res/enemy/boss/boss7.png");
	//cgBoss[7] = LoadGraph("res/enemy/boss/boss8.png");
	//cgBoss[8] = LoadGraph("res/enemy/boss/boss9.png");
	//cgBoss[9] = LoadGraph("res/enemy/boss/boss10.png");
	//cgBoss[10] = LoadGraph("res/enemy/boss/boss11.png");
	//cgBoss[11] = LoadGraph("res/enemy/boss/boss12.png");
	//cgBoss[12] = LoadGraph("res/enemy/boss/boss13.png");
	//cgBoss[13] = LoadGraph("res/enemy/boss/boss14.png");
	//cgBoss[14] = LoadGraph("res/enemy/boss/boss15.png");
	//cgBoss[15] = LoadGraph("res/enemy/boss/boss16.png");

	//触手
	//左
	cgTentacle[0][0] = LoadGraph("res/enemy/boss/tentacle_left_0.png");
	cgTentacle[0][1] = LoadGraph("res/enemy/boss/tentacle_left_1.png");
	cgTentacle[0][2] = LoadGraph("res/enemy/boss/tentacle_left_2.png");
	cgTentacle[0][3] = LoadGraph("res/enemy/boss/tentacle_left_3.png");
	cgTentacle[0][4] = LoadGraph("res/enemy/boss/tentacle_left_4.png");
	cgTentacle[0][5] = LoadGraph("res/enemy/boss/tentacle_left_5.png");

	//右
	cgTentacle[1][0] = LoadGraph("res/enemy/boss/tentacle_right_0.png");
	cgTentacle[1][1] = LoadGraph("res/enemy/boss/tentacle_right_1.png");
	cgTentacle[1][2] = LoadGraph("res/enemy/boss/tentacle_right_2.png");
	cgTentacle[1][3] = LoadGraph("res/enemy/boss/tentacle_right_3.png");
	cgTentacle[1][4] = LoadGraph("res/enemy/boss/tentacle_right_4.png");
	cgTentacle[1][5] = LoadGraph("res/enemy/boss/tentacle_right_5.png");



	//
	//カウント
	//

	cgCount[0] = LoadGraph("res/stepcnt/0.png");
	cgCount[1] = LoadGraph("res/stepcnt/1.png");
	cgCount[2] = LoadGraph("res/stepcnt/2.png");
	cgCount[3] = LoadGraph("res/stepcnt/3.png");
	cgCount[4] = LoadGraph("res/stepcnt/4.png");
	cgCount[5] = LoadGraph("res/stepcnt/5.png");
	cgCount[6] = LoadGraph("res/stepcnt/6.png");
	cgCount[7] = LoadGraph("res/stepcnt/7.png");
	cgCount[8] = LoadGraph("res/stepcnt/8.png");
	cgCount[9] = LoadGraph("res/stepcnt/9.png");

	cgMeatCount = LoadGraph("res/stepcnt/meat box count.png");

	cgLevel[0] = LoadGraph("res/stagecnt/1.png");
	cgLevel[1] = LoadGraph("res/stagecnt/2.png");
	cgLevel[2] = LoadGraph("res/stagecnt/3.png");
	cgLevel[3] = LoadGraph("res/stagecnt/4.png");
	cgLevel[4] = LoadGraph("res/stagecnt/5.png");
	cgLevel[5] = LoadGraph("res/stagecnt/6.png");
	cgLevel[6] = LoadGraph("res/stagecnt/7.png");
	cgLevel[7] = LoadGraph("res/stagecnt/8.png");
	cgLevel[8] = LoadGraph("res/stagecnt/9.png");
	cgLevel[9] = LoadGraph("res/stagecnt/10.png");

	cgStageLevel = LoadGraph("res/stagecnt/stagelevel.png");
	cgStageClear = LoadGraph("res/stage clear.png");

	//
	// サウンド
	// 

	sound[0] = LoadSoundMem("res/sound/move.mp3");
	sound[1] = LoadSoundMem("res/sound/bite.mp3");
	sound[2] = LoadSoundMem("res/sound/impact.mp3");
	sound[3] = LoadSoundMem("res/sound/explosion.mp3");
	sound[4] = LoadSoundMem("res/sound/boss_attack.mp3");


	/*bgm[0] = LoadSoundMem("res/bgm/BGM1.mp3");
	bgm[3] = LoadSoundMem("res/bgm/BGM4.mp3");*/
	bgm[4] = LoadSoundMem("res/bgm/BGM5.mp3");
	bgm[5] = LoadSoundMem("res/bgm/BGM7.mp3");	//ボスっぽい
	bgm[6] = LoadSoundMem("res/bgm/BGM9.mp3");
	//bgm[8] = LoadSoundMem("res/bgm/title.mp3");




	//
	// 危険範囲画像
	//
	cgAOE[0] = LoadGraph("res/danger1.png");
	cgAOE[1] = LoadGraph("res/danger2.png");


	//cgCharaTalk[0] = LoadGraph("res/charatalk/talk_a.png");
	//cgCharaTalk[1] = LoadGraph("res/charatalk/talk_b.png");
	//cgCharaTalk[2] = LoadGraph("res/charatalk/talk_c.png");
	//cgCharaTalk[3] = LoadGraph("res/charatalk/talk_d.png");
	//cgCharaTalk[4] = LoadGraph("res/charatalk/talk_e.png");
	//cgCharaTalk[5] = LoadGraph("res/charatalk/talk_f.png");
	//cgCharaTalk[6] = LoadGraph("res/charatalk/talk_g.png");
	//cgCharaTalk[7] = LoadGraph("res/charatalk/talk_h.png");
	//cgCharaTalk[8] = LoadGraph("res/charatalk/talk_i.png");
	//cgCharaTalk[9] = LoadGraph("res/charatalk/talk_j.png");
	//cgCharaTalk[10] = LoadGraph("res/charatalk/talk_k.png");
	//cgCharaTalk[11] = LoadGraph("res/charatalk/talk_l.png");
	//cgCharaTalk[12] = LoadGraph("res/charatalk/talk_m.png");
	//cgCharaTalk[13] = LoadGraph("res/charatalk/talk_n.png");
	//cgCharaTalk[14] = LoadGraph("res/charatalk/talk_o.png");
	//cgCharaTalk[15] = LoadGraph("res/charatalk/talk_p.png");
	//cgCharaTalk[16] = LoadGraph("res/charatalk/talk_q.png");

};