#include"DxLib.h"
#include"Help.h"

//Help.h�Ő錾�����֐��̒�`�������ɏ����܂�
int g_HelpImg;

//�w���v��ʕ`��
void DrawHelp(int key, int& gamemode)
{
	// �w���v�摜�\��
	DrawGraph(0, 0, g_HelpImg, FALSE);

	//�L�[���͂�"key",GameMode��ς������Ƃ���"gamemode"��ύX���܂�
	
	// B(2)�{�^���`�F�b�N�}�X�N(X�L�[)�Ń��j���[�ɖ߂�
	if (key & PAD_INPUT_B) gamemode = 0;

	if (key & PAD_INPUT_RIGHT) gamemode = 9;

		// �����\��
	//SetFontSize(27);
	//DrawString(300, 240, "* �^�C�~���O�悭�W�����v���Ėh���g�ɂ��悤 *", 0xffffff, 0);

	//DrawString(380, 670, "--- B�{�^���������ă^�C�g���֖߂� ---", 0xffffff, 0);
}

//�w���v�摜�ǂݍ���
int LoadHelpImage()
{
	// �w���v�摜�Ǎ�
	if ((g_HelpImg = LoadGraph("images/help1.png")) == -1) return -1;
	return 0;
}