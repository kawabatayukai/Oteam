#include "Player.h"
#include "PadInput.h"

#define MAP_X 980       //行動可能の範囲(幅)
#define MAP_Y 720       //行動可能の範囲(高さ)

Player::Player() {
	Direction = 0;  //最初は右向き

	HP = 10;
	Width = 50.f;
	Hight = 55.f;
	X = MAP_X / 2 - Width;
	Y = MAP_Y / 2 - Hight;

	Speed = 6.5f;

	LoadSounds();
}

Player::~Player() {

}

void Player::LoadImages(){
	//分割読み込み
	LoadDivGraph("images/GameMain/MikoSan02.png", 8, 4, 2, 64, 65, All_Images);

	//オーラ
	LoadDivGraph("images/GameMain/aura2.png", 14, 7, 2, 70, 70, All_Aura);

	//死亡時
	LoadDivGraph("images/GameMain/Mikosan_Death3.png", 4, 2, 2, 60, 55, Death_Image);

	//攻撃を耐えた
	LoadDivGraph("images/GameMain/Mikosan_Win.png", 8, 4, 2, 64, 65, Win_Image);
}

int Player::LoadSounds() {
	if ((RankUpSE = LoadSoundMem("sounds/se/RankUp.wav")) == -1) return -1;
}

void Player::SetHP(int HP) 
{
	this->HP += HP;
	if (this->HP < 0) this->HP = 0;  //0より小さくならない
}

void Player::Update() {
	InitPad();
	RankUp();

	float Vector = 0.71;

	if (JoyPadX >= MARGIN) {
		if (JoyPadY < MARGIN && JoyPadY > -MARGIN) X += Speed;
		else X += Speed * Vector;

		Direction = 0;   //右
	}
	if (JoyPadX <= -MARGIN) {
		if (JoyPadY < MARGIN && JoyPadY > -MARGIN) X -= Speed;
		else X -= Speed * Vector;

		Direction = 1;   //左
	}
	if (JoyPadY <= -MARGIN) {
		if (JoyPadX < MARGIN && JoyPadX > -MARGIN) Y += Speed;
		else Y += Speed * Vector;
	}
	if (JoyPadY >= MARGIN) {
		if (JoyPadX < MARGIN && JoyPadX > -MARGIN) Y -= Speed;
		else Y -= Speed * Vector;
	}

	//画面外に出ないように
	if (X < 0) {
		X = 0;             //左
	}
	if (Y < 0) {
		Y = 0;             //上
	}
	if (MAP_X < X + Width) {
		X = MAP_X - Width;  //右
	}
	if (MAP_Y < Y + Hight) {
		Y = MAP_Y - Hight;   //下
	}
}

void Player::RankUp() {
	if (HP >= 300 && HP < 600) {
		if (Rank) {
			PlaySoundMem(RankUpSE, DX_PLAYTYPE_BACK);
			Rank = false;
		}
	}
	if (HP >= 600 && HP < 900) {
		if (Rank2) {
			PlaySoundMem(RankUpSE, DX_PLAYTYPE_BACK);
			Rank2 = false;
		}
	}
	if (HP >= 900 && HP < 1200) {
		if (Rank3) {
			PlaySoundMem(RankUpSE, DX_PLAYTYPE_BACK);
			Rank3 = false;
		}
	}
	if (HP >= 1200 && HP < 1500) {
		if (Rank4) {
			PlaySoundMem(RankUpSE, DX_PLAYTYPE_BACK);
			Rank4 = false;
		}
	}
	if (HP >= 1500 && HP < 1800) {
		if (Rank5) {
			PlaySoundMem(RankUpSE, DX_PLAYTYPE_BACK);
			Rank5 = false;
		}
	}
	if (HP >= 1800 && HP < 2100) {
		if (Rank6) {
			PlaySoundMem(RankUpSE, DX_PLAYTYPE_BACK);
			Rank6 = false;
		}
	}
	if (HP >= 2100 && HP < 2400) {
		if (Rank7) {
			PlaySoundMem(RankUpSE, DX_PLAYTYPE_BACK);
			Rank7 = false;
		}
	}
	if (HP >= 2400 && HP < 2700) {
		if (Rank8) {
			PlaySoundMem(RankUpSE, DX_PLAYTYPE_BACK);
			Rank8 = false;
		}
	}
	if (HP >= 2700 && HP < 3000) {
		if (Rank9) {
			PlaySoundMem(RankUpSE, DX_PLAYTYPE_BACK);
			Rank9 = false;
		}
	}
}

