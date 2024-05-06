#pragma once

#define TENTACLE_MAX 4
#define TENTACLE_ATTACK_ROW 8

// �{�X�̍\����
struct Boss {
	// �{�X�̃}�b�v�`�b�v���W
	int x, y;
	// �A�j���[�V�����J�E���g
	int animCnt;
	// �A�j���[�V�������x
	int animSpeed;
};

// �G��̍\����
struct Tentacle {
	// ���̗v�f���g�p���Ă��邩
	int use;
	// �G��̍����̍��W
	int x, y;
	// �U�������i�G��̌����j
	int direction;
	// �U���͈�
	int range;
	// �U�������
	int row;

	// �U���ҋ@���ǂ����i���ɍU������G���1�A����ȊO��0�j
	int isReady;
	// �X�e�[�W��ɗ��܂��Ă��邩�i�U����Ԃ��ǂ����j�i0�F���܂��Ă��Ȃ��A1�F���܂��Ă���j
	int isRemain;

	// �A�j���[�V�����J�E���g
	int animCnt;
	// �A�j���[�V�������x
	int animSpeed;
};

// AOE�i�U���\���͈́j�̍\����
struct AOE {
	// ���̗v�f���g�p���Ă��邩
	int use;
	// �}�b�v�`�b�v���W
	int x, y;

	// �A�j���[�V�����J�E���g
	int animCnt;
	// �A�j���[�V�������x
	int animSpeed;
	// �摜�̖���
	int sheets;
};

// �{�X�̏�����
void BossInit();
// �G��\���̂̏�����
void TentacleInit(Tentacle[]);
// AOE�\���̂̏�����
void AOEInit(AOE[]);
// �G����U���ҋ@��Ԃɂ���
void SetTentacleReady(Tentacle[], AOE[]);
// AOE��ݒ肷��
//�{�X�̍U���͈͂𐔃^�[���O�ɕ\������
void SetBossAOE(Tentacle[], AOE[]);
// �{�X�̍U������
void BossAttack(Tentacle[]);
// �G������������i�v���C���[����G��ւ̍U���j
void DeleteTentacle(Tentacle[]);