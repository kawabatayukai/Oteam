#include "Player.h"
#include "PadInput.h"

Player::Player() {
	X = 620.f;
	Y = 340.f;
	Width = 50.f;
	Speed = 3.f;
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
	DrawBox(X, Y, X + Width, Y + Width, 0xffffff, TRUE);
}

void Player::InitPad() {
	//スティック
	JoyPadX = PAD_INPUT::GetPadThumbLX();
	JoyPadY = PAD_INPUT::GetPadThumbLY();
}