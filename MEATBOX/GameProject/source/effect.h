#pragma once
#define EFFECT_MAX	10 //EFFECT�\���̔z��̍ő�v�f��

// �G�t�F�N�g�\����
struct Effect
{
	// ���̔z��v�f���g�p���Ă��邩
	int use;
	// �G�t�F�N�g�̎��
	int type;

	// �G�t�F�N�g���Đ�����}�b�v�`�b�v���W
	int x, y;
	// �Đ��ʒu�����炷���߂̒l�i�s�N�Z���j
	int cx, cy;

	// �A�j���[�V�����J�E���g
	int animationCnt;
	// �A�j���[�V�����̍Đ����x
	int speed;
	// �A�j���[�V�����摜�̖���
	int sheets;	//�摜�̖���

	// ���G�t�F�N�g�̕����i���̃G�t�F�N�g�ł͎g�p���Ȃ��j
	// 0:�� 1:�� 2:�� 3:�E
	int arrowDirection;
};

// �G�t�F�N�g�\���̔z��̏�����
void EffectInit(Effect effect[]);
// �G�t�F�N�g�̃Z�b�g
// x, y: �G�t�F�N�g���Đ�����}�b�v�`�b�v���W
// type: �G�t�F�N�g�̎��
// arrowDirection: ���G�t�F�N�g�̕����i���̃G�t�F�N�g�ł͎g�p���Ȃ��j
void SetEffect(Effect effect[], int x, int y, int type, int arrowDirection = -1);
// �G�t�F�N�g�̃A�j���[�V�����J�E���g��i�߂鏈��
void EffectProcess(Effect effect[]);