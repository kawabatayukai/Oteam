#pragma once

//�����L���O��ʂ݂̂Ŏg���ϐ��E�֐��̐錾�������ɏ����܂�

//�摜�ϐ���share.h�ɏ����Ă�������

struct RankingData                            // �����L���O�f�[�^�\����
{
	int  no;
	char name[11];
	long score;
};

void DrawRanking(int key, int& gamemode);      //�����L���O�`��
void InputRanking(int key, int& gamemode, int score);     //�����L���O����

void SortRanking(void);  // �����L���O�̕��בւ�
int SaveRanking(void);   // �����L���O�f�[�^�̕ۑ�
int ReadRanking(void);   // �����L���O�f�[�^�̓Ǎ�

int LoadRankingImage();                        //�����L���O�摜�ǂݍ���


