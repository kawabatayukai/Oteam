#include"DxLib.h"
#include"End.h"

int g_EndImg;	//�G���h�摜�w�i
int g_WaitTime = 0;

//�G���h�摜�`��
void DrawGameEnd(int key, int& gamemode)
{
	//�G���h�摜
	DrawGraph(0, 0, g_EndImg, FALSE);
	//�N���[�Y����܂ł̎���
	if (++g_WaitTime > 360)gamemode = 8;
}


//�G���h�摜�Ǎ�
int LoadEndImage()
{
	if ((g_EndImg = LoadGraph("images/EndImage.png")) == -1)return -1;
	return 0;
}
