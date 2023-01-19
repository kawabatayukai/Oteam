#include"DxLib.h"
#include"GameMain.h"
#include"flying_Armor.h"
#include"flying_Attack.h"
#include"flying_object.h"
#include"Player.h"

/***********************************************************************/
/*  コメント文全部文字化け　→　修正                                   */
/*　　               があったのでおかしなところがありそうです          */
/*********************************************************************:*/


#define DRAWAREA_X 980 //右側エリア

//攻撃のスピード
#define SPEED_ATTACK (GetRand(4) + 1) + 5

//防具のスピード
#define SPEED_ARMOR  (GetRand(3) + 1) + 5

//防具最大出現数
#define ARMOR_MAX 25

//攻撃最大出現数
#define ATTACK_MAX 15

//防具タイムリミット
#define ARMOR_LIMIT 600

//攻撃タイムリミット
#define ATTACK_LIMIT 1200

//防具配列
Flying_object** obj_armor;     //基底クラス型

//攻撃配列
Flying_object** obj_attack;

//プレイヤー
Player* player;

int frameCount = 0;    //フレームをカウント
int death_frame = 0;   //死亡時からのフレームをカウント

Turn now_turn;         //現在のターン

int image_Back[2];     //背景画像
int image_CorO[2];     //Clear or Over  画像
int image_R_area;      //右側エリア画像
int image_hukidashi;   //吹き出し

float now_hp = 0.0f;   //右側ゲージの高さ
int font_handle;       //ゲームメイン内で使用するフォント

//BGM・SE
int GameMainBGM;
int GetSE;

int SpearSE;
int IronSE;
int PoisonSE;


//現在のターン
char Turn_str[][7] = { "Catch","Attack","END" };

//����ׂ�
//char Talk_str[][10] = { " ","ぐふ","ぐは","ぐへ" ,"わーい","きた","うぐぐ","ムムム"};
//char Talk_str[][10] = { " ","","","" ,"","","","" };

int Talk_images[8];
int talk_num = 0;    //”しゃべる”配列添え字
int talk_frame = 0;  //しゃべっている時間

//ゲームメイン画像読み込み
int LoadGameMainImages()
{
	//右エリア
	if ((image_R_area = LoadGraph("images/GameMain/RightBox.png")) == -1) return -1;

	//吹き出し
	if ((image_hukidashi = LoadGraph("images/GameMain/RightBox2.png")) == -1) return -1;

	//Clear or Over  
	LoadDivGraph("images/GameMain/Game_CorO.png", 2, 2, 1, 1280, 720, image_CorO);

	//背景
	LoadDivGraph("images/GameMain/BackLink.png", 2, 2, 1, 1280, 720, image_Back);

	//おしゃべり
	LoadDivGraph("images/GameMain/Talk_Strings.png", 8, 8, 1, 120, 40, Talk_images);

	return 0;
}

//ゲームメイン音声読み込み
int LoadGameMainSounds() {
	if ((GameMainBGM = LoadSoundMem("sounds/bgm/GameMain.wav")) == -1) return -1;
	if ((GetSE = LoadSoundMem("sounds/se/Get.wav")) == -1) return -1;
	if ((SpearSE = LoadSoundMem("sounds/se/Takeyari.wav")) == -1) return -1;
	if ((IronSE = LoadSoundMem("sounds/se/Tekkyu.wav")) == -1) return -1;
	if ((PoisonSE = LoadSoundMem("sounds/se/Doku.wav")) == -1) return -1;
}

