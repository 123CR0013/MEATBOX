#include "box.h"
#include "map.h"
#include "DxLib.h"

////���������_���Ȉʒu�ɏo��������
////����E�E�����w�肵�A���̋�`�̒����o���͈͂Ƃ���
//void AddBox(int left, int top, int right, int bottom, int playerX, int playerY) {
//
//	int rx, ry;
//	while (1) {
//		rx = (rand() % (right - left + 1)) + left;
//		ry = (rand() % (bottom - top + 1)) + top;
//
//		if (box[ry * MAP_W + rx] != 1) {
//			if (playerX != rx || playerY != ry) {
//				break;
//			}
//		}
//	}
//	box[ry * MAP_W + rx] = 1;
//
//	SetEffect(effect, next_x, next_y, EFFECT_TYPE_IMPACT);
//}