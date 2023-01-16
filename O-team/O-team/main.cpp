#include"DxLib.h"

#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	SetMainWindowText("Neko");       //タイトルを設定
	ChangeWindowMode(TRUE);                //ウィンドウモードで起動
	//SetWindowSize(1280, 720);
	SetGraphMode(1280, 720, 32);           //ウィンドウサイズを設定
	if (DxLib_Init() == -1) return -1;     //DXライブラリの初期化処理
	SetDrawScreen(DX_SCREEN_BACK);         //描画先画面を裏にする

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();

		DrawString(0, 0, "TEST", 0xffffff);

		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}