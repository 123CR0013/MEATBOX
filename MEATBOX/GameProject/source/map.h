#pragma once



// �`�b�v�̃T�C�Y
#define	CHIP_W		(64)
#define	CHIP_H		(64)

// �}�b�v�̃T�C�Y
#define	MAP_W		(30)
#define	MAP_H		(17)

// �X�e�[�W��
#define	STAGE_MAX	(10)


#define BOSS_STAGE (9)

// �}�b�v�`�b�v�̔z�u�f�[�^
extern int map[];
// �~�[�g�{�b�N�X�̔z�u�f�[�^
extern int boxMap[];
// �G�̔z�u�f�[�^
extern int enemyMap[];

// �ǂݍ��݌��̃}�b�v�f�[�^
extern int stage[][MAP_W * MAP_H];

// �}�b�v�̏���������
// ���� stageNo : �X�e�[�W�ԍ�
// ���� *playerX : �v���C���[��X���W���i�[����ϐ��̃|�C���^
// ���� *playerY : �v���C���[��Y���W���i�[����ϐ��̃|�C���^
void MapInit(int stageNo, int* playerX, int* playerY);