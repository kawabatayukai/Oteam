#include"DxLib.h"
#include"flying_Armor.h"
#include"flying_Attack.h"
#include"flying_object.h"

#pragma once
class Player{
private:
	bool Rank = true;                 //�`��1
	bool Rank2 = true;                //�`��2
	bool Rank3 = true;                //�`��3
	bool Rank4 = true;                //�`��4
	bool Rank5 = true;                //�`��5
	bool Rank6 = true;                //�`��6
	bool Rank7 = true;                //�`��7
	bool Rank8 = true;                //�`��8
	bool Rank9 = true;                //�`��9
	int RankUpSE;            //�i����������SE
	int All_Images[8];       //�v���C���[�̉摜�i4�i�K�j
	int All_Aura[14];        //�I�[��
	int Direction;           //�����@0:�E�@1:��
	int Death_Image[4];      //���S���̉摜
	int Win_Image[8];        //�U����ς������̉摜

	int now = 0;        //���݂̉摜No.
	int now_aura = 0;   //���݂̉摜No.(�I�[��)
	int win_pointY = 0; //�ς�������Y���W��ێ�
	
	//�W�����v�Ɏg�p
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x
	float old_y = 0;          //�O��̈ʒuY

	int HP;                  //�̗�
	float X, Y;              //X,Y���W
	float Width;             //�v���C���[�̕�
	float Hight;             //�v���C���[�̍���
	float Speed;             //�ړ����x
	int JoyPadX, JoyPadY;    //�p�b�h���͒l

public:
	Player();
	virtual~Player();
	void LoadImages();
	int LoadSounds();

	void RankUp();
	void SetHP(int HP);
	int GetHP() { return HP; }
	void Update();
	void InitPad();
	void Draw();
	void Draw_Death();    //���S���̕`��
	void Draw_Win();      //�ς����Ƃ��̕`��
	void Update_Win();    //�ς����Ƃ����˂�
	void Draw_Right(int x, int y);    //�E�G���A���ɕ`�悷��
	void SetWin_PointY(); //�ς������̍��W��ێ�����

	int GetX() { return (int)X; }
	int GetY() { return (int)Y; }

	bool Hit(Flying_Armor* armor);
	bool Hit(Flying_Attack* attack);
};