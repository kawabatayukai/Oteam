#include"DxLib.h"
#include"information.h"  //使いたい .hファイル をインクルードします
#include"Help.h"  


/******************************************
 * ヘルプ画面
 ******************************************/
void DrawHelp()
{
	// B(2)ボタンチェックマスク(Xキー)でメニューに戻る
	if (g_KeyFlg & PAD_INPUT_B) g_GameMode = TITLE;

	// ヘルプ画像表示
	DrawGraph(0, 0, g_HelpImg, FALSE);

	// 説明表示
	SetFontSize(16);
	DrawString(20, 200, "", 0xffffff, 0);

	DrawString(150, 450, "--- Bボタンを押してタイトルへ戻る ---", 0xffffff, 0);
}