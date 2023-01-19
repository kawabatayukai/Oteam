#include"DxLib.h"
#include"GameMain.h"
#include"flying_Armor.h"
#include"flying_Attack.h"
#include"flying_object.h"
#include"Player.h"


#define DRAWAREA_X 980 //描画エリア最低値

//攻撃のスピード  5 ～ 10
#define SPEED_ATTACK (GetRand(4) + 1) + 5

//防具のスピード  5 ～ 9
#define SPEED_ARMOR  (GetRand(3) + 1) + 5

//防具最大表示数
#define ARMOR_MAX 25

//攻撃最大表示数
#define ATTACK_MAX 15

//防具の配列
Flying_object** obj_armor;     //基底クラス型ポインタ

//攻撃の配列
Flying_object** obj_attack;

//プレイヤー
Player* player;

//フレームをカウント
int frameCount = 0;
int death_frame = 0;

//現在のターン
Turn now_turn;

int image_Back[2];     //背景画像 1,2
int image_CorO[2];     //Clear or Over  です
int image_R_area;      //右の描画エリア画像  
float now_hp = 0.0f;   //現在のHP（右エリア内のゲージで使用）
int font_handle;       //フォント

//テスト用
char Turn_str[][7] = { "Catch","Attack","END" };

//しゃべる
char Talk_str[][10] = { " ","ぐふ","ぐは","ぐへ" ,"わーい","キタ","うぐぐ","ムムム"};
int talk_num = 0;    //しゃべる番号
int talk_frame = 0;

//ゲームメイン画像読み込み
int LoadGameMainImages()
{
	//右の描画エリア画像
	if ((image_R_area = LoadGraph("images/RightBox2.png")) == -1) return -1;

	//Clear or Over  です
	LoadDivGraph("images/Game_CorO.png", 2, 2, 1, 1280, 720, image_CorO);

	//背景
	LoadDivGraph("images/BackLink.png", 2, 2, 1, 1280, 720, image_Back);

	return 0;
}

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

	//プレーヤーのメモリを確保・コンストラクタ呼び出し
	player = new Player();

	//最初のターンは装備
	now_turn = Turn::CATCH;

	frameCount = 0;
	death_frame = 0;

	now_hp = 0.0f;
	talk_num = 0;
	talk_frame = 0;

	//画像
	player->LoadImages();

	//ゲームメイン内で使うフォントを作成      NULL のところにWindows標準装備のフォントが使えそう（?）
	font_handle = CreateFontToHandle(NULL, 30, 10, DX_FONTTYPE_ANTIALIASING_8X8);
}

//ゲームメイン終了処理（デストラクタの代わり）
void GameMain_Final() {
	delete obj_armor;
	delete obj_attack;
	delete player;

	//フォントを削除
	DeleteFontToHandle(font_handle);
}

//防具  生成・更新・削除
void Armor_Update(){
	int armor_count;   //防具配列の〇番目を見ているか

	//配列を一つずつみる
	for (armor_count = 0; armor_count < ARMOR_MAX; armor_count++)
	{
		//nullptrより後にはnullptrしかないのでループを抜ける
		if (obj_armor[armor_count] == nullptr) break;

		//更新　（移動）
		obj_armor[armor_count]->Update();
		if (player->Hit(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])))
		{
			//DrawString(0, 20, "Hit", 0xffffff);

			//HPが増える
			player->SetHP(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])->GetHP());

			//しゃべる
			talk_num = 5;
		}

		//画面外に到達,またはプレイヤーとHitで削除
		if (obj_armor[armor_count]->CheckScreenOut() == true
			|| player->Hit(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])) == true)
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
		int r_dura = 100;   // とりあえず

		//ｙ座標（高さ）　　ｘ座標は 1300固定（画面外右側）
		int r_y = (GetRand(10) * 60) + 60;

		//スピード（常に 5以上）
		int r_speed = SPEED_ARMOR;//(GetRand(3) + 1) + 5;

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
		if (player->Hit(dynamic_cast<Flying_Attack*>(obj_attack[attack_count])))
		{
			//ダメージを食らう
			player->SetHP((dynamic_cast<Flying_Attack*>(obj_attack[attack_count])->GetAttackDamage(player->GetHP())) * -1);
			switch (dynamic_cast<Flying_Attack*>(obj_attack[attack_count])->GetType())
			{
			case Attack_Type::SPEAR:
				talk_num = 1;
				break;

			case Attack_Type::IRON:
				talk_num = 2;
				break;

			case Attack_Type::POISON:
				talk_num = 3;
				break;

			default:
				break;
			}
		}

		//画面外に到達、またはプレイヤーとHitで削除
		if (obj_attack[attack_count]->CheckScreenOut() == true
			|| player->Hit(dynamic_cast<Flying_Attack*>(obj_attack[attack_count])) == true)
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
		int r_speed = SPEED_ATTACK; //(GetRand(3) + 1) + 5;

		//生成する　　　　　　　                  タイプ   ｘ　　ｙ　 ｽﾋﾟｰﾄﾞ
		obj_attack[attack_count] = new Flying_Attack((r_type), 1300, r_y, r_speed);
	}
}