void Player::Draw() {
	if (HP < 300) now = 0;                    //1枚目　（デフォルト）
	else if (HP >= 300 && HP < 600) now = 1;  //2枚目
	else if (HP >= 600 && HP < 900) now = 2;  //3枚目
	else if (HP >= 900 && HP < 1200) now = 3; //4枚目
	else now = 3;                             //4枚目以降は変わらない

	//向きによって画像を変える
	now = now + (Direction * 4);

	//オーラ
	if (HP >= 1200){
		if (HP < 1200) now_aura = 0;                     //1枚目　（デフォルト）
		else if (HP >= 1200 && HP < 1500) now_aura = 1;  //2枚目
		else if (HP >= 1500 && HP < 1800) now_aura = 2;  //3枚目
		else if (HP >= 1800 && HP < 2100) now_aura = 3;  //4枚目
		else if (HP >= 2100 && HP < 2400) now_aura = 4;  //5枚目
		else if (HP >= 2400 && HP < 2700) now_aura = 5;  //6枚目
		else if (HP >= 2700 && HP < 3000) now_aura = 6;  //7枚目
		else now_aura = 6;                               //7枚目以降は変わらない

		now_aura = now_aura + (Direction * 7);           //向きによって画像を変える(オーラも)

		//オーラの描画
		DrawRotaGraph(X + (Width / 2), Y + (Width / 2), 1, 0, All_Aura[now_aura], TRUE);
	}
	//プレイヤー
	DrawRotaGraph(X + (Width / 2), Y + (Width / 2), 1, 0, All_Images[now], TRUE);

	//DrawFormatString(0, 50, 0xffffff, "HP = %d", HP);
}

//死亡時の描画
void Player::Draw_Death() {

	//ﾊﾟﾀｯ　ﾊﾞﾀﾝ

	static int frame;
	frame++;
	static int now = 0;
	if (frame % 60 == 0 && now == 0) now++;

	//左右
	//now = now + (Direction * 1);

	DrawRotaGraph(X + (Width / 2), Y + (Width / 2), 1, 0, Death_Image[now + (Direction * 2)], TRUE);
}

//耐えたときの描画
void Player::Draw_Win()
{
	if (HP < 100) now = 0;                    //1枚目　（デフォルト）
	else if (HP >= 100 && HP < 200) now = 1;  //2枚目
	else if (HP >= 200 && HP < 300) now = 2;  //3枚目
	else if (HP >= 300 && HP < 400) now = 3;  //4枚目
	else now = 3;                             //4枚目以降は変わらない

	//向きによって画像を変える
	now = now + (Direction * 4);


	DrawRotaGraph(X + (Width / 2), Y + (Width / 2), 1, 0, Win_Image[now], TRUE);
}

#define Gravity 1.0f      //重力
//耐えたとき跳ねる
void Player::Update_Win()
{
	//ジャンプ
	if (Y == win_pointY)
	{
		old_y = Y;
		g_add = -17.5f;    //重力加速度をマイナス値に
	}

	y_add = (Y - old_y) + g_add;  //今回の落下距離を
	old_y = Y;                    //1フレーム前のｙ座標
	Y += y_add;                   //落下距離をｙ座標に加算する
	g_add = Gravity;              //重力加速度を初期化する

	if (Y > win_pointY) Y = win_pointY;

}

//右エリア内に描画する
void Player::Draw_Right(int x, int y)
{
	double rate = 2.3;   //拡大率

	//オーラ
	if (HP >= 1200) 
	{
		//オーラの描画                                     左右の向きは考慮しない
		DrawRotaGraph(x, y, rate, 0, All_Aura[now_aura - (Direction * 7)], TRUE);
	}

	//プレイヤー　　　　　　　　　　　　　　　左右の向きは考慮しない
	DrawRotaGraph(x, y, rate, 0, All_Images[now - (Direction * 4)], TRUE);
}

//耐えた時の座標を保持する
void Player::SetWin_PointY()
{
	win_pointY = Y;
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

	//プレイヤーとの当たり判定
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

	//プレイヤーとの当たり判定
	if ((X1 <= AX2 && AX1 <= X2 && Y1 <= AY2 && AY1 <= Y2)) {
		return true;
	}
	return false;
}