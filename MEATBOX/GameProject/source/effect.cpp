#include "DXLib.h"
#include "effect.h"
#include "resource.h"



void EffectInit(Effect effect[]) {
	for (int i = 0; i < EFFECT_MAX; i++) {
		effect[i].use = 0;
		effect[i].Cnt = 0;
		effect[i].cx = 0;
		effect[i].cy = 0;
	}
}

void SetEffect(Effect effect[], int x, int y, int type, int arrowDirection) {
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].use == 0) {
			effect[i].use = 1;
			effect[i].x = x;
			effect[i].y = y;
			effect[i].cx = 0;
			effect[i].cy = 0;
			effect[i].type = type;

			switch (effect[i].type)
			{
			case EFFECT_TYPE_MOVE:
				effect[i].sheets = 6;
				effect[i].speed = 4;
				break;
			case EFFECT_TYPE_IMPACT:
				effect[i].sheets = 7;
				effect[i].speed = 1;
				break;
			case EFFECT_TYPE_HATENA:
				effect[i].cx = -16;
				effect[i].cy = -16;
				effect[i].sheets = 1;
				effect[i].speed = 24;
			case EFFECT_TYPE_ARROW_YELLOW:
			case EFFECT_TYPE_ARROW_RED:
				effect[i].sheets = 1;
				effect[i].speed = 60;
				effect[i].arrowDirection = arrowDirection;
				break;
			case EFFECT_TYPE_EXPLOSION_EYE_1:
				effect[i].sheets = 2;
				effect[i].speed = 8;
				break;
			case EFFECT_TYPE_EXPLOSION_EYE_2:
			case EFFECT_TYPE_EXPLOSION_MEAT:
				effect[i].sheets = 6;
				effect[i].speed = 8;

				effect[i].cx = -32;
				break;
			case EFFECT_TYPE_EXPLOSION_BLOOD:
				effect[i].sheets = 9;
				effect[i].speed = 8;

				effect[i].cx = -32;

				break;
			}

			break;
		}
	}
}

void EffectProcess(Effect effect[]) {
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (effect[i].use == 1) {
			effect[i].Cnt++;
			if (effect[i].type != EFFECT_TYPE_ARROW_RED && effect[i].type != EFFECT_TYPE_ARROW_YELLOW) {
				if (effect[i].Cnt > effect[i].speed * effect[i].sheets - 1) {
					effect[i].Cnt = 0;
					effect[i].use = 0;
				}
			}
		}
	}
}