//ゲームメイン初期処理（コンストラクタの代わり）
void GameMain_Init() 
{
	LoadGameMainSounds();

	//防具10個分のメモリを確保
	obj_armor = new Flying_object * [ARMOR_MAX];

	//初期化
	for (int i = 0; i < ARMOR_MAX; i++) obj_armor[i] = nullptr;

	//攻撃のメモリを確保
	obj_attack = new Flying_object * [ATTACK_MAX];

	//初期化
	for (int i = 0; i < ATTACK_MAX; i++) obj_attack[i] = nullptr;

	//プレイヤーのメモリを確保
	player = new Player();

	//ターンを初期化
	now_turn = Turn::CATCH;

	frameCount = 0;
	death_frame = 0;

	now_hp = 0.0f;
	talk_num = 0;
	talk_frame = 0;

	//プレイヤー画像
	player->LoadImages();

	//フォントを作成
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
	int armor_count;   //現在配列の〇番目を見ている

	//配列をみる
	for (armor_count = 0; armor_count < ARMOR_MAX; armor_count++)
	{
		//nullptrより後には要素なし
		if (obj_armor[armor_count] == nullptr) break;

		//防具の更新
		obj_armor[armor_count]->Update();
		if (player->Hit(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])))
		{
			//DrawString(0, 20, "Hit", 0xffffff);

			//HPが増える
			player->SetHP(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])->GetHP());

			//ChangeNextPlayVolumeSoundMem(   , RankUpSE);  //次に流す音量を調整  ～２５５  255が通常
			PlaySoundMem(GetSE, DX_PLAYTYPE_BACK);

			//しゃべる
			talk_num = 5;
		}

		//画面外 or Hitで削除
		if (obj_armor[armor_count]->CheckScreenOut() == true
			|| player->Hit(dynamic_cast<Flying_Armor*>(obj_armor[armor_count])) == true)
		{
			delete obj_armor[armor_count];         //削除
			obj_armor[armor_count] = nullptr;      //削除元を初期化

			//詰める
			for (int i = armor_count; i < (ARMOR_MAX - 1); i++)
			{
				//nullptrより後には要素なし
				if (obj_armor[i + 1] == nullptr) break;

				obj_armor[i] = obj_armor[i + 1];   //詰める
				obj_armor[i + 1] = nullptr;        //詰めた元を初期化
			}
			armor_count--;
		}
	}

	//生成
	if (armor_count < ARMOR_MAX && obj_armor[armor_count] == nullptr)
	{
		//種類
		int r_type = GetRand(2);       

		//耐久地
		int r_dura = 100;   // �Ƃ肠����

		//高さ
		int r_y = (GetRand(10) * 60) + 60;

		//スピード
		int r_speed = SPEED_ARMOR;//(GetRand(3) + 1) + 5;

		//生成
		obj_armor[armor_count] = new Flying_Armor(static_cast<Armor_Type>(r_type), r_dura, 1300, r_y, r_speed);
	}
}

//攻撃  生成・更新・削除
void Attack_Update() {
	int attack_count;   //現在配列の〇番目を見ている

	//配列をみる
	for (attack_count = 0; attack_count < ATTACK_MAX; attack_count++)
	{
		//nullptrより後には要素なし
		if (obj_attack[attack_count] == nullptr) break;

		//攻撃の更新
		obj_attack[attack_count]->Update();
		if (player->Hit(dynamic_cast<Flying_Attack*>(obj_attack[attack_count])))
		{
			//ダメージを食らう
			player->SetHP((dynamic_cast<Flying_Attack*>(obj_attack[attack_count])->GetAttackDamage(player->GetHP())) * -1);
			switch (dynamic_cast<Flying_Attack*>(obj_attack[attack_count])->GetType())
			{
			case Attack_Type::SPEAR:
				PlaySoundMem(SpearSE, DX_PLAYTYPE_BACK);
				talk_num = 1;
				break;

			case Attack_Type::IRON:
				PlaySoundMem(IronSE, DX_PLAYTYPE_BACK);
				talk_num = 2;
				break;

			case Attack_Type::POISON:
				ChangeNextPlayVolumeSoundMem(200, PoisonSE);  //次に流す音量を調整  ～２５５  255が通常
				PlaySoundMem(PoisonSE, DX_PLAYTYPE_BACK);
				talk_num = 3;
				break;

			default:
				break;
			}
		}

		//画面外 or Hitで削除
		if (obj_attack[attack_count]->CheckScreenOut() == true
			|| player->Hit(dynamic_cast<Flying_Attack*>(obj_attack[attack_count])) == true)
		{
			delete obj_attack[attack_count];         //削除
			obj_attack[attack_count] = nullptr;      //削除元を初期化

			//詰める
			for (int i = attack_count; i < (ATTACK_MAX - 1); i++)
			{
				//nullptrより後には要素なし
				if (obj_attack[i + 1] == nullptr) break;

				obj_attack[i] = obj_attack[i + 1];   //詰める
				obj_attack[i + 1] = nullptr;        //詰めた元を初期化
			}
			attack_count--;
		}
	}

	//生成
	if (attack_count < ATTACK_MAX && obj_attack[attack_count] == nullptr)
	{
		//種類
		int r_type = GetRand(2);       //�O�`�Q�̗���

		//高さ
		int r_y = (GetRand(10) * 60) + 60;

		//スピード
		int r_speed = SPEED_ATTACK; //(GetRand(3) + 1) + 5;

		//生成
		obj_attack[attack_count] = new Flying_Attack((r_type), 1300, r_y, r_speed);
	}
}

