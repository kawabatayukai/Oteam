#include"DxLib.h"

int g_HelpImg2;

//�T�E���h�p�ϐ�
int ClickHelp2;
int CursorMoveHelp2;

void DrawHelp2(int key, int& gamemode)
{
	DrawGraph(0, 0, g_HelpImg2, FALSE);


	//���ɗ������ʂ𒲐�  �`�Q�T�T  255���ʏ�
	ChangeNextPlayVolumeSoundMem(180, CursorMoveHelp2);
	// B(2)�{�^���`�F�b�N�}�X�N(X�L�[)�Ń��j���[�ɖ߂�
	if (key & PAD_INPUT_B) {
		PlaySoundMem(ClickHelp2, DX_PLAYTYPE_BACK);
		gamemode = 0;
	}

	if (key & PAD_INPUT_LEFT) {
		PlaySoundMem(CursorMoveHelp2, DX_PLAYTYPE_BACK);
		gamemode = 4;
	}
}

//�w���v�摜�ǂݍ���
int LoadHelp2Image()
{
	if ((g_HelpImg2 = LoadGraph("images/help2.png")) == -1) return -1;
}

//�w���v�T�E���h�ǂݍ���
int LoadHelp2Sounds() {
	if ((ClickHelp2 = LoadSoundMem("sounds/se/Click.wav")) == -1) return -1;
	if ((CursorMoveHelp2 = LoadSoundMem("sounds/se/CursorMove.wav")) == -1) return -1;
}