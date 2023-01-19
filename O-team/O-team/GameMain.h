#pragma once

// �X�V�E�v�Z(Update) �� �`��(Draw)  �̏����𕪂���Ɨǂ��ł�

int LoadGameMainImages();//�Q�[�����C���摜�ǂݍ���
int LoadGameMainSounds();//�Q�[�����C���摜�ǂݍ���
void GameMain_Init();    //�Q�[�����C�����������i�R���X�g���N�^�̑���j
void GameMain_Final();   //�Q�[�����C���I�������i�f�X�g���N�^�̑���j

void Armor_Update();     //�h��  �����E�X�V�E�폜
void Attack_Update();    //�U��  �����E�X�V�E�폜

void GameMain_Update();    //�Q�[�����C���X�V�E�v�Z
void GameMain_Draw();      //�Q�[�����C���`��
void GameMain_DrawArea();  //�Q�[�����C���`��G���A

void GameMain(int& gamemode, int lowscore, int &g_score);         //�Q�[�����C��  �����L���O5�Ԗڂ̃X�R�A�E�X�R�A��ێ�����ϐ������炤

//�^�[��
enum class Turn
{
	CATCH,     //�h����Ƃ�^�[��
	ATTACK,    //�U���ɑς���^�[��
	END,       //30�b���Ԑ؂� or �v���C���[�����S������
};