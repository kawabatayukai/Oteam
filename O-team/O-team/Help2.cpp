#include"DxLib.h"

int g_HelpImg2;

void DrawHelp2(int key, int& gamemode)
{
	DrawGraph(0, 0, g_HelpImg2, FALSE);

	// B(2)�{�^���`�F�b�N�}�X�N(X�L�[)�Ń��j���[�ɖ߂�
	if (key & PAD_INPUT_B) gamemode = 0;

	if (key & PAD_INPUT_LEFT) gamemode = 4;

}

//�w���v�摜�ǂݍ���
int LoadHelp2Image()
{
	if ((g_HelpImg2 = LoadGraph("images/help2.png")) == -1) return -1;
}