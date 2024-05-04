#pragma once

#define TENTACLE_MAX 4
#define TENTACLE_ATTACK_ROW 8

struct Boss {
	int x, y;
	int animCnt;
	int animSpeed;
};

struct Tentacle {
	int use;
	int x, y;		//Gè‚ÌªŒ³‚ÌÀ•W
	int direction;	//UŒ‚•ûŒüiGè‚ÌŒü‚«j
	int range;		//UŒ‚”ÍˆÍ
	int row; //UŒ‚‚·‚é—ñ

	int isReady;	//UŒ‚‘Ò‹@‚©‚Ç‚¤‚©iŸ‚ÉUŒ‚‚·‚éGè‚ª1j

	int isRemain;	//ƒXƒe[ƒWã‚É—¯‚Ü‚Á‚Ä‚¢‚é‚©

	int animCnt;
	int animSpeed;
};

struct AOE {
	int x, y;
	int use;

	int animCnt;
	int animSpeed;
	int sheets;
};

void BossInit();

void TentacleInit(Tentacle[]);
void AOEInit(AOE[]);
void SetTentacleReady(Tentacle[], AOE[]);
void SetBossAOE(Tentacle[], AOE[]);
void BossAttack(Tentacle[]);
void DeleteTentacle(Tentacle[]);