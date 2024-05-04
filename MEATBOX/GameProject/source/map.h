#pragma once



// チップのサイズ
#define	CHIP_W		(64)
#define	CHIP_H		(64)

// マップのサイズ
#define	MAP_W		(30)
#define	MAP_H		(17)

// ステージ数
#define	STAGE_MAX	(10)


#define BOSS_STAGE (9)

extern int map[];
extern int box[];
extern int enemyMap[];

extern int stage[][MAP_W * MAP_H];

void MapInit(int, int*, int*);