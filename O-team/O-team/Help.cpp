#include"DxLib.h"
#include"Help.h"

//Help.h�Ő錾�����֐��̒�`�������ɏ����܂�
int g_HelpImg;

//�w���v��ʕ`��
void DrawHelp(int key, int& gamemode)
{
	//�L�[���͂�"key",GameMode��ς������Ƃ���"gamemode"��ύX���܂�
	
	// B(2)�{�^���`�F�b�N�}�X�N(X�L�[)�Ń��j���[�ɖ߂�
	if (key & PAD_INPUT_B) gamemode = 0;

	// �w���v�摜�\��
	DrawGraph(0, 0, g_HelpImg, FALSE);
}

//�w���v�摜�ǂݍ���
int LoadHelpImage()
{
	// �w���v�摜�Ǎ�
	if ((g_HelpImg = LoadGraph("images/help1.png")) == -1) return -1;
	return 0;
}