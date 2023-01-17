#include"DxLib.h"
#include"Ranking.h"
#define RANKING_DATA 5    // �����L���O��ʂT�l 

//Ranking.h�Ő錾�����֐��̒�`�������ɏ����܂�
int g_RankingImg;   // �����L���O�摜
struct RankingData g_Ranking[RANKING_DATA];    // �����L���O�f�[�^�̕ϐ��錾
int g_Score;  // �X�R�A

//�����L���O�`��
void DrawRanking(int key, int& gamemode)
{
	//�L�[���͂�"key",GameMode��ς������Ƃ���"gamemode"��ύX���܂�
	// �X�y�[�X�L�[�Ń��j���[�ɖ߂�
	if (key & PAD_INPUT_B) gamemode = 0;

	// �����L���O�摜�\��
	DrawGraph(0, 0, g_RankingImg, FALSE);

	// �����L���O�ꗗ��\��
	SetFontSize(18);
	for (int i = 0; i < RANKING_DATA; i++)
	{
		DrawFormatString(30, 170 + i * 25, 0xffffff, "%2d  %-10s  %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	DrawString(120, 437, "--- �X�y�[�X�L�[�������ă^�C�g���֖߂� ---", 0xffffff, 0);
}

//�����L���O����
void InputRanking(int key, int& gamemode)
{
	//�L�[���͂�"key",GameMode��ς������Ƃ���"gamemode"��ύX���܂�
	// �����L���O�摜�\��
	DrawGraph(0, 0, g_RankingImg, FALSE);

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(20);

	// ���O���͎w��������̕`��
	DrawString(150, 240, "�����L���O�ɓo�^���܂�", 0xFFFFFF);
	DrawString(150, 270, "���O���p���œ��͂��Ă�������", 0xFFFFFF);

	// ���O�̓���
	DrawString(150, 310, "> ", 0xFFFFFF);
	DrawBox(160, 305, 300, 335, 0x000055, TRUE);
	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[RANKING_DATA - 1].name, FALSE) == 1)
	{
		g_Ranking[RANKING_DATA - 1].score = g_Score; // �����L���O�f�[�^�ɃX�R�A��o�^
		SortRanking();                               // �����L���O���בւ�
		SaveRanking();                               // �����L���O�f�[�^�̕ۑ�
		gamemode = 3;                                // �Q�[�����[�h�̕ύX
	}
}

/******************************************
 * �����L���O���בւ�
 ******************************************/
void SortRanking(void)
{
	int i, j;
	RankingData work;

	// �I��@�\�[�g
	for (i = 0; i < RANKING_DATA - 1; i++)
	{
		for (j = i + 1; j < RANKING_DATA; j++)
		{
			if (g_Ranking[i].score <= g_Ranking[j].score)
			{
				work = g_Ranking[i];
				g_Ranking[i] = g_Ranking[j];
				g_Ranking[j] = work;
			}
		}
	}
	// ���ʕt��
	for (i = 0; i < RANKING_DATA; i++)
	{
		g_Ranking[i].no = 1;
	}
	// ���_�������ꍇ�́A�������ʂƂ���
	// �����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���
	for (i = 0; i < RANKING_DATA - 1; i++)
	{
		for (j = i + 1; j < RANKING_DATA; j++)
		{
			if (g_Ranking[i].score > g_Ranking[j].score)
			{
				g_Ranking[j].no++;
			}
		}
	}
}

/***********************************************
 * �����L���O�f�[�^�̕ۑ�
 ***********************************************/
int  SaveRanking(void)
{
	FILE* fp;
#pragma warning(disable:4996)

	// �t�@�C���I�[�v��
	if ((fp = fopen("dat/rankingdata.txt", "w")) == NULL)
	{
		/* �G���[���� */
		printf("Ranking Data Error\n");
		return -1;
	}

	// �����L���O�f�[�^���z��f�[�^����������
	for (int i = 0; i < RANKING_DATA; i++)
	{
		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	return 0;

}

/*************************************
 * �����L���O�f�[�^�ǂݍ���
 *************************************/
int ReadRanking(void)
{
	FILE* fp;
#pragma warning(disable:4996)

	// �t�@�C���I�[�v��
	if ((fp = fopen("dat/rankingdata.txt", "r")) == NULL)
	{
		// �G���[����
		printf("Ranking Data Error\n");
		return -1;
	}

	// �����L���O�f�[�^�z����f�[�^��ǂݍ���
	for (int i = 0; i < RANKING_DATA; i++)
	{
		int dammy = fscanf(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	return 0;
}

//�����L���O�摜�ǂݍ���
int LoadRankingImage()
{
	// �����L���O�摜�Ǎ�
	if ((g_RankingImg = LoadGraph("images/help.png")) == -1) return -1;
	return 0;
}