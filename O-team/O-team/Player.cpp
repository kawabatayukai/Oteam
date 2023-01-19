#include "Player.h"
#include "PadInput.h"

#define MAP_X 980       //�s���\�͈̔�(��)
#define MAP_Y 720       //�s���\�͈̔�(����)

Player::Player() {
	Direction = 0;  //�ŏ��͉E����

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
	//�����ǂݍ���
	LoadDivGraph("images/GameMain/MikoSan02.png", 8, 4, 2, 64, 65, All_Images);

	//�I�[��
	LoadDivGraph("images/GameMain/aura2.png", 14, 7, 2, 70, 70, All_Aura);

	//���S��
	LoadDivGraph("images/GameMain/Mikosan_Death3.png", 4, 2, 2, 60, 55, Death_Image);

	//�U����ς���
	LoadDivGraph("images/GameMain/Mikosan_Win.png", 8, 4, 2, 64, 65, Win_Image);
}

int Player::LoadSounds() {
	if ((RankUpSE = LoadSoundMem("sounds/se/RankUp.wav")) == -1) return -1;
}

void Player::SetHP(int HP) 
{
	this->HP += HP;
	if (this->HP < 0) this->HP = 0;  //0��菬�����Ȃ�Ȃ�
}

void Player::Update() {
	InitPad();
	RankUp();

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
	if (HP < 300) now = 0;                    //1���ځ@�i�f�t�H���g�j
	else if (HP >= 300 && HP < 600) now = 1;  //2����
	else if (HP >= 600 && HP < 900) now = 2;  //3����
	else if (HP >= 900 && HP < 1200) now = 3; //4����
	else now = 3;                             //4���ڈȍ~�͕ς��Ȃ�

	//�����ɂ���ĉ摜��ς���
	now = now + (Direction * 4);

	//�I�[��
	if (HP >= 1200){
		if (HP < 1200) now_aura = 0;                     //1���ځ@�i�f�t�H���g�j
		else if (HP >= 1200 && HP < 1500) now_aura = 1;  //2����
		else if (HP >= 1500 && HP < 1800) now_aura = 2;  //3����
		else if (HP >= 1800 && HP < 2100) now_aura = 3;  //4����
		else if (HP >= 2100 && HP < 2400) now_aura = 4;  //5����
		else if (HP >= 2400 && HP < 2700) now_aura = 5;  //6����
		else if (HP >= 2700 && HP < 3000) now_aura = 6;  //7����
		else now_aura = 6;                               //7���ڈȍ~�͕ς��Ȃ�

		now_aura = now_aura + (Direction * 7);           //�����ɂ���ĉ摜��ς���(�I�[����)

		//�I�[���̕`��
		DrawRotaGraph(X + (Width / 2), Y + (Width / 2), 1, 0, All_Aura[now_aura], TRUE);
	}
	//�v���C���[
	DrawRotaGraph(X + (Width / 2), Y + (Width / 2), 1, 0, All_Images[now], TRUE);

	//DrawFormatString(0, 50, 0xffffff, "HP = %d", HP);
}

//���S���̕`��
void Player::Draw_Death() {

	//�����@����

	static int frame;
	frame++;
	static int now = 0;
	if (frame % 60 == 0 && now == 0) now++;

	//���E
	//now = now + (Direction * 1);

	DrawRotaGraph(X + (Width / 2), Y + (Width / 2), 1, 0, Death_Image[now + (Direction * 2)], TRUE);
}

//�ς����Ƃ��̕`��
void Player::Draw_Win()
{
	if (HP < 100) now = 0;                    //1���ځ@�i�f�t�H���g�j
	else if (HP >= 100 && HP < 200) now = 1;  //2����
	else if (HP >= 200 && HP < 300) now = 2;  //3����
	else if (HP >= 300 && HP < 400) now = 3;  //4����
	else now = 3;                             //4���ڈȍ~�͕ς��Ȃ�

	//�����ɂ���ĉ摜��ς���
	now = now + (Direction * 4);


	DrawRotaGraph(X + (Width / 2), Y + (Width / 2), 1, 0, Win_Image[now], TRUE);
}

#define Gravity 1.0f      //�d��
//�ς����Ƃ����˂�
void Player::Update_Win()
{
	//�W�����v
	if (Y == win_pointY)
	{
		old_y = Y;
		g_add = -17.5f;    //�d�͉����x���}�C�i�X�l��
	}

	y_add = (Y - old_y) + g_add;  //����̗���������
	old_y = Y;                    //1�t���[���O�̂����W
	Y += y_add;                   //���������������W�ɉ��Z����
	g_add = Gravity;              //�d�͉����x������������

	if (Y > win_pointY) Y = win_pointY;

}

//�E�G���A���ɕ`�悷��
void Player::Draw_Right(int x, int y)
{
	double rate = 2.3;   //�g�嗦

	//�I�[��
	if (HP >= 1200) 
	{
		//�I�[���̕`��                                     ���E�̌����͍l�����Ȃ�
		DrawRotaGraph(x, y, rate, 0, All_Aura[now_aura - (Direction * 7)], TRUE);
	}

	//�v���C���[�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@���E�̌����͍l�����Ȃ�
	DrawRotaGraph(x, y, rate, 0, All_Images[now - (Direction * 4)], TRUE);
}

//�ς������̍��W��ێ�����
void Player::SetWin_PointY()
{
	win_pointY = Y;
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