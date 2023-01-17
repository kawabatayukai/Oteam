#include"DxLib.h"
#include"GameMain.h"
#include"flying_Armor.h"
#include"flying_Attack.h"
#include"flying_object.h"
#include"Player.h"

//防具最大表示数
#define ARMOR_MAX 10 

//攻撃最大表示数
#define ATTACK_MAX 10 

//防具の配列
Flying_object** obj_armor;     //基底クラス型ポインタ

//攻撃の配列
Flying_object** obj_attack;

Player player;

//フレームをカウント
int frameCount = 0;

Turn now_turn;

//テスト用
char Turn_str[][7] = { "Catch","Attack" };

//ゲームメイン初期処理（コンストラクタ代わり）
void GameMain_Init() {
	//防具10個分のメモリを確保
	obj_armor = new Flying_object * [ARMOR_MAX];

	//初期化
	for (int i = 0; i < ARMOR_MAX; i++) obj_armor[i] = nullptr;

	//防具10個分のメモリを確保
	obj_attack = new Flying_object * [ATTACK_MAX];

	//初期化
	for (int i = 0; i < ATTACK_MAX; i++) obj_attack[i] = nullptr;

	//最初のターンは装備
	now_turn = Turn::CATCH;
	frameCount = 0;
}

//ゲームメイン終了処理（デストラクタの代わり）
void GameMain_Final() {
	delete obj_armor;
	delete obj_attack;
	delete& player;
}

//防具  生成・更新・削除
void Armor_Update()
{
	int armor_count;   //防具配列の〇番目を見ているか

	//配列を一つずつみる
	for (armor_count = 0; armor_count < ARMOR_MAX; armor_count++)
	{
		//nullptrより後にはnullptrしかないのでループを抜ける
		if (obj_armor[armor_count] == nullptr) break;

		//更新　（移動）
		obj_armor[armor_count]->Update();
		if (player.Hit(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])))
		{
			DrawString(0, 20, "Hit", 0xffffff);
			player.SetHP(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])->GetHP());
		}

		//画面外に到達,またはプレイヤーとHitで削除
		if (obj_armor[armor_count]->CheckScreenOut() == true
			|| player.Hit(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])) == true)
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
		//タイプ
		int r_type = GetRand(2);       //０～２の乱数

		//耐久値
		int r_dura = 30;   // とりあえず

		//ｙ座標（高さ）　　ｘ座標は 1300固定（画面外右側）
		int r_y = (GetRand(10) * 60) + 60;

		//スピード（常に 5以上）
		int r_speed = (GetRand(3) + 1) + 5;

		//生成する　　　　　　　                  耐久値   ｘ　　ｙ　 ｽﾋﾟｰﾄﾞ
		obj_armor[armor_count] = new Flying_Armor(static_cast<Armor_Type>(r_type), r_dura, 1300, r_y, r_speed);
	}




}

//攻撃  生成・更新・削除
void Attack_Update() {
	int attack_count;   //防具配列の〇番目を見ているか

	//配列を一つずつみる
	for (attack_count = 0; attack_count < ATTACK_MAX; attack_count++)
	{
		//nullptrより後にはnullptrしかないのでループを抜ける
		if (obj_attack[attack_count] == nullptr) break;

		//更新　（移動）
		obj_attack[attack_count]->Update();
		if (player.Hit(dynamic_cast<Flying_Attack*>(obj_attack[attack_count])))
		{
			DrawString(0, 30, "Die", 0xff0000);
		}

		//画面外に到達、またはプレイヤーとHitで削除
		if (obj_attack[attack_count]->CheckScreenOut() == true
			|| player.Hit(dynamic_cast<Flying_Attack*>(obj_attack[attack_count])) == true)
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
		obj_attack[attack_count] = new Flying_Attack((r_type), 1300, r_y, r_speed);
	}
}

//ゲームメイン更新・計算
void GameMain_Update()
{
	player.Update();

	switch (now_turn)
	{
	case Turn::CATCH:

		Armor_Update();
		break;

	case Turn::ATTACK:

		//ターン切り替え後・2秒待つ
		if (frameCount > 120) Attack_Update();
		break;
	default:
		break;
	}
}

//ゲームメイン描画
void GameMain_Draw()
{
	player.Draw();

	switch (now_turn)
	{
	case Turn::CATCH:

		//防具の描画
		for (int i = 0; i < ARMOR_MAX; i++)
		{
			if (obj_armor[i] == nullptr) break;   //nullptrより後にはnullptrしかないのでループを抜ける
			obj_armor[i]->Draw();                 //要素がある時は描画
		}
		break;

	case Turn::ATTACK:

		//攻撃の描画
		for (int i = 0; i < ATTACK_MAX; i++)
		{
			if (obj_attack[i] == nullptr) break;  //nullptrより後にはnullptrしかないのでループを抜ける
			obj_attack[i]->Draw();                //要素があるときは描画
		}
		break;
	default:
		break;
	}

	//Test
	DrawFormatString(0, 100, 0x000000, "Now : %s", Turn_str[static_cast<int>(now_turn)]);
	DrawFormatString(0, 130, 0x000000, "Time : %d", (frameCount / 60));
}

//ゲームメイン
void GameMain(int &gamemode)
{
	GameMain_Update();    //ゲームメイン更新・計算

	GameMain_Draw();      //ゲームメイン描画

	//フレームを加算
	frameCount++;


	//Attackターンは30秒で終了
	if (now_turn == Turn::ATTACK && frameCount % 1800 == 0)
	{
		//ランキング

		gamemode = 6;   //リザルト画面へ
	}

	//20秒でターンを切り替え
	if (now_turn == Turn::CATCH && frameCount % 600 == 0)
	{
		now_turn = Turn::ATTACK;  //攻撃を受けるターン
		frameCount = 0;           //カウントをリセット
	}

}