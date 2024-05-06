#pragma once

// 指定した範囲内にミートボックスをランダムに追加する処理
// 左上・右下を指定し、その矩形の中を出現範囲とする
// プレイヤーの座標にはミートボックスを出現させない
void AddBox(int left, int top, int right, int bottom, int playerX, int playerY);