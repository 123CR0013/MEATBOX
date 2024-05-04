#include "DxLib.h"
#include <time.h>


// 画面設定
constexpr auto SCREEN_W = 1920;  ///< 画面の横解像度
constexpr auto SCREEN_H = 1080;  ///< 画面の縦解像度
constexpr auto SCREEN_DEPTH = 32;    ///< １ドットあたりのビット数


void GameMain();	// gamemain.cpp に実体を記述

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 初期化 -------------------------------------------------------------------------
	// ＤＸライブラリ初期化処理
	SetOutApplicationLogValidFlag(false); 		  // log.txtを出力しない
	SetGraphMode(SCREEN_W, SCREEN_H, SCREEN_DEPTH);	// 画面の解像度を横1920×縦1080、1ドットあたり32ビットに指定する
	ChangeWindowMode(true);							// ウィンドウモードに指定する
	if (DxLib_Init() == -1)
	{	// エラーが起きたら直ちに終了
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// 描画先画面を裏画面にセット

	SetMouseDispFlag(FALSE);

	// 乱数初期化
	srand((unsigned)time(NULL));

	// ゲームメイン
	GameMain();


	// 解放 ---------------------------------------------------------------------------
	DxLib_End();		// ＤＸライブラリ使用の終了処理

	// 終了
	return 0;
}
