#include"DxLib.h"
#include"Help.h"

//Help.hで宣言した関数の定義をここに書きます
int g_HelpImg;

//サウンド用変数
int ClickHelp;
int CursorMoveHelp;

//ヘルプ画面描画
void DrawHelp(int key, int& gamemode)
{
	// ヘルプ画像表示
	DrawGraph(0, 0, g_HelpImg, FALSE);

	//キー入力は"key",GameModeを変えたいときは"gamemode"を変更します

	//次に流す音量を調整  ～２５５  255が通常
	ChangeNextPlayVolumeSoundMem(220, ClickHelp);
	ChangeNextPlayVolumeSoundMem(200, CursorMoveHelp);
	// B(2)ボタンチェックマスク(Xキー)でメニューに戻る
	if (key & PAD_INPUT_B) {
		PlaySoundMem(ClickHelp, DX_PLAYTYPE_BACK);
		gamemode = 0;
	}

	if (key & PAD_INPUT_RIGHT) {
		PlaySoundMem(CursorMoveHelp, DX_PLAYTYPE_BACK);
		gamemode = 9;
	}

	// 説明表示
//SetFontSize(27);
//DrawString(300, 240, "* タイミングよくジャンプして防具を身につけよう *", 0xffffff, 0);

//DrawString(380, 670, "--- Bボタンを押してタイトルへ戻る ---", 0xffffff, 0);
}

//ヘルプ画像読み込み
int LoadHelpImage()
{
	// ヘルプ画像読込
	if ((g_HelpImg = LoadGraph("images/Help/help1.png")) == -1) return -1;

	return 0;
}

//ヘルプサウンド読み込み
int LoadHelpSounds() {
	if ((ClickHelp = LoadSoundMem("sounds/se/Click.wav")) == -1) return -1;
	if ((CursorMoveHelp = LoadSoundMem("sounds/se/CursorMove.wav")) == -1) return -1;
}