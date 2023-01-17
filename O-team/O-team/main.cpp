#include"DxLib.h"
#include"information.h"  //�g������ .h�t�@�C�� ���C���N���[�h���܂�

#include"Help.h"
#include"Ranking.h"
#include"Result.h"
#include"Title.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("Neko");             //�^�C�g����ݒ�
	ChangeWindowMode(TRUE);                //�E�B���h�E���[�h�ŋN��

	//�E�B���h�E�T�C�Y��ݒ�
	SetGraphMode(SCREENSIZE_X, SCREENSIZE_Y, 32);

	if (DxLib_Init() == -1) return -1;     //DX���C�u�����̏���������
	SetDrawScreen(DX_SCREEN_BACK);         //�`����ʂ𗠂ɂ���

	//�摜�ǂݍ���
	if (LoadImages() == -1) return -1;

	// �����L���O�f�[�^�̓Ǎ�
	if (ReadRanking() == -1) return -1;

	//�ŏ��̓^�C�g��
	GameMode = mode::INPUTNAME;

	//���Ȃ���΃��[�v
	while (ProcessMessage() == 0)
	{

		//�L�[���͎擾 
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);    //��̃R���g���[���[�̓��͂��g���܂�
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();                 //��ʂ�������

		switch (GameMode)
		{
		case mode::TITLE:

			//�^�C�g��
			DrawGameTitle(g_KeyFlg, GameMode);

			break;

		case mode::INIT:

			//������
			GameInit();

			break;

		case mode::MAIN:

			//�Q�[�����C��
			GameMain();

			break;

		case mode::RANKING:

			//�����L���O�\��
			DrawRanking(g_KeyFlg, GameMode);

			break;

		case mode::HELP:

			//�w���v�\��
			DrawHelp(g_KeyFlg, GameMode);

			break;

		case mode::INPUTNAME:

			//���O����
			InputRanking(g_KeyFlg, GameMode,g_Score);

			break;

		case mode::RESULT:

			//���U���g
			DrawResult(g_KeyFlg, GameMode);

			break;

		case mode::END:

			//�G���h
			break;

		case mode::CLOSE:

			//����[��
			break;

		default:
			break;
		}

		DxLib::ScreenFlip();                      //����ʂ�\��ʂɔ��f
	}

	DxLib_End();				           // �c�w���C�u�����g�p�̏I������

	return 0;				               // �\�t�g�̏I�� 
}

//������
void GameInit()
{
	//���낢�돉����

	//�Q�[�����C����
	GameMode = mode::MAIN;
}

//�Q�[�����C��
void GameMain()
{

}

//�摜�ǂݍ���
int LoadImages()
{
	if (LoadHelpImage() == -1) return -1;     //�w���v�摜�ǂݍ���
	if (LoadRankingImage() == -1) return -1;  //�����L���O�摜�ǂݍ���
	if (LoadResultImage() == -1) return -1;   //���U���g�摜�ǂݍ���
	if (LoadTitleImage() == -1) return -1;    //�^�C�g���摜�ǂݍ���

	return 0;
}

//�����ǂݍ���
int LoadSounds()
{
	return 0;
}