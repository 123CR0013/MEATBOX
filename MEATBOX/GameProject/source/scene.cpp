#include "DxLib.h"
#include "scene.h"
#include "gamemain.h"
#include "resource.h"

int cgBg[2];
int cgGameClear[4];
int animCnt;

int talkNum = 0;


int cgPrologue;
int cgInstruction;

void SceneInit() {
	cgBg[0] = LoadGraph("res/MEAT BOX rogo.png"); //�^�C�g�����
	cgBg[1] = LoadGraph("res/gameover.png");//�Q�[���I�[�o�[���
	cgGameClear[0] = LoadGraph("res/stageclear/gameclear 1.png");//�Q�[���N���A���
	cgGameClear[1] = LoadGraph("res/stageclear/gameclear 2.png");
	cgGameClear[2] = LoadGraph("res/stageclear/gameclear 3.png");
	cgGameClear[3] = LoadGraph("res/stageclear/gameclear 4.png");


	cgPrologue = LoadGraph("res/prologue.png");
	cgInstruction = LoadGraph("res/meat_info.png");

	animCnt = 0;
}

// �V�[���̐؂�ւ�����
// �����Fscene �`�悷��V�[���̔ԍ�
// 0:�^�C�g����� 1:�Q�[����� 2:�Q�[���I�[�o�[��� 3:�Q�[���N���A���
void SceneManage(int scene) {
	switch (scene)
	{
	case SCENE_TITLE:
		TitleDraw();
		break;
	case SCENE_GAME:
		GameDraw();
		break;
	case SCENE_GAMEOVER:
		GameOverDraw();
		break;
	case SCENE_GAMECLEAR:
		GameClearDraw();
		animCnt++;
		break;

	case SCENE_CHARATALK:
		CharaTalkDraw();
		break;
	}
}

void TitleDraw() {
	DrawGraph(0, -70, cgBg[0], TRUE);
}

void GameOverDraw() {
	DrawGraph(0, 0, cgBg[1], TRUE);
}

void GameClearDraw() {
	DrawGraph(0, 0, cgGameClear[(animCnt / 6) % 4], TRUE);
}

void CharaTalkDraw() {
	if (talkNum == 0) {
		DrawGraph(0, 0, cgPrologue, TRUE);
	}
	else {
		DrawGraph(0, 0, cgInstruction, TRUE);
	}
}