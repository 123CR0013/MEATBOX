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

// マップチップの配置データ
extern int map[];
// ミートボックスの配置データ
extern int boxMap[];
// 敵の配置データ
extern int enemyMap[];

// 読み込み元のマップデータ
extern int stage[][MAP_W * MAP_H];

// マップの初期化処理
// 引数 stageNo : ステージ番号
// 引数 *playerX : プレイヤーのX座標を格納する変数のポインタ
// 引数 *playerY : プレイヤーのY座標を格納する変数のポインタ
void MapInit(int stageNo, int* playerX, int* playerY);