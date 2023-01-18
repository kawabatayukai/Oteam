#include"DxLib.h"
#include"Title.h"

//Title.h�Ő錾�����֐��̒�`�������ɏ����܂�

//�ϐ��錾
int g_TitleImg;

//�Q�[���^�C�g���`��
void DrawGameTitle(int key, int& gamemode)
{


	static int menuNo = 0;
	static int M_PI = 0;
	static int gConeImg = 0;

	//�^�C�g���摜
	DrawGraph(0, 0, g_TitleImg, FALSE);

	//���j���[�J�[�\���̈ړ�����
	if (key & PAD_INPUT_DOWN) {
		if (++menuNo > 3)menuNo = 0;
	}
	if (key & PAD_INPUT_UP) {
		if (--menuNo < 0)menuNo = 3;
	}

	//�@�^�C�g���A���j���[�A�J�[�\���摜�̕\��
	DrawRotaGraph(90, 220 + menuNo * 40, 0.7f, M_PI / 2, gConeImg, TRUE);
	DrawTriangle(860, 400 + menuNo * 80, 900, 430 + menuNo * 80, 860, 450 + menuNo * 80, 0x00ff00, TRUE);

	if (key & PAD_INPUT_B)
	{
		switch (menuNo)
		{
		case 0:
			gamemode = 1;	//�Q�[�����C���ɔ��
			break;
		case 1:
			gamemode = 4;	//�w���v�ɔ��
			break;
		case 2:
			gamemode = 3;	//�����L���O�ɔ��
			break;
		case 3:
			gamemode = 7;	//�G���h�ɔ��
			break;
		}
	}

}

//�^�C�g���摜�ǂݍ���
int LoadTitleImage()
{
	g_TitleImg = LoadGraph("images/titleimages.png");
	return 0;
}