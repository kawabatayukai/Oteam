#pragma once

//�����L���O��ʂ݂̂Ŏg���ϐ��E�֐��̐錾�������ɏ����܂�

//�摜�ϐ���share.h�ɏ����Ă�������


#define RANKING_DATA 5    // �����L���O��ʂT�l 


struct RankingData                            // �����L���O�f�[�^�\����
{
	int  no;
	char name[11];
	long score;
};
extern RankingData g_Ranking[RANKING_DATA];    // �����L���O�f�[�^�̕ϐ��錾 ()

void DrawRanking(int key, int& gamemode);                    //�����L���O�`��  "KeyFlg"  �́@�������u��
void InputRanking(int nowkey, int& gamemode, int score);     //�����L���O����  "NowKey"�@�́@�����Ă���ԁ@�޽

void SortRanking(void);  // �����L���O�̕��בւ�
int SaveRanking(void);   // �����L���O�f�[�^�̕ۑ�
int ReadRanking(void);   // �����L���O�f�[�^�̓Ǎ�

int LoadRankingImage();                        //�����L���O�摜�ǂݍ���
int LoadRankingSounds();                       //�����L���O�T�E���h�ǂݍ���


