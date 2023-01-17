#pragma once
#include "flying_object.h"


//   防具          右から左に飛んでいく（仮）


class Flying_Armor : public Flying_object
{
public:
	//コンストラクタ
	Flying_Armor(int durability = 10, int x = 1200, int y = 360, int speed = 1);

	//デストラクタ
	~Flying_Armor();

	void Update() override;    //更新
	void Draw() override;      //描画

	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetW() const { return w; }
	int GetH() const { return h; }

	int GetHP() const { return durability; }
	
private:
	int image = 0;    //画像用変数

	int durability;   //耐久値
};

