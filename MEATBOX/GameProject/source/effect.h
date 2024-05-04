#pragma once
#define EFFECT_MAX	10 //EFFECT�\���̔z��̍ő�v�f��

struct Effect
{
	int x, y;	//�G�t�F�N�g���Đ�������W
	int cx, cy;
	int Cnt;	//
	int use;	//���̔z��v�f���g�p���Ă��邩
	int type;	//�G�t�F�N�g�̎��
	int speed;	//�G�t�F�N�g�̍Đ����x
	int sheets;	//�摜�̖���

	int arrowDirection; //���G�t�F�N�g�̕���
};


void EffectInit(Effect[]);

void SetEffect(Effect[], int, int, int, int arrowDirection = -1);

void EffectProcess(Effect[]);