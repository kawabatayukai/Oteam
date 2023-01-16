#pragma once
#include "flying_object.h"


//   攻撃          右から左に飛んでいく（仮）

//攻撃の種類
enum class Attack_Type
{
	SPEAR,      //槍　竹
	IRON,       //鉄　球
	POISON,     //毒　ポーション
};


class Flying_Attack : public Flying_object
{
public:
	//コンストラクタ
	Flying_Attack(Attack_Type type, int x = 1200, int y = 360, int speed = 10);

	//デストラクタ
	~Flying_Attack();

	void Update() override;    //更新
	void Draw() override;      //描画

	// 攻撃によるダメージ取得（ playerのHP(耐久値) ）
	int GetAttackDamage(const int hp);

private:
	int image = 0;          //画像用変数

	Attack_Type my_Type;    //自分がどのタイプの攻撃か

	int damage = 0;
};

