#include"DxLib.h"
#include"Result.h"


//Result.hで宣言した関数の定義をここに書きます
int g_ResultImg;

int ResultBGM;
int ClickResult;
int CursorMoveResult;

//エンド描画
void DrawResult(int key, int& gamemode, int score)
{
	ChangeNextPlayVolumeSoundMem(130, ResultBGM);  //次に流す音量を調整  ～２５５  255が通常
	PlaySoundMem(ResultBGM, DX_PLAYTYPE_LOOP, FALSE);

	//リザルト画像表示
	DrawGraph(0, 0,g_ResultImg,FALSE);

	static int menuNo=0;

	SetFontSize(46);//フォントサイズ設定
	//スコア表示
	DrawFormatString(830, 310, 0xffffff, "%d", score);

	ChangeNextPlayVolumeSoundMem(180, CursorMoveResult);  //次に流す音量を調整  ～２５５  255が通常
	//メニューカーソルの移動処理
	if (key & PAD_INPUT_RIGHT) {
		PlaySoundMem(CursorMoveResult, DX_PLAYTYPE_BACK);
		if (++menuNo > 2)menuNo = 0;
	}
	if (key & PAD_INPUT_LEFT) {
		PlaySoundMem(CursorMoveResult, DX_PLAYTYPE_BACK);
		if (--menuNo < 0)menuNo = 2;
	}

	if (key & PAD_INPUT_B)
	{
		PlaySoundMem(ClickResult, DX_PLAYTYPE_BACK);
		StopSoundMem(ResultBGM);
		switch (menuNo)
		{
		case 0:
			gamemode = 1;	//ゲームメインに飛ぶ
			break;
		case 1:
			gamemode = 0;	//タイトル
			break;
		case 2:
			gamemode = 7;	//エンドに飛ぶ
			break;
		}
	}

	//メニューカーソルの表示
	DrawTriangle(180 + menuNo * 375, 630, 220+ menuNo * 375, 660 , 180 + menuNo * 375, 680, 0x00ff00, TRUE);

}

//エンド画像読み込み
int LoadResultImage()
{
	if ((g_ResultImg = LoadGraph("images/resurtImg.png")) == -1)return -1;
	return 0;
}

int LoadResultSounds() {
	if ((ResultBGM = LoadSoundMem("sounds/bgm/Result.wav")) == -1) return -1;
	if ((ClickResult = LoadSoundMem("sounds/se/Click.wav")) == -1) return -1;
	if ((CursorMoveResult = LoadSoundMem("sounds/se/CursorMove.wav")) == -1) return -1;
}