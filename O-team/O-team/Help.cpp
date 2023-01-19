#include"DxLib.h"
#include"Help.h"

//Help.h�Ő錾�����֐��̒�`�������ɏ����܂�
int g_HelpImg;

//�T�E���h�p�ϐ�
int ClickHelp;
int CursorMoveHelp;

//�w���v��ʕ`��
void DrawHelp(int key, int& gamemode)
{
	// �w���v�摜�\��
	DrawGraph(0, 0, g_HelpImg, FALSE);

	//�L�[���͂�"key",GameMode��ς������Ƃ���"gamemode"��ύX���܂�

	//���ɗ������ʂ𒲐�  �`�Q�T�T  255���ʏ�
	ChangeNextPlayVolumeSoundMem(220, ClickHelp);
	ChangeNextPlayVolumeSoundMem(200, CursorMoveHelp);
	// B(2)�{�^���`�F�b�N�}�X�N(X�L�[)�Ń��j���[�ɖ߂�
	if (key & PAD_INPUT_B) {
		PlaySoundMem(ClickHelp, DX_PLAYTYPE_BACK);
		gamemode = 0;
	}

	if (key & PAD_INPUT_RIGHT) {
		PlaySoundMem(CursorMoveHelp, DX_PLAYTYPE_BACK);
		gamemode = 9;
	}

	// �����\��
//SetFontSize(27);
//DrawString(300, 240, "* �^�C�~���O�悭�W�����v���Ėh���g�ɂ��悤 *", 0xffffff, 0);

//DrawString(380, 670, "--- B�{�^���������ă^�C�g���֖߂� ---", 0xffffff, 0);
}

//�w���v�摜�ǂݍ���
int LoadHelpImage()
{
	// �w���v�摜�Ǎ�
	if ((g_HelpImg = LoadGraph("images/Help/help1.png")) == -1) return -1;

	return 0;
}

//�w���v�T�E���h�ǂݍ���
int LoadHelpSounds() {
	if ((ClickHelp = LoadSoundMem("sounds/se/Click.wav")) == -1) return -1;
	if ((CursorMoveHelp = LoadSoundMem("sounds/se/CursorMove.wav")) == -1) return -1;
}