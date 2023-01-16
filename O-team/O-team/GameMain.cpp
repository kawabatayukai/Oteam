#include"DxLib.h"
#include"GameMain.h"
#include"flying_Armor.h"
#include"flying_Attack.h"
#include"flying_object.h"

//防具最大表示数
#define ARMOR_MAX 10 

//攻撃最大表示数
#define ATTACK_MAX 10 

//防具の配列
Flying_object** obj_armor;     //基底クラス型ポインタ

//攻撃の配列
Flying_object** obj_attack;  


//ゲームメイン初期処理（コンストラクタ代わり）
void GameMain_Init()
{
	//防具10個分のメモリを確保
	obj_armor = new Flying_object * [ARMOR_MAX];

	//初期化
	for (int i = 0; i < ARMOR_MAX; i++) obj_armor[i] = nullptr;

	
	//防具10個分のメモリを確保
	obj_attack = new Flying_object * [ATTACK_MAX];

	//初期化
	for (int i = 0; i < ATTACK_MAX; i++) obj_attack[i] = nullptr;
}

//ゲームメイン更新・計算
void GameMain_Update()
{

	int armor_count;   //防具配列の〇番目を見ているか

	//配列を一つずつみる
	for (armor_count = 0; armor_count < ARMOR_MAX; armor_count++)
	{
		//nullptrより後にはnullptrしかないのでループを抜ける
		if (obj_armor[armor_count] == nullptr) break;

		//更新　（移動）
		obj_armor[armor_count]->Update();

		//画面外に到達で削除
		if (obj_armor[armor_count]->CheckScreenOut() == true)
		{
			delete obj_armor[armor_count];         //到達したﾔﾂを削除
			obj_armor[armor_count] = nullptr;      //削除した配列の要素を初期化

			//配列を詰める
			for (int i = armor_count; i < (ARMOR_MAX - 1); i++)
			{
				//次の要素が nullptr なら詰める必要がないので抜ける
				if (obj_armor[i + 1] == nullptr) break;

				obj_armor[i] = obj_armor[i + 1];   //詰める
				obj_armor[i + 1] = nullptr;        //詰められた要素は初期化
			}
			armor_count--;
		}
	}

	//配列に空要素があればオブジェクトを生成する
	if (armor_count < ARMOR_MAX && obj_armor[armor_count] == nullptr)
	{
		//耐久値
		int r_dura = 30;   // とりあえず

		//ｙ座標（高さ）　　ｘ座標は 1300固定（画面外右側）
		int r_y = (GetRand(10) * 60) + 60;

		//スピード（常に 5以上）
		int r_speed = (GetRand(3) + 1) + 5;

		//生成する　　　　　　　                  耐久値   ｘ　　ｙ　 ｽﾋﾟｰﾄﾞ
		obj_armor[armor_count] = new Flying_Armor(r_dura, 1300, r_y, r_speed);
	}




	int attack_count;   //防具配列の〇番目を見ているか

	//配列を一つずつみる
	for (attack_count = 0; attack_count < ATTACK_MAX; attack_count++)
	{
		//nullptrより後にはnullptrしかないのでループを抜ける
		if (obj_attack[attack_count] == nullptr) break;

		//更新　（移動）
		obj_attack[attack_count]->Update();

		//画面外に到達で削除
		if (obj_attack[attack_count]->CheckScreenOut() == true)
		{
			delete obj_attack[attack_count];         //到達したﾔﾂを削除
			obj_attack[attack_count] = nullptr;      //削除した配列の要素を初期化

			//配列を詰める
			for (int i = attack_count; i < (ATTACK_MAX - 1); i++)
			{
				//次の要素が nullptr なら詰める必要がないので抜ける
				if (obj_attack[i + 1] == nullptr) break;

				obj_attack[i] = obj_attack[i + 1];   //詰める
				obj_attack[i + 1] = nullptr;        //詰められた要素は初期化
			}
			attack_count--;
		}
	}

	//配列に空要素があればオブジェクトを生成する
	if (attack_count < ATTACK_MAX && obj_attack[attack_count] == nullptr)
	{
		//タイプ
		int r_type = GetRand(2);       //０～２の乱数

		//ｙ座標（高さ）　　ｘ座標は 1300固定（画面外右側）
		int r_y = (GetRand(10) * 60) + 60;

		//スピード（常に 5以上）
		int r_speed = (GetRand(3) + 1) + 15;

		//生成する　　　　　　　                  タイプ   ｘ　　ｙ　 ｽﾋﾟｰﾄﾞ
		obj_attack[attack_count] = new Flying_Attack(static_cast<Attack_Type>(r_type), 1300, r_y, r_speed);
	}
}

//ゲームメイン描画
void GameMain_Draw()
{
	//防具の描画
	for (int i = 0; i < ARMOR_MAX; i++)
	{
		if (obj_armor[i] == nullptr) break;   //nullptrより後にはnullptrしかないのでループを抜ける
		obj_armor[i]->Draw();                 //要素がある時は描画
	}

	//攻撃の描画
	for (int i = 0; i < ATTACK_MAX; i++)
	{
		if (obj_attack[i] == nullptr) break;  //nullptrより後にはnullptrしかないのでループを抜ける
		obj_attack[i]->Draw();                //要素があるときは描画
	}
}

//ゲームメイン
void GameMain()
{
	GameMain_Update();    //ゲームメイン更新・計算

	GameMain_Draw();      //ゲームメイン描画
}