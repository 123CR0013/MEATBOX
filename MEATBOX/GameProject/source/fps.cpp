#include "DxLib.h"
#include "fps.h"

// �t���[�����[�g��60�ɌŒ肷��
// �Q�l�T�C�g: 
// https://dixq.net/rp/43.html
// https://dixq.net/forum/viewtopic.php?t=4295 


//fps
#define FRAME 60

//fps�̃J�E���^�A60�t���[����1���ƂȂ鎞�����L�^����ϐ�
int fps_count, count0t;
//���ς��v�Z���邽��60���1�����Ԃ��L�^
int f[FRAME];
//����fps
double ave;

//FLAME fps �ɂȂ�悤��fps���v�Z�E����
void fps_wait() {
    int term, i, gnt;
    static int t = 0;
    if (fps_count == 0) {//60�t���[����1��ڂȂ�
        if (t == 0)//���S�ɍŏ��Ȃ�܂��Ȃ�
            term = 0;
        else//�O��L�^�������Ԃ����Ɍv�Z
            term = count0t + 1000 - GetNowCount();
    }
    else    //�҂ׂ�����=���݂���ׂ�����-���݂̎���
        term = (int)(count0t + fps_count * (1000.0 / FRAME)) - GetNowCount();

    if (term > 0)//�҂ׂ����Ԃ����҂�
        Sleep(term);

    gnt = GetNowCount();

    if (fps_count == 0)//60�t���[����1�x������
        count0t = gnt;
    f[fps_count] = gnt - t;//�P���������Ԃ��L�^
    t = gnt;
    //���όv�Z
    if (fps_count == FRAME - 1) {
        ave = 0;
        for (i = 0; i < FRAME; i++)
            ave += f[i];
        ave /= FRAME;
    }
    fps_count = (++fps_count) % FRAME;
}

//x,y�̈ʒu��fps��\��
void draw_fps(int x, int y) {
    if (ave != 0) {
        DrawFormatString(x, y, GetColor(255, 255, 255), "[%.1f]", 1000 / ave);
    }
}
