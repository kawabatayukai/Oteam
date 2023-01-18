#include"DxLib.h"
#include"Result.h"


//Result.h�Ő錾�����֐��̒�`�������ɏ����܂�
int g_ResultImg;
int g_FontR[7]={0,0,0,0,0,0,0};		//���U���g
int g_SentakImg;		//�I���摜�p
int g_Miko[4]={0,0,0,0};		//�ޏ��摜�p
int g_kitune;	//�ς̂��ʃJ�[�\���p
int page=0;		//�y�[�W�ړ�

//�G���h�`��
void DrawResult(int key, int& gamemode, int score)
{

	//���U���g�摜�\��
	DrawGraph(0, 0,g_ResultImg,FALSE);

	static int menuNo=0;

	//���U���g��ʂ���I����ʂɈړ�����p
	if (key & PAD_INPUT_A) {
		page = 1;

	}

	switch(page) {
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
		//DrawTriangle(140 + menuNo * 375, 310, 180 + menuNo * 375, 350, 130 + menuNo * 345, 350, 0x00ff00, TRUE);
		DrawGraph(120+menuNo*355, 290, g_kitune, TRUE);

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


		//�ޏ�����̉摜�؂�ւ�
		switch (menuNo)
		{
		case 0:
			DrawGraph(180, 280, g_FontR[3], TRUE);
			DrawRotaGraph(655, 545, 2.5, 0, g_Miko[0], TRUE);
			break;
		case 1:
			DrawGraph(540, 290, g_FontR[4], TRUE);
			DrawRotaGraph(655, 545, 2.5, 0, g_Miko[1], TRUE);
			break;
		case 2:
			DrawGraph(890, 290, g_FontR[5], TRUE);
			DrawRotaGraph(655, 545, 2.5, 0, g_Miko[2], TRUE);
			break;
		}


		
		if (key & PAD_INPUT_B)
		{
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
	if ((g_ResultImg = LoadGraph("images/ResultImg.png")) == -1)return -1;	//���U���g�摜�Ǎ�
	if ((g_SentakImg = LoadGraph("images/SentakImg.png")) == -1)return -1;	//�I����ʉ摜�Ǎ�
	if ((g_kitune = LoadGraph("images/kitsune.png")) == -1)return -1;	//�ς̂��ʉ摜�Ǎ�

	if (LoadDivGraph("images/FontResurt.png", 6, 1, 6, 350, 109, g_FontR) == -1)return -1; //�t�H���g�摜�Ǎ�
	if (LoadDivGraph("images/SentakM.png", 3, 3, 1, 64, 64, g_Miko) == -1)return -1;	//�ޏ�����摜�Ǎ�

	
	return 0;
}