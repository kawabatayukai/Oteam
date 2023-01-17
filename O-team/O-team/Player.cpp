#include "Player.h"
#include "PadInput.h"

Player::Player() {
	X = 620.f;
	Y = 340.f;
	Width = 50.f;
	Hight = 50.f;
	Speed = 5.f;
	MoveFlag = 0;
}

Player::~Player() {

}

void Player::Update() {
	InitPad();

	float Vector = 0.71;

	if (JoyPadX >= MARGIN) {
		if (JoyPadY < MARGIN && JoyPadY > -MARGIN) X += Speed;
		else X += Speed * Vector;
	}
	if (JoyPadX <= -MARGIN) {
		if (JoyPadY < MARGIN && JoyPadY > -MARGIN) X -= Speed;
		else X -= Speed * Vector;
	}
	if (JoyPadY <= -MARGIN) {
		if (JoyPadX < MARGIN && JoyPadX > -MARGIN) Y += Speed;
		else Y += Speed * Vector;
	}
	if (JoyPadY >= MARGIN) {
		if (JoyPadX < MARGIN && JoyPadX > -MARGIN) Y -= Speed;
		else Y -= Speed * Vector;
	}
}

void Player::Draw() {
	DrawBox(X, Y, X + Width, Y + Hight, 0xffffff, TRUE);
}

void Player::InitPad() {
	//スティック
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

	//プレイヤーの右端
	if (BX1 < X2 
		&& Y1 < BY1 && BY1 < Y2
		|| Y1 < BY2 && BY2 < Y2) {
		return true;
	}
	return false;
}

bool Player::Hit(Flying_Attack attack) {
	int X1, Y1;
	int X2, Y2;

	X1 = X; Y1 = Y;
	X2 = X + Width; Y2 = Y + Hight;

	return false;
}