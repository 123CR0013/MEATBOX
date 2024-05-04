#pragma once
#include "gamemain.h"


#define EFFECT_TYPE_MAX	10
#define EFFECT_SHEETS_MAX 10

#define EFFECT_TYPE_MOVE 0
#define EFFECT_TYPE_IMPACT 1
#define EFFECT_TYPE_HATENA 2
#define EFFECT_TYPE_ARROW_YELLOW 3
#define EFFECT_TYPE_ARROW_RED 4

#define EFFECT_TYPE_EXPLOSION_EYE_1 (5)
#define EFFECT_TYPE_EXPLOSION_EYE_2 (6)

#define EFFECT_TYPE_EXPLOSION_MEAT (7)
#define EFFECT_TYPE_EXPLOSION_BLOOD (8)

#define ARROW_DOWN 0
#define ARROW_UP 1
#define ARROW_LEFT 2
#define ARROW_RIGHT 3


// �摜�f�[�^
int cgChipBase[][10];		// ���`�b�v�摜�i�z��j
int cgChipWall[][10];		// �ǃ`�b�v�摜�i�z��j
int cgPlayer[][3];			// �v���C���[
int cgBox[];		// ��
int cgEffect[][EFFECT_SHEETS_MAX];

int cgEnemy[][4];		//�G
int cgBoss[];
int cgTentacle[][6]; //�{�X�̐G��

int cgCount[];
int cgLevel[];
extern int cgMeatCount;
extern int cgStageLevel;
extern int cgStageClear;


//�����f�[�^
int sound[];
int bgm[];

int cgAOE[];

int cgCharaTalk[];

void ResourceInit();