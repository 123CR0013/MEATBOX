#pragma once


// �v���C���[���
struct Player
{
	int x, y; // ���W�i�`�b�v�P�ʁj
	int moveCnt;

	int animCnt;
	int animSpeed;
	int IsSound;
	int sound_cnt;

	int stepCnt;
	int arrow;
};



void PlayerInit(Player *, int, int);