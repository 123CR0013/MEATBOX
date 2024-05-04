#include "enemy.h"
#include "map.h"

int enemyTomatoCnt;

void EnemyInit(Enemy enemy[], EnemyRoute enemyRoute[][ROUTE_MAX]) {
	for (int j = 0; j < ENEMY_MAX; j++) {
		enemy[j].use = 0;
		enemy[j].type = -1;
		enemy[j].animCnt = 0;
	}

	int i = 0;
	int x, y;
	for (y = 0; y < MAP_H; y++) {
		for (x = 0; x < MAP_W; x++) {
			// enemyMap[] から、チップ番号を取り出す
			int chip_no = enemyMap[y * MAP_W + x];
			if (chip_no != 0)
			{
				if (chip_no == ENEMY_TYPE_TOMATO + 3) { //tomato
					enemy[i].routeNum = enemyTomatoCnt;
					enemy[i].x = enemyRoute[enemy[i].routeNum][0].x;
					enemy[i].y = enemyRoute[enemy[i].routeNum][0].y;

					enemy[i].moveCnt = 0;
					enemy[i].moveOrder = 1;
					enemy[i].use = 1;
					enemy[i].type = chip_no - 3;

					enemy[i].animSpeed = 16;

					i++;
					enemyTomatoCnt++;
				}
				else { //namako
					enemy[i].x = x;
					enemy[i].y = y;
					enemy[i].use = 1;
					enemy[i].type = chip_no - 3;

					enemy[i].animSpeed = 16;
					i++;
				}

			}
		}
	}
}

void EnemyMove(Enemy enemy[], EnemyRoute enemyRoute[][ROUTE_MAX]) {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i].use == 1 && enemy[i].type == ENEMY_TYPE_TOMATO) {
			if (enemy[i].moveOrder == 1 && ROUTE_MAX - 1 <= enemy[i].moveCnt) {
				enemy[i].moveOrder = -1;
			}
			else if (enemy[i].moveOrder == -1 && enemy[i].moveCnt <= 0) {
				enemy[i].moveOrder = 1;
			}


			int old_x, old_y, old_n;
			old_n = enemy[i].moveCnt;
			old_x = enemyRoute[enemy[i].routeNum][old_n].x;
			old_y = enemyRoute[enemy[i].routeNum][old_n].y;

			//移送先の情報を仮で入れる
			int x, y, n;
			n = enemy[i].moveCnt + enemy[i].moveOrder;
			x = enemyRoute[enemy[i].routeNum][n].x;
			y = enemyRoute[enemy[i].routeNum][n].y;

			if (x == -1) {

				enemy[i].moveOrder *= -1;

				n = enemy[i].moveCnt + enemy[i].moveOrder;
				x = enemyRoute[enemy[i].routeNum][n].x;
				y = enemyRoute[enemy[i].routeNum][n].y;
			}

			// 移動した先に壁か箱なければ
			if (map[y * MAP_W + x] != 1 && box[y * MAP_W + x] != 1)
			{
				//移送可能なら仮で入れたものを反映する
				enemy[i].moveCnt = n;
				enemy[i].x = x;
				enemy[i].y = y;

				enemyMap[old_y * MAP_W + old_x] = 0;
				enemyMap[y * MAP_W + x] = 1;

			}

			//ある場合は折り返す
			else {
				enemy[i].moveOrder *= -1;
			}


		}
	}

}