#pragma once


#define ENEMY_MAX 20 //Enemy構造体配列の最大要素数（1ステージの最大数）

#define ENEMY_TOMATO_MAX 100
#define ROUTE_MAX 10
#define ENEMY_TYPE_MAX 2

#define ENEMY_TYPE_TOMATO 0
#define ENEMY_TYPE_NAMAKO 1
#define ENEMY_TYPE_MAX 2

// 敵情報
struct Enemy
{
	int x, y;		// 座標（チップ単位）

	//enemyRoute構造体配列の番号
	//enemyRoute[routeNum][moveCnt]
	int routeNum;	//
	int moveCnt;	//

	int moveOrder;	//Routeをどう進むか 1.正順 -1.逆順
	int use;		//この配列要素を使用しているか
	int type;		//敵の種類

	int animCnt;
	int animSpeed;
};

//敵の移動座標情報
struct EnemyRoute {
	int x, y;
};

//enemy_tomatoが何体使われたかをカウント
//このカウントをenemy[i].routeNumに持たせる
extern int enemyTomatoCnt;

void EnemyInit(Enemy[], EnemyRoute[][ROUTE_MAX]);
void EnemyMove(Enemy[], EnemyRoute[][ROUTE_MAX]);