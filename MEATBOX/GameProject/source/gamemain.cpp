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
// �O���[�o���ϐ��錾
//

int gScene = SCENE_TITLE;

// �Q�[�����
int gKey;			// �L�[���͂̏��
int gTrg;			// �g���K���͂̏��
int gStageNo;		// �X�e�[�W�ԍ�
int gViewClearCnt;	// �X�e�[�W�N���A�\���J�E���^

int boxAnimCnt;

int tentacleMoveCnt;


int bgmHandle;

//�����o�����߂̃t���O
//�ړ������^�C�~���O��1, �����Z�b�g������0��
int moveCnt; 

Player player;
Effect effect[EFFECT_MAX];

Enemy enemy[ENEMY_MAX];

//���̃��[�g�����Ԃɒʂ�
//�ړ���ɏ�Q������������܂�Ԃ��āA�t���ɍŏ��̒n�_�܂ōs��
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
	//stage 6�i�ǉ��j
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
//����������
//

// �A�v���̏�����
// �N������1�񂾂����s�����
void AppInit() {
	ResourceInit();

	SceneInit();
	bgmHandle = bgm[4];
	PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);
}

void GameInit() {
	// �X�e�[�W�f�[�^������
	gStageNo = 0;
	StageInit(gStageNo);

	enemyTomatoCnt = 0;
	EnemyInit(enemy, enemyRoute);
}

// �X�e�[�W�f�[�^������
void StageInit(int stageNo) {
	int x, y;
	MapInit(stageNo, &x, &y); //x, y�Ƀv���C���[�̊J�n�n�_�̍��W������
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

	//�{�X�X�e�[�W�̏ꍇ
	if (gStageNo == BOSS_STAGE) {
		for (int i = 0; i < 4; i++) {
			AddBox(12, 9, 17, 10, player.x, player.y);
		}		
		TentacleInit(tentacle);
		tentacleMoveCnt = 0;
	}
}


// �A�v���̉��
// �I������1�񂾂����s�����
void AppRelease() {
}





//
// �t���[�������B1�t���[����1�񂸂��s�����
//

// �t���[�������F����
void FrameInput() {
	// �L�[�̓��́A�g���K���͂𓾂�
	int keyold = gKey;
	gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// �L�[���͂��擾
	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
	gTrg = (gKey ^ keyold) & gKey;
}


// �w�肵���͈͓��Ƀ~�[�g�{�b�N�X�������_���ɒǉ����鏈��
// ����E�E�����w�肵�A���̋�`�̒����o���͈͂Ƃ���
// �v���C���[�̍��W�ɂ̓~�[�g�{�b�N�X���o�������Ȃ�
void AddBox(int left, int top, int right, int bottom, int playerX, int playerY) {

	int rx, ry;
	while (1) {
		// �����_���ɍ��W�����߂�
		rx = (rand() % (right - left + 1)) + left;
		ry = (rand() % (bottom - top + 1)) + top;

		// �����_���Ɍ��肵�����W�Ɋ��Ƀ~�[�g�{�b�N�X���Ȃ��A���A�v���C���[�̍��W�łȂ��ꍇ�Ƀ��[�v�𔲂���
		if (box[ry * MAP_W + rx] != 1) {
			if (playerX != rx || playerY != ry) {
				break;
			}
		}
	}
	// box[] �Ƀ~�[�g�{�b�N�X��ǉ�
	box[ry * MAP_W + rx] = 1;

	// �G�t�F�N�g���Z�b�g
	SetEffect(effect, rx, ry, EFFECT_TYPE_IMPACT);
}

int alphaFrag;

