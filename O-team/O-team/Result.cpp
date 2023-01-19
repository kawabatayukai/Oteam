#include"DxLib.h"
#include"Result.h"


//Result.h�Ő錾�����֐��̒�`�������ɏ����܂�
int g_ResultImg;					//���U���g�摜�p
int g_FontR[7] = { 0,0,0,0,0,0,0 };		//���U���g�t�H���g�p
int g_SentakImg;					//�I���摜�p
int g_Miko[6] = { 0,0,0,0,0,0 };		//�ޏ��摜�p

int g_kitune;	//�ς̂��ʃJ�[�\���p
int page = 0;		//�y�[�W�ړ�

int y = 0;			//�ޏ��摜�ړ��p
int gWaitTime = 0;	//�ޏ��摜�؂�ւ��p
int check = 0;		//�ޏ��摜�؂�ւ��p
int flg = FALSE;	//�ޏ��摜�؂�ւ��p

int ResultBGM;
int ClickResult;
int CursorMoveResult;

//�G���h�`��
void DrawResult(int key, int& gamemode, int score)
{

	ChangeNextPlayVolumeSoundMem(130, ResultBGM);  //���ɗ������ʂ𒲐�  �`�Q�T�T  255���ʏ�
	PlaySoundMem(ResultBGM, DX_PLAYTYPE_LOOP, FALSE);

	//���U���g�摜�\��
	DrawGraph(0, 0, g_ResultImg, FALSE);

	static int menuNo = 0;

	//���U���g��ʂ���I����ʂɈړ�����p
	if (key & PAD_INPUT_4) {
		page = 1;

	}

	switch (page) {
	case 0:
		//���U���g�摜�\��
		DrawGraph(0, 0, g_ResultImg, FALSE);
		SetFontSize(46);//�t�H���g�T�C�Y�ݒ�

		//�X�R�A�\��
		DrawFormatString(830, 350, 0xff4040, "%d", score);

		break;

	case 1://�I�����
		DrawGraph(0, 0, g_SentakImg, FALSE);

		//���j���[�J�[�\���̕\��
		DrawGraph(120 + menuNo * 355, 290, g_kitune, TRUE);

		//�t�H���g�摜�\��
		DrawGraph(180, 280, g_FontR[0], TRUE);
		DrawGraph(540, 290, g_FontR[1], TRUE);
		DrawGraph(890, 290, g_FontR[2], TRUE);



		//���j���[�J�[�\���̈ړ�����
		if (key & PAD_INPUT_RIGHT) {
			if (++menuNo > 2)menuNo = 0;
		}
		if (key & PAD_INPUT_LEFT) {
			if (--menuNo < 0)menuNo = 2;
		}
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


		//�ޏ�����̉摜�؂�ւ�
		switch (menuNo)
		{
		case 0:
			WalkImg();
			DrawGraph(180, 280, g_FontR[3], TRUE);

			check = 0;
			break;
		case 1:
			JampImg();
			DrawGraph(540, 290, g_FontR[4], TRUE);

			check = 0;
			break;
		case 2:
			SleepImg();
			DrawGraph(890, 290, g_FontR[5], TRUE);
			break;
		}



		if (key & PAD_INPUT_B)
		{
		PlaySoundMem(ClickResult, DX_PLAYTYPE_BACK);
		StopSoundMem(ResultBGM);
			switch (menuNo)
			{
			case 0:
				gamemode = 2;	//�Q�[�����C���ɔ��
				break;
			case 1:
				gamemode = 0;	//�^�C�g��
				break;
			case 2:
				gamemode = 7;	//�G���h�ɔ��
				break;
			}

		}
		break;
	}
}

//���U���g�摜�ǂݍ���
int LoadResultImage()
{
	if ((g_ResultImg = LoadGraph("images/Result/Score.png")) == -1)return -1;	//���U���g�摜�Ǎ�
	if ((g_SentakImg = LoadGraph("images/Result/SentakImg.png")) == -1)return -1;	//�I����ʉ摜�Ǎ�
	if ((g_kitune = LoadGraph("images/Result/kitsune.png")) == -1)return -1;	//�ς̂��ʉ摜�Ǎ�

	if (LoadDivGraph("images/Result/FontResurt.png", 6, 1, 6, 350, 109, g_FontR) == -1)return -1; //�t�H���g�摜�Ǎ�
	if (LoadDivGraph("images/Result/SentakM.png", 6, 6, 1, 64, 64, g_Miko) == -1)return -1;	//�ޏ�����摜�Ǎ�


	return 0;
}

//�ޏ�����摜�W�����v
void JampImg(void)
{

	if (flg == FALSE) {

		DrawRotaGraph(655, 545, 2.5, 0, g_Miko[1], TRUE);

	}

	if (++gWaitTime > 220) {
		flg = TRUE;
		y = -40;

		if (flg == TRUE) {

			DrawRotaGraph(655, 545 + y, 2.5, 0, g_Miko[0], TRUE);

		}
	}

	if (++gWaitTime > 500) {
		flg = FALSE;
		gWaitTime = 0;
	}



}

//�ޏ�����摜����
void WalkImg(void) {
	if (flg == FALSE) {

		DrawRotaGraph(655, 545, 2.5, 0, g_Miko[1], TRUE);

	}

	if (++gWaitTime > 220) {
		flg = TRUE;

		if (flg == TRUE) {

			DrawRotaGraph(655, 545, 2.5, 0, g_Miko[3], TRUE);

		}
	}

	if (++gWaitTime > 500) {
		flg = FALSE;
		gWaitTime = 0;
	}



}

//�ޏ�����摜�|���
void SleepImg(void) {

	if (check == 0) {
		flg = FALSE;
		check = 1;
	}


	if (flg == FALSE)
	{
		DrawRotaGraph(655, 545, 2.5, 0, g_Miko[5], TRUE);

		if (++gWaitTime > 420)
		{
			flg = TRUE;
		}
	}


	if (flg == TRUE)
	{
		DrawRotaGraph(655, 545, 2.5, 0, g_Miko[4], TRUE);
	}


	if (++gWaitTime > 500) {
		gWaitTime = 0;
	}

}

int LoadResultSounds() {
	if ((ResultBGM = LoadSoundMem("sounds/bgm/Result.wav")) == -1) return -1;
	if ((ClickResult = LoadSoundMem("sounds/se/Click.wav")) == -1) return -1;
	if ((CursorMoveResult = LoadSoundMem("sounds/se/CursorMove.wav")) == -1) return -1;
}