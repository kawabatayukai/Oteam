#include"DxLib.h"
#include"Title.h"
#include"Ranking.h"

//Title.hで宣言した関数の定義をここに書きます

//変数宣言
int g_TitleImg;		//タイトル画像表示用
int g_TitleWhite[8]={0,0,0,0,0,0,0,0};	//タイトルフォント表示用
int g_TitleBlack[8]={0,0,0,0,0};	//タイトルフォント表示用
int g_TitleCasol;

//サウンド用変数
int TitleBGM;
int Click;
int CursorMove;

//ゲームタイトル描画
void DrawGameTitle(int key, int& gamemode)
{
	if (CheckSoundMem(TitleBGM) == FALSE) {
		PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP, FALSE);
	}
	static int menuNo = 0;
	static int M_PI = 0;
	static int gConeImg = 0;

	//タイトル画像
	DrawGraph(0, 0, g_TitleImg, FALSE);

	/**
	for (int i = 0; i < 4; i++) {
		DrawGraph(920, 395+i*80, g_TitleFont[i], TRUE);

	}*/


	DrawGraph(920, 395,g_TitleWhite[4], TRUE);
	DrawGraph(920, 395 + 80, g_TitleWhite[5], TRUE);
	DrawGraph(920, 395 + 150, g_TitleWhite[6], TRUE);
	DrawGraph(920, 395 + 220, g_TitleWhite[7], TRUE);
	

	//DrawGraph(0, 30, gNumberImg[tempScore % 10], TRUE);

	ChangeNextPlayVolumeSoundMem(180, CursorMove);  //次に流す音量を調整  ～２５５  255が通常
	//メニューカーソルの移動処理
	if (key & PAD_INPUT_DOWN) {
		PlaySoundMem(CursorMove, DX_PLAYTYPE_BACK);
		if (++menuNo > 3)menuNo = 0;
	}
	if (key & PAD_INPUT_UP) {
		PlaySoundMem(CursorMove, DX_PLAYTYPE_BACK);
		if (--menuNo < 0)menuNo = 3;
	}

	
	//　タイトル、メニュー、カーソル画像の表示
	DrawRotaGraph(90, 220 + menuNo * 40, 0.7f, M_PI / 2, gConeImg, TRUE);
	//DrawTriangle(860, 405 + menuNo * 80, 900, 435 + menuNo * 80, 860, 455 + menuNo * 80, 0x00ff00, TRUE);
	DrawGraph(860, 405 + menuNo * 70, g_TitleCasol, TRUE);

		switch (menuNo)
		{
		case 0:
			DrawGraph(920, 395, g_TitleWhite[0], TRUE);
			break;
		case 1:
			DrawGraph(920, 395 + 80, g_TitleWhite[1], TRUE);
			break;
		case 2:
			DrawGraph(920, 395 + 150, g_TitleWhite[2], TRUE);
			break;
		case 3:
			DrawGraph(920, 395 + 220, g_TitleWhite[3], TRUE);
			break;
		}
	

	if (key & PAD_INPUT_B)
	{
		PlaySoundMem(Click, DX_PLAYTYPE_BACK);
		switch (menuNo)
		{
		case 0:
			StopSoundMem(TitleBGM);
			LoadTitleSounds();       //もう一度読み込んで　曲最初から始めるようにする
			gamemode = 1;	//ゲームメインに飛ぶ
			break;
		case 1:
			gamemode = 4;	//ヘルプに飛ぶ
			break;
		case 2:
			StopSoundMem(TitleBGM);
			LoadTitleSounds();
			LoadRankingSounds();
			gamemode = 3;	//ランキングに飛ぶ
			break;
		case 3:
			StopSoundMem(TitleBGM);
			LoadTitleSounds();
			gamemode = 7;	//エンドに飛ぶ
			break;
		}
	}

}

//タイトル画像読み込み
int LoadTitleImage()
{
	g_TitleImg = LoadGraph("images/Title/TitleImage.png");
	g_TitleCasol = LoadGraph("images/Title/TitleCasol.png");
	if(LoadDivGraph("images/Title/TitleFont.png",8,1,8,300,69, g_TitleWhite)==-1)return -1;
	return 0;
}

//サウンド読み込み
int LoadTitleSounds() {
	if ((TitleBGM = LoadSoundMem("sounds/bgm/Title.Help.wav")) == -1) return -1;
	if ((Click = LoadSoundMem("sounds/se/Click.wav")) == -1) return -1;
	if ((CursorMove = LoadSoundMem("sounds/se/CursorMove.wav")) == -1) return -1;
}