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

extern int map[];
extern int box[];
extern int enemyMap[];

extern int stage[][MAP_W * MAP_H];

void MapInit(int, int*, int*);