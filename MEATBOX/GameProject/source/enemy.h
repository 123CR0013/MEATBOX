#pragma once


#define ENEMY_MAX 20 //Enemy�\���̔z��̍ő�v�f���i1�X�e�[�W�̍ő吔�j

#define ENEMY_TOMATO_MAX 100
#define ROUTE_MAX 10
#define ENEMY_TYPE_MAX 2

#define ENEMY_TYPE_TOMATO 0
#define ENEMY_TYPE_NAMAKO 1
#define ENEMY_TYPE_MAX 2

// �G���
struct Enemy
{
	int x, y;		// ���W�i�`�b�v�P�ʁj

	//enemyRoute�\���̔z��̔ԍ�
	//enemyRoute[routeNum][moveCnt]
	int routeNum;	//
	int moveCnt;	//

	int moveOrder;	//Route���ǂ��i�ނ� 1.���� -1.�t��
	int use;		//���̔z��v�f���g�p���Ă��邩
	int type;		//�G�̎��

	int animCnt;
	int animSpeed;
};

//�G�̈ړ����W���
struct EnemyRoute {
	int x, y;
};

//enemy_tomato�����̎g��ꂽ�����J�E���g
//���̃J�E���g��enemy[i].routeNum�Ɏ�������
extern int enemyTomatoCnt;

void EnemyInit(Enemy[], EnemyRoute[][ROUTE_MAX]);
void EnemyMove(Enemy[], EnemyRoute[][ROUTE_MAX]);