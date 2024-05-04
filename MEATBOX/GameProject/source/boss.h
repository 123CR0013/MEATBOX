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
	int x, y;		//�G��̍����̍��W
	int direction;	//�U�������i�G��̌����j
	int range;		//�U���͈�
	int row; //�U�������

	int isReady;	//�U���ҋ@���ǂ����i���ɍU������G�肪1�j

	int isRemain;	//�X�e�[�W��ɗ��܂��Ă��邩

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