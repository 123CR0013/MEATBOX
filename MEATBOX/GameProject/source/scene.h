#pragma once


#define SCENE_TITLE 0
#define SCENE_GAME 1
#define SCENE_GAMEOVER 2

#define SCENE_GAMECLEAR 3

#define SCENE_CHARATALK 4


extern int talkNum;

void SceneInit();
// �V�[���̐؂�ւ�����
// �����Fscene �`�悷��V�[���̔ԍ�
// 0:�^�C�g����� 1:�Q�[����� 2:�Q�[���I�[�o�[��� 3:�Q�[���N���A���
void SceneManage(int);
//void ChangeScene(int*);

void TitleDraw();
void GameOverDraw();
void GameClearDraw();

void CharaTalkDraw();