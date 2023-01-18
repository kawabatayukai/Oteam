#include"DxLib.h"
#include"Result.h"


//Result.h�Ő錾�����֐��̒�`�������ɏ����܂�
int g_ResultImg;

//�G���h�`��
void DrawResult(int key, int& gamemode, int score)
{
	//���U���g�摜�\��
	DrawGraph(0, 0,g_ResultImg,FALSE);

	static int menuNo=0;

	SetFontSize(46);//�t�H���g�T�C�Y�ݒ�
	//�X�R�A�\��
	DrawFormatString(830, 310, 0xffffff, "%d", score);

	//���j���[�J�[�\���̈ړ�����
	if (key & PAD_INPUT_RIGHT) {
		if (++menuNo > 2)menuNo = 0;
	}
	if (key & PAD_INPUT_LEFT) {
		if (--menuNo < 0)menuNo = 2;
	}

	if (key & PAD_INPUT_B)
	{
		switch (menuNo)
		{
		case 0:
			gamemode = 1;	//�Q�[�����C���ɔ��
			break;
		case 1:
			gamemode = 0;	//�^�C�g��
			break;
		case 2:
			gamemode = 7;	//�G���h�ɔ��
			break;
		}
	}

	//���j���[�J�[�\���̕\��
	DrawTriangle(180 + menuNo * 375, 630, 220+ menuNo * 375, 660 , 180 + menuNo * 375, 680, 0x00ff00, TRUE);

}

//�G���h�摜�ǂݍ���
int LoadResultImage()
{
	if ((g_ResultImg = LoadGraph("images/resurtImg.png")) == -1)return -1;
	return 0;
}