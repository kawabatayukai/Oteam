#include"DxLib.h"
#include"flying_Armor.h"
#include"flying_Attack.h"
#include"flying_object.h"

#pragma once
class Player{
private:
	int All_Images[8];       //�v���C���[�̉摜�i4�i�K�j
	int All_Aura[14];        //�I�[��
	int Direction;           //�����@0:�E�@1:��
	int Death_Image[4];         //���S���̉摜
	
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

	void SetHP(int HP);
	int GetHP() { return HP; }
	void Update();
	void InitPad();
	void Draw();
	void Draw_Death();    //���S���̕`��
	int GetX() { return (int)X; }
	int GetY() { return (int)Y; }

	bool Hit(Flying_Armor* armor);
	bool Hit(Flying_Attack* attack);
};