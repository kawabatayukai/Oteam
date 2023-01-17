#include"DxLib.h"
#include"flying_Armor.h"
#include"flying_Attack.h"
#include"flying_object.h"

#pragma once
class Player{
private:
	int Image;
	int HP;                  //体力
	float X, Y;              //X,Y座標
	float Width;             //プレイヤーの幅
	float Hight;             //プレイヤーの高さ
	float Speed;             //移動速度
	int JoyPadX, JoyPadY;    //パッド入力値

public:
	Player();
	virtual~Player();

	void SetHP(int HP);
	void Update();
	void InitPad();
	void Draw();
	int GetX() { return (int)X; }
	int GetY() { return (int)Y; }

	bool Hit(Flying_Armor* armor);
	bool Hit(Flying_Attack* attack);
};