#include"DxLib.h"
#include"flying_Armor.h"
#include"flying_Attack.h"
#include"flying_object.h"

#pragma once
class Player{
private:
	bool Rank = true;                 //形態1
	bool Rank2 = true;                //形態2
	bool Rank3 = true;                //形態3
	bool Rank4 = true;                //形態4
	bool Rank5 = true;                //形態5
	bool Rank6 = true;                //形態6
	bool Rank7 = true;                //形態7
	bool Rank8 = true;                //形態8
	bool Rank9 = true;                //形態9
	int RankUpSE;            //進化した時のSE
	int All_Images[8];       //プレイヤーの画像（4段階）
	int All_Aura[14];        //オーラ
	int Direction;           //方向　0:右　1:左
	int Death_Image[4];      //死亡時の画像
	int Win_Image[8];        //攻撃を耐えた時の画像

	int now = 0;        //現在の画像No.
	int now_aura = 0;   //現在の画像No.(オーラ)
	int win_pointY = 0; //耐えた時のY座標を保持
	
	//ジャンプに使用
	float y_add = 0;          //落下距離
	float g_add = 1.0f;       //重力加速度
	float old_y = 0;          //前回の位置Y

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
	int LoadSounds();

	void RankUp();
	void SetHP(int HP);
	int GetHP() { return HP; }
	void Update();
	void InitPad();
	void Draw();
	void Draw_Death();    //死亡時の描画
	void Draw_Win();      //耐えたときの描画
	void Update_Win();    //耐えたとき跳ねる
	void Draw_Right(int x, int y);    //右エリア内に描画する
	void SetWin_PointY(); //耐えた時の座標を保持する

	int GetX() { return (int)X; }
	int GetY() { return (int)Y; }

	bool Hit(Flying_Armor* armor);
	bool Hit(Flying_Attack* attack);
};