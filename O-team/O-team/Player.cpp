#include "Player.h"
#include "PadInput.h"

#define MAP_X 1280      //�s���\�͈̔�(��)
#define MAP_Y 720       //�s���\�͈̔�(����)

Player::Player() {
	Direction = 0;  //�ŏ��͉E����

	HP = 10;
	X = 620.f;
	Y = 340.f;
	Width = 64.f;
	Hight = 65.f;
	Speed = 5.f;
}

Player::~Player() {

}

void Player::LoadImages(){
	//�����ǂݍ���
	LoadDivGraph("images/MikoSan02.png", 8, 4, 2, 64, 65, All_Images);

	//�I�[��
	LoadDivGraph("images/aura2.png", 14, 7, 2, 70, 70, All_Aura);
}

void Player::SetHP(int HP) {
	this->HP += HP;
}

void Player::Update() {
	InitPad();

	float Vector = 0.71;

	if (JoyPadX >= MARGIN) {
		if (JoyPadY < MARGIN && JoyPadY > -MARGIN) X += Speed;
		else X += Speed * Vector;

		Direction = 0;   //�E
	}
	if (JoyPadX <= -MARGIN) {
		if (JoyPadY < MARGIN && JoyPadY > -MARGIN) X -= Speed;
		else X -= Speed * Vector;

		Direction = 1;   //��
	}
	if (JoyPadY <= -MARGIN) {
		if (JoyPadX < MARGIN && JoyPadX > -MARGIN) Y += Speed;
		else Y += Speed * Vector;
	}
	if (JoyPadY >= MARGIN) {
		if (JoyPadX < MARGIN && JoyPadX > -MARGIN) Y -= Speed;
		else Y -= Speed * Vector;
	}

	//��ʊO�ɏo�Ȃ��悤��
	if (X < 0) {
		X = 0;             //��
	}
	if (Y < 0) {
		Y = 0;             //��
	}
	if (MAP_X < X + Width) {
		X = MAP_X - Width;  //�E
	}
	if (MAP_Y < Y + Hight) {
		Y = MAP_Y - Hight;   //��
	}
}

void Player::Draw() {
	int now = 0;        //���݂̉摜No.
	int now_aura = 0;   //���݂̉摜No.(�I�[��)

	if (HP < 100) now = 0;                    //1���ځ@�i�f�t�H���g�j
	else if (HP >= 100 && HP < 200) now = 1;  //2����
	else if (HP >= 200 && HP < 300) now = 2;  //3����
	else if (HP >= 300 && HP < 400) now = 3;  //4����
	else now = 3;                             //4���ڈȍ~�͕ς��Ȃ�

	//�����ɂ���ĉ摜��ς���
	now = now + (Direction * 4);
	
	//�I�[��
	if (HP >= 400){
		if (HP < 400) now_aura = 0;                    //1���ځ@�i�f�t�H���g�j
		else if (HP >= 400 && HP < 500) now_aura = 1;  //2����
		else if (HP >= 500 && HP < 600) now_aura = 2;  //3����
		else if (HP >= 600 && HP < 700) now_aura = 3;  //4����
		else if (HP >= 700 && HP < 800) now_aura = 4;  //5����
		else if (HP >= 800 && HP < 900) now_aura = 5;  //6����
		else if (HP >= 900 && HP < 1000) now_aura = 6; //7����
		else now_aura = 6;                             //7���ڈȍ~�͕ς��Ȃ�

		now_aura = now_aura + (Direction * 7);         //�����ɂ���ĉ摜��ς���(�I�[����)

		//�I�[���̕`��
		DrawRotaGraph(X + (Width / 2), Y + (Width / 2), 1, 0, All_Aura[now_aura], TRUE);
	}
	//�v���C���[
	DrawRotaGraph(X + (Width / 2), Y + (Width / 2), 1, 0, All_Images[now], TRUE);

	DrawFormatString(0, 50, 0xffffff, "HP = %d", HP);
}

void Player::InitPad() {
	//�X�e�B�b�N
	JoyPadX = PAD_INPUT::GetPadThumbLX();
	JoyPadY = PAD_INPUT::GetPadThumbLY();
}

bool Player::Hit(Flying_Armor* armor) {
	int X1, Y1;
	int X2, Y2;

	X1 = X; Y1 = Y;
	X2 = X + Width; Y2 = Y + Hight;

	int BX1, BY1;
	int BX2, BY2;

	BX1 = armor->GetX(); BY1 = armor->GetY();
	BX2 = armor->GetX()+ armor->GetW();
	BY2 = armor->GetY() + armor->GetH();

	//�v���C���[�Ƃ̓����蔻��
	if ((X1 <= BX2 && BX1 <= X2 && Y1 <= BY2 && BY1 <= Y2)) {
		return true;
	}
	return false;
}

bool Player::Hit(Flying_Attack* attack) {
	int X1, Y1;
	int X2, Y2;

	X1 = X; Y1 = Y;
	X2 = X + Width; Y2 = Y + Hight;

	int AX1, AY1;
	int AX2, AY2;

	AX1 = attack->GetX(); AY1 = attack->GetY();
	AX2 = attack->GetX() + attack->GetW();
	AY2 = attack->GetY() + attack->GetH();

	//�v���C���[�Ƃ̓����蔻��
	if ((X1 <= AX2 && AX1 <= X2 && Y1 <= AY2 && AY1 <= Y2)) {
		return true;
	}
	return false;
}