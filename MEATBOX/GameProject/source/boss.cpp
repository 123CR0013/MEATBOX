#include "DxLib.h"
#include "boss.h"
#include "map.h"
#include "resource.h"

// �{�X�̏���������
void BossInit() {
	// �{�X�摜�̓ǂݍ���

	// DxLib�̎d�l��A��x�摜�Ƀt�B���^�[��������Ɩ߂��Ȃ��̂ŁC���̊֐���boss�X�e�[�W�J�n���ɖ���ǂݍ��݂�����

	for (int i = 0; i < 16; i++) {
		DeleteGraph(cgBoss[i]);
	}

	cgBoss[0] = LoadGraph("res/enemy/boss/boss1.png");
	cgBoss[1] = LoadGraph("res/enemy/boss/boss2.png");
	cgBoss[2] = LoadGraph("res/enemy/boss/boss3.png");
	cgBoss[3] = LoadGraph("res/enemy/boss/boss4.png");
	cgBoss[4] = LoadGraph("res/enemy/boss/boss5.png");
	cgBoss[5] = LoadGraph("res/enemy/boss/boss6.png");
	cgBoss[6] = LoadGraph("res/enemy/boss/boss7.png");
	cgBoss[7] = LoadGraph("res/enemy/boss/boss8.png");
	cgBoss[8] = LoadGraph("res/enemy/boss/boss9.png");
	cgBoss[9] = LoadGraph("res/enemy/boss/boss10.png");
	cgBoss[10] = LoadGraph("res/enemy/boss/boss11.png");
	cgBoss[11] = LoadGraph("res/enemy/boss/boss12.png");
	cgBoss[12] = LoadGraph("res/enemy/boss/boss13.png");
	cgBoss[13] = LoadGraph("res/enemy/boss/boss14.png");
	cgBoss[14] = LoadGraph("res/enemy/boss/boss15.png");
	cgBoss[15] = LoadGraph("res/enemy/boss/boss16.png");
}

// �G��\���̂̏�����
void TentacleInit(Tentacle tentacle[]) {
	int x, y;
	x = 10;
	y = 8;
	for (int i = 0; i < TENTACLE_MAX; i++) {
		if (i % 2 == 0) {
			tentacle[i].x = x;
			tentacle[i].direction = 1;
		}else{
			tentacle[i].x = 29 - x;
			tentacle[i].direction = -1;
		}
		tentacle[i].use = 1;
		tentacle[i].y = y + i;
		tentacle[i].range = 8;
		tentacle[i].row = -1;

		tentacle[i].isReady = 0;
		tentacle[i].isRemain = 0;

		tentacle[i].animCnt = 0;
		tentacle[i].animSpeed = 16;
	}
}

// AOE�\���́i�U���\���͈́j�̏�����
void AOEInit(AOE aoe[]) {
	for (int i = 0; i < 8; i++) {
		aoe[i].use = 0;
		aoe[i].animCnt = 0;
		aoe[i].animSpeed = 8;
		aoe[i].sheets = 2;
	}
}

// �G����U���ҋ@��Ԃɂ���
void SetTentacleReady(Tentacle tentacle[], AOE aoe[]) {
	// AOE�\���̂̏�����
	AOEInit(aoe);

	// ���ݍU�����̐G��̏�Ԃ��U����Ԃɂ���
	for (int i = 0; i < TENTACLE_MAX; i++) {
		if (tentacle[i].isRemain == 1) {
			tentacle[i].isRemain = 0;
			// enemyMap����U���͈͓��̓G�����锻�������
			for (int j = 1; j <= tentacle[i].range; j++) {
				enemyMap[(tentacle[i].row + TENTACLE_ATTACK_ROW) * MAP_W + tentacle[i].x + (tentacle[i].direction * j)] = 0;
			}
		}
	}

	// �c���Ă���G�肪���邩�ǂ����𔻒肷��
	int remainTentacle = 0;
	for (int i = 0; i < TENTACLE_MAX; i++) {
		if (tentacle[i].use == 1) {
			remainTentacle = 1;
		}
	}

	// �c���Ă���G�肪����ꍇ
	if (remainTentacle == 1) {
		//���ɍU������G��������_���Ɍ���
		int r;
		while (1) { //���łɓ|���ꂽ�G�肪�I�΂�Ȃ��悤�ɂ���
			r = rand() % TENTACLE_MAX;
			if (tentacle[r].use != 0) break; //�܂��c���Ă���G�肪�I�΂ꂽ�烋�[�v�𔲂���
		}
		tentacle[r].isReady = 1;
		tentacle[r].row = rand() % 4;
	}
}

// AOE��ݒ肷��
//�{�X�̍U���͈͂𐔃^�[���O�ɕ\������
void SetBossAOE(Tentacle tentacle[], AOE aoe[]) {
	for (int i = 0; i < TENTACLE_MAX; i++) {
		//�U���ҋ@��Ԃ̐G��̍U���͈͂�AOE���Z�b�g����
		if (tentacle[i].isReady == 1) {
			for (int j = 1; j <= tentacle[i].range; j++) {
				aoe[j - 1].x = tentacle[i].x + (tentacle[i].direction * j);
				aoe[j - 1].y = tentacle[i].row + TENTACLE_ATTACK_ROW;
				aoe[j - 1].use = 1;
			}
			break;
		}
	}
}

// �{�X�̍U������
void BossAttack(Tentacle tentacle[]) {
	for (int i = 0; i < TENTACLE_MAX; i++) {
		// �U���ҋ@��Ԃ̐G�肪����ꍇ
		if (tentacle[i].isReady == 1) {
			// �U������
			for (int j = 1; j <= tentacle[i].range; j++) {
				// �U���͈͓��̔�����
				box[(tentacle[i].row + TENTACLE_ATTACK_ROW) * MAP_W + tentacle[i].x + (tentacle[i].direction * j)] = 0;
				// �U���͈͓��ɓG�����锻�������
				enemyMap[(tentacle[i].row + TENTACLE_ATTACK_ROW) * MAP_W + tentacle[i].x + (tentacle[i].direction * j)] = 9;
			}

			// �U���ҋ@��Ԃ̉���
			tentacle[i].isReady = 0;
			// �U����Ԃ̐ݒ�
			tentacle[i].isRemain = 1;

			// SE�̍Đ�
			PlaySoundMem(sound[4], DX_PLAYTYPE_BACK);
			break;
		}
	}
}

// �G������������i�v���C���[����G��ւ̍U���j
void DeleteTentacle(Tentacle tentacle[]) {
	for (int i = 0; i < TENTACLE_MAX; i++) {
		// �X�e�[�W��Ɏc���Ă���G��
		if (tentacle[i].isRemain == 1) {
			// �v�f���g�p���Ă��Ȃ���Ԃɂ���
			tentacle[i].use = 0;

			// �U���͈͓��̓G�����锻�������
			for (int j = 1; j <= tentacle[i].range; j++) {
				enemyMap[(tentacle[i].row + TENTACLE_ATTACK_ROW) * MAP_W + tentacle[i].x + (tentacle[i].direction * j)] = 0;
			}
			break;
		}
	}
}
