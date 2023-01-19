#include"DxLib.h"
#include"Result.h"


//Result.h�Ő錾�����֐��̒�`�������ɏ����܂�
int g_ResultImg;

int ResultBGM;
int ClickResult;
int CursorMoveResult;

//�G���h�`��
void DrawResult(int key, int& gamemode, int score)
{
	ChangeNextPlayVolumeSoundMem(130, ResultBGM);  //���ɗ������ʂ𒲐�  �`�Q�T�T  255���ʏ�
	PlaySoundMem(ResultBGM, DX_PLAYTYPE_LOOP, FALSE);

	//���U���g�摜�\��
	DrawGraph(0, 0,g_ResultImg,FALSE);

	static int menuNo=0;

	SetFontSize(46);//�t�H���g�T�C�Y�ݒ�
	//�X�R�A�\��
	DrawFormatString(830, 310, 0xffffff, "%d", score);

	ChangeNextPlayVolumeSoundMem(180, CursorMoveResult);  //���ɗ������ʂ𒲐�  �`�Q�T�T  255���ʏ�
	//���j���[�J�[�\���̈ړ�����
	if (key & PAD_INPUT_RIGHT) {
		PlaySoundMem(CursorMoveResult, DX_PLAYTYPE_BACK);
		if (++menuNo > 2)menuNo = 0;
	}
	if (key & PAD_INPUT_LEFT) {
		PlaySoundMem(CursorMoveResult, DX_PLAYTYPE_BACK);
		if (--menuNo < 0)menuNo = 2;
	}

	if (key & PAD_INPUT_B)
	{
		PlaySoundMem(ClickResult, DX_PLAYTYPE_BACK);
		StopSoundMem(ResultBGM);
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

int LoadResultSounds() {
	if ((ResultBGM = LoadSoundMem("sounds/bgm/Result.wav")) == -1) return -1;
	if ((ClickResult = LoadSoundMem("sounds/se/Click.wav")) == -1) return -1;
	if ((CursorMoveResult = LoadSoundMem("sounds/se/CursorMove.wav")) == -1) return -1;
}