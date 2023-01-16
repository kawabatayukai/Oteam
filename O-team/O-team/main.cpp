#include"DxLib.h"
#include"information.h"  //使いたい .hファイル をインクルードします


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("Neko");             //タイトルを設定
	ChangeWindowMode(TRUE);                //ウィンドウモードで起動

	//ウィンドウサイズを設定
	SetGraphMode(SCREENSIZE_X, SCREENSIZE_Y, 32);

	if (DxLib_Init() == -1) return -1;     //DXライブラリの初期化処理
	SetDrawScreen(DX_SCREEN_BACK);         //描画先画面を裏にする

	//問題なければループ
	while (ProcessMessage() == 0)
	{

		//キー入力取得 
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);    //例のコントローラーの入力も使えます
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();                 //画面を初期化

		if (g_NowKey & PAD_INPUT_A) DrawString(0, 0, "TEST", 0xffffff);

		ScreenFlip();                      //裏画面を表画面に反映
	}

	DxLib_End();				           // ＤＸライブラリ使用の終了処理

	return 0;				               // ソフトの終了 
}

/******************************************
 * 画像読込
 ******************************************/
int LoadImages()
{
	// ヘルプ画像読込
	if ((g_HelpImg = LoadGraph("images/help.bmp")) == -1) return -1;
}