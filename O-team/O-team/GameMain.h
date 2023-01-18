#pragma once

// �X�V�E�v�Z(Update) �� �`��(Draw)  �̏����𕪂���Ɨǂ��ł�

void GameMain_Init();    //�Q�[�����C�����������i�R���X�g���N�^�̑���j
void GameMain_Final();   //�Q�[�����C���I�������i�f�X�g���N�^�̑���j

void Armor_Update();     //�h��  �����E�X�V�E�폜
void Attack_Update();    //�U��  �����E�X�V�E�폜

void GameMain_Update();  //�Q�[�����C���X�V�E�v�Z
void GameMain_Draw();    //�Q�[�����C���`��

void GameMain(int &gamemode);         //�Q�[�����C��

//�^�[��
enum class Turn
{
	CATCH,     //�h����Ƃ�^�[��
	ATTACK,    //�U���ɑς���^�[��
	END,       //30�b���Ԑ؂� or �v���C���[�����S������
};