//ゲームメイン更新・計算
void GameMain_Update()
{
	ChangeNextPlayVolumeSoundMem(180, GameMainBGM);  //次に流す音量を調整  ～２５５  255が通常
	PlaySoundMem(GameMainBGM, DX_PLAYTYPE_LOOP, FALSE);

	//右エリア内ゲージ用
	now_hp = static_cast<float>(player->GetHP() * 0.5);
	if (now_hp < 0.0f) now_hp = 0.0f;  //0より小さくならない

	//しゃべる時間
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

		//最初の２秒
		if (frameCount > 120) Attack_Update();
		else
		{
			DrawBox(0, 0, 1280, 720, 0x000000, TRUE);  //暗転
			talk_num = 7;
		}
		break;

	case Turn::END:

		death_frame++;

		//プレイヤーのHPが０以上
		if (player->GetHP() > 0)
		{
			player->Update_Win();    //跳ねる
			talk_num = 4;
		}
		else talk_num = 6;

		break;

	default:
		StopSoundMem(GameMainBGM);
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

		//描画
		for (int i = 0; i < ARMOR_MAX; i++)
		{
			if (obj_armor[i] == nullptr) break;   //nullptrより後はnullptrのみなので抜ける
			obj_armor[i]->Draw();                 //要素があれば描画

		}

		break;

	case Turn::ATTACK:

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
		DrawGraph(0, 0, image_Back[1], TRUE);     //背景
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		if (frameCount > 120) {}
		else DrawBox(0, 0, 1280, 720, 0x000000, TRUE);  //暗転(？)

		player->Draw();                           //プレイヤー描画

		//描画
		for (int i = 0; i < ATTACK_MAX; i++)
		{
			if (obj_attack[i] == nullptr) break;  //nullptrより後はnullptrのみなので抜ける
			obj_attack[i]->Draw();                //攻撃描画
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
			player->Draw_Win();       //跳ねる（描画）
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

	DrawBox(1150, 80, 1250, 700, 0x1f1006, TRUE);                            //ゲージのうしろ

	//(float型のDrawBoxらしいです)  ゲージ
	DrawBoxAA(1150.0f, (690.0f - now_hp), 1250.0f, 690.0f, 0xff0000, TRUE);  
	DrawGraph(0, 0, image_R_area, TRUE);                                     //右エリア

	DrawFormatStringToHandle(1130, 20, 0xffffff, font_handle, "HP : %d", player->GetHP());

	//プレイヤーを右エリア内に
	player->Draw_Right(1060, 620);
	if (talk_num != 0) DrawGraph(0, 0, image_hukidashi, TRUE);
	//DrawFormatStringToHandle(1010, 412, 0x000000, font_handle, Talk_str[talk_num]);  //����ׂ�

	DrawRotaGraph(1062, 427, 1, 0, Talk_images[talk_num], TRUE);

	//制限時間
	if (now_turn == Turn::CATCH)
	{
		DrawFormatStringToHandle(1000, 120, 0xffffff, font_handle, "Time : %d", (ARMOR_LIMIT/60) - (frameCount / 60));
	}
	else if (now_turn == Turn::ATTACK)
	{
		DrawFormatStringToHandle(1000, 120, 0xffffff, font_handle, "Time : %d", (ATTACK_LIMIT/60) - (frameCount / 60));
	}
	else{}
}

//ゲームメイン  ランキング5番目のスコア・スコアを保持する変数をもらう
void GameMain(int &gamemode,int lowscore, int& g_score)
{
	GameMain_Update();    //ゲームメイン更新

	GameMain_Draw();      //ゲームメイン描画

	GameMain_DrawArea();  //右エリア描画

	//フレームをカウント
	frameCount++;

	//Attackターンで20秒経過
	if (now_turn == Turn::ATTACK && frameCount % ATTACK_LIMIT == 0 || player->GetHP() <= 0)
	{

		player->SetWin_PointY();  //Y座標を保持
		now_turn = Turn::END;     //ENDに切り替え
		death_frame = frameCount;
	}

	//CATCHターンで10秒経過
	if (now_turn == Turn::CATCH && frameCount % ARMOR_LIMIT == 0)
	{
		now_turn = Turn::ATTACK;  //ATTACKに切り替え
		frameCount = 0;           
	}

	//30秒経過
	if (now_turn == Turn::END && death_frame % 480 == 0)
	{
		g_score = player->GetHP();
		

		//今回のスコアとランキング最低スコアを比較
		if (g_score > lowscore)
		{
			StopSoundMem(GameMainBGM);
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