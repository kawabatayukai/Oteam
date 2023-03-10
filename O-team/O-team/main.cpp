#include"DxLib.h"
#include"information.h"  //使いたい .hファイル をインクルードします
#include"Help.h"
#include"Help2.h"
#include"Ranking.h"
#include"Result.h"
#include"Title.h"
#include"End.h"
#include"Keyboard.h"
#include"GameMain.h"
#include "PadInput.h"
#include"fps.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("TsukemonoGatari");             //タイトルを設定
	ChangeWindowMode(TRUE);                //ウィンドウモードで起動

	//ウィンドウサイズを設定
	SetGraphMode(SCREENSIZE_X, SCREENSIZE_Y, 32);

	if (DxLib_Init() == -1) return -1;     //DXライブラリの初期化処理
	SetDrawScreen(DX_SCREEN_BACK);         //描画先画面を裏にする

	//画像読み込み
	if (LoadImages() == -1) return -1;

	//サウンド読込み
	if (LoadSounds() == -1) return -1;

	// ランキングデータの読込
	if (ReadRanking() == -1) return -1;

	//最初はタイトル
	GameMode = mode::TITLE;

	//キーボードの初期化
	KeyBoardInit();

	//FPSControll
	FPSControll FpsCtrl(60.0f, 800);

	//問題なければループ
	while (ProcessMessage() == 0 && GameMode != CLOSE && !(g_KeyFlg & PAD_INPUT_START))
	{
		//ESCAPEキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) DxLib_End();
		//PAD入力
		PAD_INPUT::UpdateKey();
		//PADのBACKキーで終了
		if (PAD_INPUT::OnClick(XINPUT_BUTTON_BACK)) DxLib_End();

		//キー入力取得 
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);    //例のコントローラーの入力も使えます
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();                 //画面を初期化

		DrawBox(0, 0, 1280, 720, 0xd3d3d3,TRUE);
		switch (GameMode)
		{
		case mode::TITLE:

			//タイトル
			DrawGameTitle(g_KeyFlg, GameMode);

			break;

		case mode::INIT:

			//初期化
			GameInit();

			break;

		case mode::MAIN:

			//ゲームメイン      ランキング5番目のスコアをもらう g_Ranking[RANKING_DATA-1].score みたいな
			GameMain(GameMode, g_Ranking[RANKING_DATA - 1].score, g_Score);

			break;

		case mode::RANKING:

			//ランキング表示
			DrawRanking(g_KeyFlg, GameMode);

			break;

		case mode::HELP:

			//ヘルプ表示
			DrawHelp(g_KeyFlg, GameMode);

			break;

		case mode::INPUTNAME:

			//名前入力
			InputRanking(g_NowKey, GameMode,g_Score);

			break;

		case mode::RESULT:

			//リザルト
			DrawResult(g_KeyFlg, GameMode, g_Score);

			break;

		case mode::END:

			//エンド
			DrawGameEnd(g_KeyFlg, GameMode);
			break;

		case mode::CLOSE:

			//くろーず
			break;

		case mode::HELP2:

			DrawHelp2(g_KeyFlg, GameMode);
			break;

		default:
			break;
		}

		//FPS固定処理
		FpsCtrl.Get();
		FpsCtrl.Wait();
		//FpsCtrl.Disp();

		DxLib::ScreenFlip();                      //裏画面を表画面に反映
	}

	DxLib::DxLib_End();				           // ＤＸライブラリ使用の終了処理

	return 0;				               // ソフトの終了 
}

//初期化
void GameInit()
{
	//いろいろ初期化
	GameMain_Init();

	//キーボードの初期化
	KeyBoardInit();

	//ゲームメインへ
	GameMode = mode::MAIN;
}


//画像読み込み
int LoadImages()
{
	if (LoadHelpImage() == -1) return -1;     //ヘルプ画像読み込み
	if (LoadHelp2Image() == -1) return -1;    //ヘルプ2画像読み込み
	if (LoadRankingImage() == -1) return -1;  //ランキング画像読み込み
	if (LoadResultImage() == -1) return -1;   //リザルト画像読み込み
	if (LoadTitleImage() == -1) return -1;    //タイトル画像読み込み
	if (LoadEndImage() == -1) return -1;      //エンド画像読み込み
	if (LoadResultImage() == -1) return -1;   //エンド画像読み込み
	if (LoadGameMainImages() == -1) return -1;//ゲームメイン画像読み込み

	return 0;
}

//音声読み込み
int LoadSounds()
{
	if (LoadTitleSounds() == -1) return -1;      //タイトルサウンド読み込み
	if (LoadGameMainSounds() == -1) return -1;   //ゲームメインサウンド読み込み
	if (LoadKeyBoardSounds() == -1) return -1;   //ランキングサウンド読み込み
	if (LoadResultSounds() == -1) return -1;     //リザルトサウンド読み込み
	if (LoadHelpSounds() == -1) return -1;       //ヘルプサウンド読み込み
	if (LoadHelp2Sounds() == -1) return -1;      //ヘルプ2サウンド読み込み
	if (LoadRankingSounds() == -1) return -1;    //ランキングサウンド読み込み
	if (LoadEndSounds() == -1) return -1;        //エンドサウンド読み込み

	return 0;
}