#include"DxLib.h"
#include"Title.h"
#include"Ranking.h"

//Title.h�Ő錾�����֐��̒�`�������ɏ����܂�

//�ϐ��錾
int g_TitleImg;		//�^�C�g���摜�\���p
int g_TitleWhite[8]={0,0,0,0,0,0,0,0};	//�^�C�g���t�H���g�\���p
int g_TitleBlack[8]={0,0,0,0,0};	//�^�C�g���t�H���g�\���p
int g_TitleCasol;

//�T�E���h�p�ϐ�
int TitleBGM;
int Click;
int CursorMove;

//�Q�[���^�C�g���`��
void DrawGameTitle(int key, int& gamemode)
{
	if (CheckSoundMem(TitleBGM) == FALSE) {
		PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP, FALSE);
	}
	static int menuNo = 0;
	static int M_PI = 0;
	static int gConeImg = 0;

	//�^�C�g���摜
	DrawGraph(0, 0, g_TitleImg, FALSE);

	/**
	for (int i = 0; i < 4; i++) {
		DrawGraph(920, 395+i*80, g_TitleFont[i], TRUE);

	}*/


	DrawGraph(920, 395,g_TitleWhite[4], TRUE);
	DrawGraph(920, 395 + 80, g_TitleWhite[5], TRUE);
	DrawGraph(920, 395 + 150, g_TitleWhite[6], TRUE);
	DrawGraph(920, 395 + 220, g_TitleWhite[7], TRUE);
	

	//DrawGraph(0, 30, gNumberImg[tempScore % 10], TRUE);

	ChangeNextPlayVolumeSoundMem(180, CursorMove);  //���ɗ������ʂ𒲐�  �`�Q�T�T  255���ʏ�
	//���j���[�J�[�\���̈ړ�����
	if (key & PAD_INPUT_DOWN) {
		PlaySoundMem(CursorMove, DX_PLAYTYPE_BACK);
		if (++menuNo > 3)menuNo = 0;
	}
	if (key & PAD_INPUT_UP) {
		PlaySoundMem(CursorMove, DX_PLAYTYPE_BACK);
		if (--menuNo < 0)menuNo = 3;
	}

	
	//�@�^�C�g���A���j���[�A�J�[�\���摜�̕\��
	DrawRotaGraph(90, 220 + menuNo * 40, 0.7f, M_PI / 2, gConeImg, TRUE);
	//DrawTriangle(860, 405 + menuNo * 80, 900, 435 + menuNo * 80, 860, 455 + menuNo * 80, 0x00ff00, TRUE);
	DrawGraph(860, 405 + menuNo * 70, g_TitleCasol, TRUE);

		switch (menuNo)
		{
		case 0:
			DrawGraph(920, 395, g_TitleWhite[0], TRUE);
			break;
		case 1:
			DrawGraph(920, 395 + 80, g_TitleWhite[1], TRUE);
			break;
		case 2:
			DrawGraph(920, 395 + 150, g_TitleWhite[2], TRUE);
			break;
		case 3:
			DrawGraph(920, 395 + 220, g_TitleWhite[3], TRUE);
			break;
		}
	

	if (key & PAD_INPUT_B)
	{
		PlaySoundMem(Click, DX_PLAYTYPE_BACK);
		switch (menuNo)
		{
		case 0:
			StopSoundMem(TitleBGM);
			LoadTitleSounds();       //������x�ǂݍ���Ł@�ȍŏ�����n�߂�悤�ɂ���
			gamemode = 1;	//�Q�[�����C���ɔ��
			break;
		case 1:
			gamemode = 4;	//�w���v�ɔ��
			break;
		case 2:
			StopSoundMem(TitleBGM);
			LoadTitleSounds();
			LoadRankingSounds();
			gamemode = 3;	//�����L���O�ɔ��
			break;
		case 3:
			StopSoundMem(TitleBGM);
			LoadTitleSounds();
			gamemode = 7;	//�G���h�ɔ��
			break;
		}
	}

}

//�^�C�g���摜�ǂݍ���
int LoadTitleImage()
{
	g_TitleImg = LoadGraph("images/Title/TitleImage.png");
	g_TitleCasol = LoadGraph("images/Title/TitleCasol.png");
	if(LoadDivGraph("images/Title/TitleFont.png",8,1,8,300,69, g_TitleWhite)==-1)return -1;
	return 0;
}

//�T�E���h�ǂݍ���
int LoadTitleSounds() {
	if ((TitleBGM = LoadSoundMem("sounds/bgm/Title.Help.wav")) == -1) return -1;
	if ((Click = LoadSoundMem("sounds/se/Click.wav")) == -1) return -1;
	if ((CursorMove = LoadSoundMem("sounds/se/CursorMove.wav")) == -1) return -1;
}