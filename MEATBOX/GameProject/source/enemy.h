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
	// ���̔z��v�f���g�p���Ă��邩
	int use;
	// �G�̎��
	int type;

	// �G�̃}�b�v�`�b�v���W
	int x, y;

	//enemyRoute�\���̔z��̔ԍ�
	//enemyRoute[routeNum][moveCnt]
	int routeNum;
	int moveCnt;

	//Route���ǂ��i�ނ� 1.���� -1.�t��
	int moveOrder;

	// �A�j���[�V�����J�E���g
	int animCnt;
	// �A�j���[�V�������x
	int animSpeed;
};

//�G�̈ړ����W���
struct EnemyRoute {
	int x, y;
};

// enemy_tomato�����̎g��ꂽ�����J�E���g
// ���̃J�E���g��enemy[i].routeNum�Ɏ�������iEnemy��EnemyRoute�̑Ή��t���j
// �X�e�[�W�̃��g���C�ɂ��g��
extern int enemyTomatoCnt;

// �G�̏���������
void EnemyInit(Enemy[], EnemyRoute[][ROUTE_MAX]);
// �G�̈ړ�����
void EnemyMove(Enemy[], EnemyRoute[][ROUTE_MAX]);