void SetArrowEffect() {
	if (moveCnt == 1) {	
		alphaFrag = 0;

		//��x���ݕ\������Ă����������
		for (int i = 0; i < EFFECT_MAX; i++) {
			if (effect[i].use == 1) {
				if (effect[i].type == EFFECT_TYPE_ARROW_YELLOW || effect[i].type == EFFECT_TYPE_ARROW_RED) {
					effect[i].use = 0;
				}
			}
		}

		//���̈ړ���̍��W���擾���Ė����Z�b�g����
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (enemy[i].use == 1 && enemy[i].type == ENEMY_TYPE_TOMATO) {
				//�ڑ���̏������œ����
				int x, y, n, order;
				n = enemy[i].moveCnt + enemy[i].moveOrder;
				x = enemyRoute[enemy[i].routeNum][n].x;
				y = enemyRoute[enemy[i].routeNum][n].y;
				order = enemy[i].moveOrder;

				//enemyRoute�̏I�[�ɂ�����A�܂�Ԃ���̍��W���擾����
				if (x == -1 || n == -1) { 				
					order *= -1;
					n = enemy[i].moveCnt + order;
					x = enemyRoute[enemy[i].routeNum][n].x;
					y = enemyRoute[enemy[i].routeNum][n].y;			
				
				}

				// �G���ړ��ł��Ȃ��ꍇ�͖��𔼓����ɂ���
				if (map[y * MAP_W + x] == 1 || box[y * MAP_W + x] == 1) { 
					alphaFrag = 1;
					//break; 
				
				}

				//�G�������܂�2�^�[���������物�F�������Z�b�g����
				if (player.moveCnt == 0) {
					//���F
					if (enemy[i].x > x) {
						//��
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_YELLOW, ARROW_LEFT);
					}
					else if (enemy[i].x < x) {
						//�E
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_YELLOW, ARROW_RIGHT);
					}
					else if (enemy[i].y > y) {
						//��
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_YELLOW, ARROW_UP);
					}
					else if (enemy[i].y < y) {
						//��
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_YELLOW, ARROW_DOWN);
					}
				}
				//�G�����̃^�[���Ɉړ�����Ȃ�Ԃ������Z�b�g����
				else if (player.moveCnt == 1) {
					//��
					if (enemy[i].x > x) {
						//��
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_RED, ARROW_LEFT);
					}
					else if (enemy[i].x < x) {
						//�E
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_RED, ARROW_RIGHT);
					}
					else if (enemy[i].y > y) {
						//��
						SetEffect(effect, x, y, EFFECT_TYPE_ARROW_RED, ARROW_UP);
					}
					else if (enemy[i].y < y) {
						//��
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
	// �ړ��O�̏ꏊ������Ă���
	int old_x = player.x;
	int old_y = player.y;

	// �ړ������p�ϐ�
	int move_x = 0;
	int move_y = 0;
	
	//�ړ��L�[
	if (gTrg & (PAD_INPUT_LEFT + PAD_INPUT_RIGHT + PAD_INPUT_UP + PAD_INPUT_DOWN)) { //���ׂĉ��Z������Ɂi2�i���ŕ\���������ɌJ��グ���Ȃ��jgTrg�Ɣr���I�_���a
		PlaySoundMem(sound[0], DX_PLAYTYPE_BACK);

		if (gStageNo != BOSS_STAGE) {
			player.stepCnt--;
		}
		else {
			tentacleMoveCnt++;
		}		
	}
			
	// �L�[���͂𔻒肵�āA��l�����ړ�������
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
	if (move_x == 0) {	// �΂߈ړ����Ȃ��悤�ɁA���ړ���D��
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

	// �ړ������悪�ǂ��H
	if (map[player.y * MAP_W + player.x] >= 50 || map[player.y * MAP_W + player.x] == -1)
	{
		// �ړ������悪�ǂ������̂ŁA�ړ��O�̏ꏊ�ɖ߂�
		player.x = old_x;
		player.y = old_y;
		IsMove = 0;
	}

	//�v���C���[�ƓG���Ԃ�������Q�[���I�[�o�[
	if (enemyMap[player.y * MAP_W + player.x] != 0) {
		
		gScene = SCENE_GAMEOVER;
	}

	// �ړ�������ɔ��͂��邩�H
	if (box[player.y * MAP_W + player.x] == 1)
	{
		// �ړ�������ɔ����������B
		// �����邩�ǂ������ׂ���
		int push_ok = 1;

		// ����ɓ��������̂��̐�̍��W�����߂�i�ړ������p�ϐ��𑫂��j
		int next_x = player.x + move_x;
		int next_y = player.y + move_y;

		// ���̐�ɁA�ǂ����邩�𒲂ׂ�
		if (map[next_y * MAP_W + next_x] >= 50 || map[next_y * MAP_W + next_x] == -1)
		{
			// �ǂ�����̂ŉ����Ȃ�
			push_ok = 0;
			IsMove = 0;
		}

		// ���̐�ɁA�������邩�𒲂ׂ�
		if (box[next_y * MAP_W + next_x] == 1)
		{
			// ��������̂ŉ����Ȃ�
			push_ok = 0;
			IsMove = 0;
		}

		int crush_ok = 0;

		//�����Ԃ�
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

		// ���ׂ����ʁA������H
		if (push_ok == 1)
		{
			// ������B���̈ʒu���ړ�����
			// �܂��A�v���C���[����������������A
			box[player.y * MAP_W + player.x] = 0;

			// �ړ���ɔ�����������
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
			// �����Ȃ��̂ŁA�v���C���[�̈ʒu���ړ��O�̏ꏊ�ɖ߂�
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

 
// �t���[�������F�v�Z
void FrameProcess() {
	if (player.stepCnt == 0) {
		gScene = SCENE_GAMEOVER;
	}
	boxAnimCnt++;
	boss.animCnt++;
	
	
	// �G�����ׂē|������
	int all_get = 1;	
	
	//BOSS�X�e�[�W�ȊO�Ȃ�
	if(gStageNo != BOSS_STAGE){
		// �S�����ׂ�1�̂܂܂Ȃ�A�S���|����
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (enemy[i].use == 1) {
				enemy[i].animCnt++;
				all_get = 0;
			}
		}
	}
	else if(gStageNo == BOSS_STAGE){
		// �S�����ׂ�1�̂܂܂Ȃ�A�S���|����
		for (int i = 0; i < TENTACLE_MAX; i++) {
			if (tentacle[i].use == 1) {
				tentacle[i].animCnt++;
				all_get = 0;
			}
		}
	}

		


	player.animCnt++;
	EffectProcess(effect);

	// �G���c���Ă�����A�Q�[���̏���������
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
						// box[] ����A�`�b�v�ԍ������o��
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
		}else if (player.moveCnt == 2) { //�v���C���[��2���������тɁA�G��1������
			EnemyMove(enemy, enemyRoute);
			player.moveCnt = 0;
		}

		
		// �X�e�[�W�f�[�^���Z�b�g�i��蒼���j
		if (gTrg & PAD_INPUT_1) {	// [z]
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (enemy[i].type == ENEMY_TYPE_TOMATO) {
					enemyTomatoCnt--;
				}
			}
			StageInit(gStageNo);
			EnemyInit(enemy, enemyRoute);
		}
		








		// �J���p�B���̃X�e�[�W��
		if (gTrg & PAD_INPUT_7) { // [q] �L�[
			if (gStageNo + 1 < STAGE_MAX) {
				gStageNo++;
				/*if(gStageNo == 7) {
					gStageNo = BOSS_STAGE;
				}*/
				StageInit(gStageNo);
				EnemyInit(enemy, enemyRoute);
			}
		}

		//�J���p �{�X�X�e�[�W��
		if (gTrg & PAD_INPUT_8) { // [w] �L�[
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
		// ���ׂĂ̓G��|����
		gScene = SCENE_GAME;
		if (gViewClearCnt == 0) {
			// �X�e�[�W�N���A�\����
			gViewClearCnt = 120;		// �\���t���[����

			if (gStageNo == BOSS_STAGE) {
				PlaySoundMem(sound[3], DX_PLAYTYPE_BACK);
				gViewClearCnt = 150;		// �\���t���[����

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
			// �\���t���[�������炷
			gViewClearCnt--;

			if (gViewClearCnt == 0) {
				if (gStageNo == BOSS_STAGE) {
					gScene = SCENE_GAMECLEAR;

					StopSoundMem(bgmHandle);
					bgmHandle = bgm[6];
					PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);
				}
				else {

					// ���炵�������玟�̃X�e�[�W��
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
	// �摜�\�� ////////////////////////////////////////

	if(gStageNo == BOSS_STAGE) {
		//�{�X
		

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

	// �}�b�v�`�b�v�� for ���[�v�łЂƂЂƂ`�悷��
	int x, y;
	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			// map[] ����A�`�b�v�ԍ������o��
			int chip_no = map[y * MAP_W + x];

			if (chip_no != -1) {
				// �`�b�v�ԍ��ɍ��킹���摜���A�}�X�ڂɉ����ĕ`�悷��
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

	// ����for���[�v�ŕ`�悷��
	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			// box[] ����A�`�b�v�ԍ������o��
			int chip_no = box[y * MAP_W + x];
			if (chip_no != 0)
			{
				int animTbl[] = { 0, 1, 2, 2, 2, 1, 0};
				DrawGraph(x * CHIP_W, y * CHIP_H - CHIP_H / 10, cgBox[animTbl[(boxAnimCnt / 12) % 7]], TRUE);
			}
		}
	}


	//�G�̕`��
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


	
	

	

	// �v���C���[
	int animTbl[] = { 0, 1, 2, 2, 2 ,1 };
	DrawGraph(player.x* CHIP_W, player.y* CHIP_H - CHIP_H / 4, cgPlayer[player.arrow][animTbl[(player.animCnt / player.animSpeed) % 6]], TRUE);

	if(gStageNo == BOSS_STAGE) {
		//�G��
		for(int i = 0; i < TENTACLE_MAX; i++) {
			if(tentacle[i].use == 1) {


				if(tentacle[i].direction == 1) { //��
					if(tentacle[i].isRemain == 0) {
						//�ҋ@
						DrawGraph((tentacle[i].x - 1) * CHIP_W, tentacle[i].y * CHIP_H - 96, cgTentacle[0][(tentacle[i].animCnt / tentacle[i].animSpeed) % 2], TRUE);
					}
					else {
						//�U��
						DrawGraph((tentacle[i].x + 1) * CHIP_W - CHIP_W / 2, (tentacle[i].row + TENTACLE_ATTACK_ROW)* CHIP_H, cgTentacle[0][((tentacle[i].animCnt / tentacle[i].animSpeed) % 2) + 4], TRUE);
					}
				}




				else { //�E
					if(tentacle[i].isRemain == 0) {
						//�ҋ@
						DrawGraph((tentacle[i].x + 1) * CHIP_W - 450, tentacle[i].y * CHIP_H - 96, cgTentacle[1][(tentacle[i].animCnt / tentacle[i].animSpeed) % 2], TRUE);
					}
					else {
						//�U��
						DrawGraph((tentacle[i].x - 1) * CHIP_W - 450 + CHIP_W / 2, (tentacle[i].row + TENTACLE_ATTACK_ROW) * CHIP_H, cgTentacle[1][((tentacle[i].animCnt / tentacle[i].animSpeed) % 3) + 3], TRUE);
					}
				}
			}
		}
	}

	// �G�t�F�N�g�̕`��
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].use == 1) {
			// ���G�t�F�N�g�̏ꍇ
			if (effect[i].type == EFFECT_TYPE_ARROW_RED || effect[i].type == EFFECT_TYPE_ARROW_YELLOW) {
				// �������ŕ`�悷��ꍇ
				if (alphaFrag == 1) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 140);
				}
				DrawGraph(effect[i].x * CHIP_W, effect[i].y * CHIP_H, cgEffect[effect[i].type][effect[i].arrowDirection], TRUE);
				
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			}
			// ���̑��̃G�t�F�N�g
			else {
				DrawGraph(effect[i].x * CHIP_W + effect[i].cx, effect[i].y * CHIP_H + effect[i].cy, cgEffect[effect[i].type][(effect[i].animationCnt / effect[i].speed) % effect[i].sheets], TRUE);
			}
		}
	}

	//�{�X�X�e�[�W
	if (gStageNo == BOSS_STAGE) {
		//AOE
		for (int i = 0; i < 8; i++) {
			if (aoe[i].use == 1) {
				DrawGraph(aoe[i].x * CHIP_W, aoe[i].y * CHIP_H, cgAOE[(aoe[i].animCnt / aoe[i].animSpeed) % aoe[i].sheets], TRUE);
				aoe[i].animCnt++;
			}
		}
	}


	//�����J�E���^�[
	DrawGraph(0, 0, cgMeatCount, TRUE);
	if (gStageNo != BOSS_STAGE) {
		//������3���̏ꍇ
		if (player.stepCnt >= 100) {
			DrawGraph(180, 180, cgCount[player.stepCnt / 100], TRUE);
			DrawGraph(220, 180, cgCount[(player.stepCnt / 10) % 10], TRUE);
			DrawGraph(260, 180, cgCount[player.stepCnt % 10], TRUE);
		}
		//������2���̏ꍇ
		else if (player.stepCnt > 9) {
			DrawGraph(189, 180, cgCount[player.stepCnt / 10], TRUE);
			DrawGraph(249, 180, cgCount[player.stepCnt % 10], TRUE);
		}
		//������1���̏ꍇ
		else if (player.stepCnt <= 9) {
			DrawGraph(220, 180, cgCount[player.stepCnt % 10], TRUE);
		}
	}
	else {
		//��

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


	//�X�e�[�W�ԍ��\��
	DrawGraph(0, 0, cgStageLevel, TRUE);

	if(gStageNo <= 10) {
		DrawGraph(1706, 914, cgLevel[gStageNo % 10], TRUE);
	}

	int  h = 1;
	int line = 10;
	DrawString(SCREEN_W - 250, h *(16 + line), "[���] �L�[�ňړ�", GetColor(255, 255, 255));			 h++;
	DrawString(SCREEN_W - 250, h *(16 + line), "[Z] �L�[�Ń��g���C", GetColor(255, 255, 255));			 h++;
	DrawString(SCREEN_W - 250, h *(16 + line), "[esc] �L�[�ŃQ�[���I��", GetColor(255, 255, 255));	 h++;



	// �N���A�\��
	if(gViewClearCnt != 0) {
		if (gStageNo != BOSS_STAGE) {
			if (gViewClearCnt <= 90) {
				DrawGraph(0, 0, cgStageClear, TRUE);
			}
		}
	}


#ifdef _DEBUG

	////�ȉ��J���p
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "gScene %d", gScene);

	////�G�t�F�N�g
	//for (int i = 0; i < EFFECT_MAX; i++) {
	//	DrawFormatString(0, 100 + 16 * i, GetColor(255, 255, 255), "use %d, x %d, y %d, Cnt %d", effect[i].use, effect[i].x, effect[i].y, effect[i].Cnt);
	//}

	// �v���C���[
	//DrawFormatString(500, 100 - 16, GetColor(255, 255, 255), "x %d, y %d, moveCnt %d", player.x, player.y, player.moveCnt);

	//�G
	//for (int i = 0; i < ENEMY_MAX; i++) {
	//	DrawFormatString(500, 100 + 16 * i, GetColor(255, 255, 255), "enemy_no: %d, use %d, x %d, y %d, moveCnt %d, moveOrder %d Cnt %d type %d animCnt %d", i, enemy[i].use, enemy[i].x, enemy[i].y, enemy[i].moveCnt, enemy[i].moveOrder, enemy[i].routeNum, enemy[i].type, enemy[i].animCnt);
	//}

	//�G��
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


// �t���[�������F�`��
void FrameDraw() {

	ClearDrawScreen();						// ��ʂ�����������

	SceneManage(gScene);
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "gScene %d", gScene);

	

#ifdef _DEBUG
	draw_fps(0, 0);
#endif

	ScreenFlip();							// ����ʂ̓��e��\��ʂɔ��f������
}

