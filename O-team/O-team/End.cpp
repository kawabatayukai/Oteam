#include"DxLib.h"
#include"End.h"

int g_EndImg;	//エンド画像背景
int g_WaitTime = 0;

//エンド画像描画
void DrawGameEnd(int key, int& gamemode)
{
	//エンド画像
	DrawGraph(0, 0, g_EndImg, FALSE);
	//クローズするまでの時間
	if (++g_WaitTime > 360)gamemode = 8;
}


//エンド画像読込
int LoadEndImage()
{
	if ((g_EndImg = LoadGraph("images/EndImage.png")) == -1)return -1;
	return 0;
}
