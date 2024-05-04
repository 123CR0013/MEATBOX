#include "player.h"


void PlayerInit(Player *player, int x, int y) {
	player->x = x;
	player->y = y;
	player->moveCnt = 0;
	player->animCnt = 0;
	player->animSpeed = 8;
	player->arrow = 0;
}


