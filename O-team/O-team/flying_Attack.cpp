#include"DxLib.h"
#include "flying_Attack.h"

//テスト用 color
int colors[3] = { 0x00ffff,0x00ff00,0xff00ff };

//サイズ　
struct Attack_Size
{
	int w;    //幅
	int h;    //高さ
};

Attack_Size at_size[3] =
{
	{100,25},   //槍
	{70,70},    //鉄
	{44,44},    //ポーション
};

//at_size[static_cast<int>(myType)].x

//コンストラクタ
Flying_Attack::Flying_Attack(int type, int x, int y, int speed)
	:my_Type(type), Flying_object(x, y, at_size[type].w, at_size[type].h, speed)     //基底クラスのコンストラクタ呼び出し
{
	//コンストラクタで値を渡さないとデフォルト引数で画面右端より飛んできます

	//画像読み込み    槍・鉄球・毒　で大きさが違うので許してください
	switch (my_Type)
	{
	case Attack_Type::SPEAR:

		image = LoadGraph("images/spear.png");
		break;

	case Attack_Type::IRON:

		image = LoadGraph("images/iron.png");
		break;

	case Attack_Type::POISON:

		image = LoadGraph("images/poison.png");
		break;

	default:
		break;
	}
}

//デストラクタ
Flying_Attack::~Flying_Attack()
{

}

//更新
void Flying_Attack::Update()
{
	//右から左へ
	x -= speed;
}

//描画
void Flying_Attack::Draw()
{
	//画像変数に何もない場合は　□　を描画
	if (image != 0)
	{
		//画像で描画(中心座標)
		DrawRotaGraph(x, y, 1, 0, image, TRUE);
	}
	else
	{
		// □ を描画   槍：水　　鉄：緑　毒：紫
		DrawBox(x, y, x + w, y + h, colors[static_cast<int>(my_Type)], TRUE);
	}

	//テスト
	DrawFormatString(0, 0, 0xffffff, "イルヨ");
}

// 攻撃によるダメージ取得（ playerのHP(耐久値) ）
int Flying_Attack::GetAttackDamage(int hp)
{
	switch (my_Type)
	{
	case Attack_Type::SPEAR:

		return 10;     //10ダメージ
		break;

	case Attack_Type::IRON:

		return static_cast<int>(hp * 0.5);  //50%の割合ダメージ
		break;

	case Attack_Type::POISON:

		return 50;     //50ダメージ
		break;

	default:
		break;
	}

	return 0;
}