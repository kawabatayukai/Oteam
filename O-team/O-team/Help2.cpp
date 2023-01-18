#include"DxLib.h"

int g_HelpImg2;

void DrawHelp2(int key, int& gamemode)
{
	DrawGraph(0, 0, g_HelpImg2, FALSE);

	// B(2)ボタンチェックマスク(Xキー)でメニューに戻る
	if (key & PAD_INPUT_B) gamemode = 0;

	if (key & PAD_INPUT_LEFT) gamemode = 4;

}

//ヘルプ画像読み込み
int LoadHelp2Image()
{
	if ((g_HelpImg2 = LoadGraph("images/help2.png")) == -1) return -1;
}