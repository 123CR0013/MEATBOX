#include "enemy.h"
#include "map.h"

int enemyTomatoCnt;

// �G�̏���������
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
			// enemyMap[] ����A�`�b�v�ԍ������o��
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

// �G�̈ړ�����
void EnemyMove(Enemy enemy[], EnemyRoute enemyRoute[][ROUTE_MAX]) {
	for (int i = 0; i < ENEMY_MAX; i++) {
		// �G���g���Ă���A���A���񂷂�G�̏ꍇ�Ɉړ��������s��
		if (enemy[i].use == 1 && enemy[i].type == ENEMY_TYPE_TOMATO) {

			// �ړ����������A���A�Ō�̗v�f�ɓ��B���Ă���ꍇ�A�t���ɂ���
			if (enemy[i].moveOrder == 1 && ROUTE_MAX - 1 <= enemy[i].moveCnt) {
				enemy[i].moveOrder = -1;
			}
			// �ړ������t���A���A�ŏ��̗v�f�ɓ��B���Ă���ꍇ�A�����ɂ���
			else if (enemy[i].moveOrder == -1 && enemy[i].moveCnt <= 0) {
				enemy[i].moveOrder = 1;
			}

			// �ړ��O�̍��W��ێ�����
			int old_x, old_y, old_n;
			old_n = enemy[i].moveCnt;
			old_x = enemyRoute[enemy[i].routeNum][old_n].x;
			old_y = enemyRoute[enemy[i].routeNum][old_n].y;

			// �ڑ���̏������œ����
			int x, y, n;
			n = enemy[i].moveCnt + enemy[i].moveOrder;
			x = enemyRoute[enemy[i].routeNum][n].x;
			y = enemyRoute[enemy[i].routeNum][n].y;

			// EnemyRoute�̍Ō�̗v�f�̏ꍇ�́A���[�g��܂�Ԃ�
			if (x == -1) {

				enemy[i].moveOrder *= -1;

				n = enemy[i].moveCnt + enemy[i].moveOrder;
				x = enemyRoute[enemy[i].routeNum][n].x;
				y = enemyRoute[enemy[i].routeNum][n].y;
			}

			// �ړ�������ɕǂ����Ȃ����
			if (map[y * MAP_W + x] != 1 && boxMap[y * MAP_W + x] != 1)
			{
				// �ړ��\�Ȃ牼�œ��ꂽ���̂𔽉f����
				enemy[i].moveCnt = n;
				enemy[i].x = x;
				enemy[i].y = y;

				enemyMap[old_y * MAP_W + old_x] = 0;
				enemyMap[y * MAP_W + x] = 1;
			}
			// ����ꍇ�͐܂�Ԃ�
			else {
				enemy[i].moveOrder *= -1;
			}
		}
	}
}