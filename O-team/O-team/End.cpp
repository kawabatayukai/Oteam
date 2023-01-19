#include"DxLib.h"
#include"End.h"

int g_EndImg;	//エンド画像背景
int g_WaitTime = 0;

int EndBGM;

//エンド画像描画
void DrawGameEnd(int key, int& gamemode)
{
	ChangeNextPlayVolumeSoundMem(180, EndBGM);  //次に流す音量を調整  ～２５５  255が通常
	PlaySoundMem(EndBGM, DX_PLAYTYPE_LOOP, FALSE);
	//エンド画像
	DrawGraph(0, 0, g_EndImg, FALSE);
	//クローズするまでの時間
	if (++g_WaitTime > 330)gamemode = 8;
}


//エンド画像読込
int LoadEndImage()
{
	if ((g_EndImg = LoadGraph("images/End/EndImage.png")) == -1)return -1;
	return 0;
}

//エンドサウンド読込
int LoadEndSounds() {
	if ((EndBGM = LoadSoundMem("sounds/bgm/End.wav")) == -1) return -1;

}
