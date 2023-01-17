#include"DxLib.h"
#include "flying_Armor.h"


//コンストラクタ
Flying_Armor::Flying_Armor(Armor_Type type, int durability, int x, int y, int speed)
	:durability(durability), Flying_object(x, y, 45, 45, speed)      //基底クラスのコンストラクタ呼び出し
{
	//コンストラクタで値を渡さないとデフォルト引数で画面右端より飛んできます

	//画像読み込み
	//image = LoadGraph("images/");
}

//デストラクタ
Flying_Armor::~Flying_Armor()
{

}

//更新
void Flying_Armor::Update()
{
	//右から左へ
	x -= speed;
}

//描画
void Flying_Armor::Draw()
{
	//画像変数に何もない場合は　□　を描画
	if (image != 0)
	{
		//画像で描画(中心座標)
		DrawRotaGraph(x, y, 1, 0, image, TRUE);
	}
	else
	{
		// □ を描画
		DrawBox(x, y, x + w, y + h, 0xffffff, TRUE);
	}
}