int scene_key = 0;
int scene_trg = 0;

void GameMain()
{
	//�L�[���������܂Ŗ������[�v

	AppInit();	// ������

	// 1�t���[�����[�v��g�� ----------------------------------------------------------
	while (ProcessMessage() == 0)		// �v���O�������I������܂Ń��[�v
	{
		//int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		// �L�[�̓��́A�g���K���͂𓾂�
		int scene_keyold = scene_key;
		scene_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// �L�[���͂��擾
		// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
		int scene_trg = (scene_key ^ scene_keyold) & scene_key;

		switch (gScene)
		{
		case SCENE_TITLE: //�^�C�g�����
			if ((scene_trg & PAD_INPUT_10) || (scene_trg & PAD_INPUT_1)) { //�X�y�[�X�� z�L�[
				gScene = SCENE_CHARATALK;				
				talkNum = 0;
			}
			break;
		case SCENE_GAME: //�Q�[�����
			FrameInput();	// ����
			FrameProcess();	// �v�Z
			break;
		case SCENE_GAMEOVER: //�Q�[���I�[�o�[���
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
		case SCENE_GAMECLEAR: //�Q�[���N���A���
			if ((scene_trg & PAD_INPUT_10) || (scene_trg & PAD_INPUT_1)) {
				gScene = SCENE_TITLE;

				StopSoundMem(bgmHandle);
				bgmHandle = bgm[4];
				PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);
			}
			break;

		case SCENE_CHARATALK: //�L������b

			//if((scene_trg & PAD_INPUT_10) || (scene_trg & PAD_INPUT_2)) { //�X�y�[�X�� x�L�[�iB�{�^���j
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
		
		
		FrameDraw();	// �`��


		// �t���[�����[�g�̌Œ�
		fps_wait();




		if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)	// ESCAPE�L�[��������Ă��邩�𒲂ׂ�
			break;			// ������Ă����烁�C�����[�v�𔲂���
	}

	AppRelease();	// ���
}
