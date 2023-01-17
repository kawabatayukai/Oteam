#include"DxLib.h"

#pragma once
class Player{
private:
	int JoyPadX, JoyPadY;    //パッド入力値
	float X, Y;              //X,Y座標
	float Width;             //プレイヤーの幅
	float Speed;             //移動速度
	int MoveFlag;

public:
	Player();
	virtual~Player();

	void Update();

	void InitPad();
	void Draw();

	int GetX() { return (int)X; }
	int GetY() { return (int)Y; }
};