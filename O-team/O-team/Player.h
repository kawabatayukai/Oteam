#include"DxLib.h"
#include"flying_Armor.h"
#include"flying_Attack.h"
#include"flying_object.h"

#pragma once
class Player{
private:
	int All_Images[8];       //プレイヤーの画像（4段階）
	int All_Aura[14];        //オーラ
	int Direction;           //方向　0:右　1:左
	int Death_Image[4];         //死亡時の画像
	
	int HP;                  //体力
	float X, Y;              //X,Y座標
	float Width;             //プレイヤーの幅
	float Hight;             //プレイヤーの高さ
	float Speed;             //移動速度
	int JoyPadX, JoyPadY;    //パッド入力値

public:
	Player();
	virtual~Player();
	void LoadImages();

	void SetHP(int HP);
	int GetHP() { return HP; }
	void Update();
	void InitPad();
	void Draw();
	void Draw_Death();    //死亡時の描画
	int GetX() { return (int)X; }
	int GetY() { return (int)Y; }

	bool Hit(Flying_Armor* armor);
	bool Hit(Flying_Attack* attack);
};