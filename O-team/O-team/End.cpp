#include"DxLib.h"
#include"End.h"

int g_EndImg;	//�G���h�摜�w�i
int g_WaitTime = 0;

int EndBGM;

//�G���h�摜�`��
void DrawGameEnd(int key, int& gamemode)
{
	ChangeNextPlayVolumeSoundMem(180, EndBGM);  //���ɗ������ʂ𒲐�  �`�Q�T�T  255���ʏ�
	PlaySoundMem(EndBGM, DX_PLAYTYPE_LOOP, FALSE);
	//�G���h�摜
	DrawGraph(0, 0, g_EndImg, FALSE);
	//�N���[�Y����܂ł̎���
	if (++g_WaitTime > 330)gamemode = 8;
}


//�G���h�摜�Ǎ�
int LoadEndImage()
{
	if ((g_EndImg = LoadGraph("images/End/EndImage.png")) == -1)return -1;
	return 0;
}

//�G���h�T�E���h�Ǎ�
int LoadEndSounds() {
	if ((EndBGM = LoadSoundMem("sounds/bgm/End.wav")) == -1) return -1;

}
