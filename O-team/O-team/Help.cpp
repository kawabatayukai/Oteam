#include"DxLib.h"
#include"Help.h"

//Help.hで宣言した関数の定義をここに書きます
int g_HelpImg[2];

//ヘルプ画面描画
void DrawHelp(int key, int& gamemode)
{
	//キー入力は"key",GameModeを変えたいときは"gamemode"を変更します
	
	// B(2)ボタンチェックマスク(Xキー)でメニューに戻る
	if (key & PAD_INPUT_B) gamemode = 0;

	if (key & PAD_INPUT_RIGHT)
	{
		DrawGraph(0, 0, g_HelpImg[1], FALSE);
	}

	// ヘルプ画像表示
	DrawGraph(0, 0, g_HelpImg[0], FALSE);

	// 説明表示
	SetFontSize(27);
	//DrawString(300, 240, "* タイミングよくジャンプして防具を身につけよう *", 0xffffff, 0);

	//DrawString(380, 670, "--- Bボタンを押してタイトルへ戻る ---", 0xffffff, 0);
}

//ヘルプ画像読み込み
int LoadHelpImage()
{
	// ヘルプ画像読込
	if ((g_HelpImg[0] = LoadGraph("images/help1.png")) == -1) return -1;
	if ((g_HelpImg[1] = LoadGraph("images/help2.png")) == -1) return -1;

	return 0;
}