//ゲームメイン更新・計算
void GameMain_Update()
{
	//右エリア内ゲージ用
	now_hp = static_cast<float>(player->GetHP() * 0.5);
	if (now_hp < 0.0f) now_hp = 0.0f;  //0より下がらない

	//しゃべる
	talk_frame++;
	if (talk_frame % 120 == 0 && now_turn != Turn::END)
	{
		talk_num = 0;
		talk_frame = 0;
	}


	switch (now_turn)
	{
	case Turn::CATCH:

		player->Update();
		Armor_Update();
		break;

	case Turn::ATTACK:

		player->Update();

		//ターン切り替え後・2秒待つ
		if (frameCount > 120) Attack_Update();
		else
		{
			DrawBox(0, 0, 1280, 720, 0x000000, TRUE);  //暗転
			talk_num = 7;
		}
		break;

	case Turn::END:

		death_frame++;
		//プレイヤーのHPが0以上
		if (player->GetHP() > 0)
		{
			player->Update_Win();
			talk_num = 4;
		}
		else talk_num = 6;

		break;

	default:
		break;
	}
}

//ゲームメイン描画
void GameMain_Draw()
{


	switch (now_turn)
	{
	case Turn::CATCH:

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
		DrawGraph(0, 0, image_Back[0], TRUE);     //背景
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		player->Draw();                           //プレイヤー描画

		//防具の描画
		for (int i = 0; i < ARMOR_MAX; i++)
		{
			if (obj_armor[i] == nullptr) break;   //nullptrより後にはnullptrしかないのでループを抜ける
			obj_armor[i]->Draw();                 //要素がある時は描画

		}

		break;

	case Turn::ATTACK:

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawGraph(0, 0, image_Back[1], TRUE);     //背景
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		if (frameCount > 120) {}
		else DrawBox(0, 0, 1280, 720, 0x000000, TRUE);  //暗転

		player->Draw();                           //プレイヤー描画

		//攻撃の描画
		for (int i = 0; i < ATTACK_MAX; i++)
		{
			if (obj_attack[i] == nullptr) break;  //nullptrより後にはnullptrしかないのでループを抜ける
			obj_attack[i]->Draw();                //要素があるときは描画
		}
		break;

	case Turn::END:

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawGraph(0, 0, image_Back[1], TRUE);     //背景
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		//プレイヤーのHPが0以上
		if (player->GetHP() > 0)
		{
			DrawGraph(0, 0, image_CorO[0], TRUE);    //Game Over
			player->Draw_Win();       //プレイヤーを描画
		}
		else
		{
			DrawGraph(0, 0, image_CorO[1], TRUE);    //Game Over
			player->Draw_Death();
		}
		break;

	default:
		break;
	}
}

//ゲームメイン描画エリア
void GameMain_DrawArea() {
	////描画エリア
	//DrawBox(DRAWAREA_X, 0, 1280, 720, 0x00ddbb, TRUE);

	//SetFontSize(20);
	////Test
	//DrawFormatString(1130, 100, 0x000000, "Now : %s", Turn_str[static_cast<int>(now_turn)]);
	//DrawFormatString(1130, 130, 0x000000, "Time : %d", (frameCount / 60));

	DrawBox(1150, 80, 1250, 700, 0x1f1006, TRUE);                            //ゲージの後ろ

	//(float型が使えるDrawBoxらしいです)  ゲージ
	DrawBoxAA(1150.0f, (690.0f - now_hp), 1250.0f, 690.0f, 0xff0000, TRUE);  
	DrawGraph(0, 0, image_R_area, TRUE);                                     //右エリア画像

	DrawFormatStringToHandle(1130, 20, 0xffffff, font_handle, "HP : %d", player->GetHP());

	//プレイヤー
	player->Draw_Right(1060, 620);
	DrawFormatStringToHandle(1010, 412, 0x000000, font_handle, Talk_str[talk_num]);
}

//ゲームメイン ランキング5番目のスコア・スコアを保持する変数をもらう
void GameMain(int &gamemode,int lowscore, int& g_score)
{
	GameMain_Update();    //ゲームメイン更新・計算

	GameMain_Draw();      //ゲームメイン描画

	GameMain_DrawArea();  //ゲームメイン描画エリア

	//フレームを加算
	frameCount++;

	//if (now_turn == Turn::END && frameCount % 300 == 0)
	//{
	//	DrawString(100, 100, "end", 0xffffff);
	//}

	//Attackターン30秒　または　playerのHPが0以下でターン切り替え　攻撃　→　エンド
	if (now_turn == Turn::ATTACK && frameCount % 1200 == 0 || player->GetHP() <= 0)
	{
		//ランキング

		//if (player->GetHP() < 0)
		//{
		//	
		//}
		player->SetWin_PointY();  //Y座標を保持
		now_turn = Turn::END;     //死亡時
		death_frame = frameCount;
	}

	//20秒でターンを切り替え  装備　→　攻撃
	if (now_turn == Turn::CATCH && frameCount % 600 == 0)
	{
		now_turn = Turn::ATTACK;  //攻撃を受けるターン
		frameCount = 0;           //カウントをリセット
	}

	//死亡または30経過して7秒経過
	if (now_turn == Turn::END && death_frame % 480 == 0)
	{
		g_score = player->GetHP();
		

		//ランキング最低スコアと比較
		if (g_score > lowscore)
		{
			gamemode = 5;  //ランキング入力へ
			GameMain_Final();
		}
		else
		{
			gamemode = 6; //リザルトへ
			GameMain_Final();
		}
	}
}