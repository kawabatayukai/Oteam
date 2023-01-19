#include"DxLib.h"

int g_HelpImg2;

//サウンド用変数
int ClickHelp2;
int CursorMoveHelp2;

void DrawHelp2(int key, int& gamemode)
{
	DrawGraph(0, 0, g_HelpImg2, FALSE);


	//次に流す音量を調整  ～２５５  255が通常
	ChangeNextPlayVolumeSoundMem(180, CursorMoveHelp2);
	// B(2)ボタンチェックマスク(Xキー)でメニューに戻る
	if (key & PAD_INPUT_B) {
		PlaySoundMem(ClickHelp2, DX_PLAYTYPE_BACK);
		gamemode = 0;
	}

	if (key & PAD_INPUT_LEFT) {
		PlaySoundMem(CursorMoveHelp2, DX_PLAYTYPE_BACK);
		gamemode = 4;
	}
}

//ヘルプ画像読み込み
int LoadHelp2Image()
{
	if ((g_HelpImg2 = LoadGraph("images/help2.png")) == -1) return -1;
}

//ヘルプサウンド読み込み
int LoadHelp2Sounds() {
	if ((ClickHelp2 = LoadSoundMem("sounds/se/Click.wav")) == -1) return -1;
	if ((CursorMoveHelp2 = LoadSoundMem("sounds/se/CursorMove.wav")) == -1) return -1;
}