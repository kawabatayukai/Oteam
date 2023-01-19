#include"DxLib.h"
#include"Result.h"


//Result.hで宣言した関数の定義をここに書きます
int g_ResultImg;					//リザルト画像用
int g_FontR[7] = { 0,0,0,0,0,0,0 };		//リザルトフォント用
int g_SentakImg;					//選択画像用
int g_Miko[6] = { 0,0,0,0,0,0 };		//巫女画像用

int g_kitune;	//狐のお面カーソル用
int page = 0;		//ページ移動

int y = 0;			//巫女画像移動用
int gWaitTime = 0;	//巫女画像切り替え用
int check = 0;		//巫女画像切り替え用
int flg = FALSE;	//巫女画像切り替え用

int ResultBGM;
int ClickResult;
int CursorMoveResult;

//エンド描画
void DrawResult(int key, int& gamemode, int score)
{

	ChangeNextPlayVolumeSoundMem(130, ResultBGM);  //次に流す音量を調整  ～２５５  255が通常
	PlaySoundMem(ResultBGM, DX_PLAYTYPE_LOOP, FALSE);

	//リザルト画像表示
	DrawGraph(0, 0, g_ResultImg, FALSE);

	static int menuNo = 0;

	//リザルト画面から選択画面に移動する用
	if (key & PAD_INPUT_4) {
		page = 1;

	}

	switch (page) {
	case 0:
		//リザルト画像表示
		DrawGraph(0, 0, g_ResultImg, FALSE);
		SetFontSize(46);//フォントサイズ設定

		//スコア表示
		DrawFormatString(830, 350, 0xff4040, "%d", score);

		break;

	case 1://選択画面
		DrawGraph(0, 0, g_SentakImg, FALSE);

		//メニューカーソルの表示
		DrawGraph(120 + menuNo * 355, 290, g_kitune, TRUE);

		//フォント画像表示
		DrawGraph(180, 280, g_FontR[0], TRUE);
		DrawGraph(540, 290, g_FontR[1], TRUE);
		DrawGraph(890, 290, g_FontR[2], TRUE);



		//メニューカーソルの移動処理
		if (key & PAD_INPUT_RIGHT) {
			if (++menuNo > 2)menuNo = 0;
		}
		if (key & PAD_INPUT_LEFT) {
			if (--menuNo < 0)menuNo = 2;
		}
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


		//巫女さんの画像切り替え
		switch (menuNo)
		{
		case 0:
			WalkImg();
			DrawGraph(180, 280, g_FontR[3], TRUE);

			check = 0;
			break;
		case 1:
			JampImg();
			DrawGraph(540, 290, g_FontR[4], TRUE);

			check = 0;
			break;
		case 2:
			SleepImg();
			DrawGraph(890, 290, g_FontR[5], TRUE);
			break;
		}



		if (key & PAD_INPUT_B)
		{
		PlaySoundMem(ClickResult, DX_PLAYTYPE_BACK);
		StopSoundMem(ResultBGM);
			switch (menuNo)
			{
			case 0:
				gamemode = 2;	//ゲームメインに飛ぶ
				break;
			case 1:
				gamemode = 0;	//タイトル
				break;
			case 2:
				gamemode = 7;	//エンドに飛ぶ
				break;
			}

		}
		break;
	}
}

//リザルト画像読み込み
int LoadResultImage()
{
	if ((g_ResultImg = LoadGraph("images/Result/Score.png")) == -1)return -1;	//リザルト画像読込
	if ((g_SentakImg = LoadGraph("images/Result/SentakImg.png")) == -1)return -1;	//選択画面画像読込
	if ((g_kitune = LoadGraph("images/Result/kitsune.png")) == -1)return -1;	//狐のお面画像読込

	if (LoadDivGraph("images/Result/FontResurt.png", 6, 1, 6, 350, 109, g_FontR) == -1)return -1; //フォント画像読込
	if (LoadDivGraph("images/Result/SentakM.png", 6, 6, 1, 64, 64, g_Miko) == -1)return -1;	//巫女さん画像読込


	return 0;
}

//巫女さん画像ジャンプ
void JampImg(void)
{

	if (flg == FALSE) {

		DrawRotaGraph(655, 545, 2.5, 0, g_Miko[1], TRUE);

	}

	if (++gWaitTime > 220) {
		flg = TRUE;
		y = -40;

		if (flg == TRUE) {

			DrawRotaGraph(655, 545 + y, 2.5, 0, g_Miko[0], TRUE);

		}
	}

	if (++gWaitTime > 500) {
		flg = FALSE;
		gWaitTime = 0;
	}



}

//巫女さん画像歩き
void WalkImg(void) {
	if (flg == FALSE) {

		DrawRotaGraph(655, 545, 2.5, 0, g_Miko[1], TRUE);

	}

	if (++gWaitTime > 220) {
		flg = TRUE;

		if (flg == TRUE) {

			DrawRotaGraph(655, 545, 2.5, 0, g_Miko[3], TRUE);

		}
	}

	if (++gWaitTime > 500) {
		flg = FALSE;
		gWaitTime = 0;
	}



}

//巫女さん画像倒れる
void SleepImg(void) {

	if (check == 0) {
		flg = FALSE;
		check = 1;
	}


	if (flg == FALSE)
	{
		DrawRotaGraph(655, 545, 2.5, 0, g_Miko[5], TRUE);

		if (++gWaitTime > 420)
		{
			flg = TRUE;
		}
	}


	if (flg == TRUE)
	{
		DrawRotaGraph(655, 545, 2.5, 0, g_Miko[4], TRUE);
	}


	if (++gWaitTime > 500) {
		gWaitTime = 0;
	}

}

int LoadResultSounds() {
	if ((ResultBGM = LoadSoundMem("sounds/bgm/Result.wav")) == -1) return -1;
	if ((ClickResult = LoadSoundMem("sounds/se/Click.wav")) == -1) return -1;
	if ((CursorMoveResult = LoadSoundMem("sounds/se/CursorMove.wav")) == -1) return -1;
}