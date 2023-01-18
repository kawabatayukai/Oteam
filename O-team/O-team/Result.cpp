#include"DxLib.h"
#include"Result.h"


//Result.hで宣言した関数の定義をここに書きます
int g_ResultImg;
int g_FontR[7]={0,0,0,0,0,0,0};		//リザルト
int g_SentakImg;
int g_Miko[4]={0,0,0,0};		//巫女画像用
int page=1;		//ページ移動

//エンド描画
void DrawResult(int key, int& gamemode, int score)
{


	/*ClearDrawScreen();


	SetDrawScreen(DX_SCREEN_BACK);//巫女さんが被ってるのでどうにかする

	ScreenFlip();*/

	//リザルト画像表示
	DrawGraph(0, 0,g_ResultImg,FALSE);

	static int menuNo=0;

	if (key & PAD_INPUT_A) {
		page = 1;

	}


	switch(page) {
	case 0:
		//リザルト画像表示
		DrawGraph(0, 0, g_ResultImg, FALSE);

		SetFontSize(46);//フォントサイズ設定
		//スコア表示
		DrawFormatString(830, 310, 0xffffff, "%d", score);

		break;

	case 1://選択画面
		DrawGraph(0, 0, g_SentakImg, FALSE);
		DrawRotaGraph(655, 545,2.5,0, g_Miko[1],TRUE);

		//メニューカーソルの表示
		DrawTriangle(180 + menuNo * 375, 280, 220 + menuNo * 375, 310, 180 + menuNo * 375, 320, 0x00ff00, TRUE);

		DrawGraph(180, 280, g_FontR[0], TRUE);
		DrawGraph(540, 290, g_FontR[1], TRUE);
		DrawGraph(880, 290, g_FontR[2], TRUE);



		//メニューカーソルの移動処理
		if (key & PAD_INPUT_RIGHT) {
			if (++menuNo > 2)menuNo = 0;
		}
		if (key & PAD_INPUT_LEFT) {
			if (--menuNo < 0)menuNo = 2;
		}

		switch (menuNo)
		{
		case 0:
			DrawRotaGraph(655, 545, 2.5, 0, g_Miko[0], TRUE);

			ClearDrawScreen();
			break;
		case 1:
			DrawRotaGraph(655, 545, 2.5, 0, g_Miko[1], TRUE);
			break;
		case 2:
			DrawRotaGraph(655, 545, 2.5, 0, g_Miko[2], TRUE);
			break;
		}

		if (key & PAD_INPUT_B)
		{
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
	if ((g_ResultImg = LoadGraph("images/ResultImg.png")) == -1)return -1;
	if ((g_SentakImg = LoadGraph("images/SentakImg.png")) == -1)return -1;

	if (LoadDivGraph("images/FontResurt.png", 6, 1, 6, 350, 109, g_FontR) == -1)return -1;

	if (LoadDivGraph("images/SentakM.png", 3, 3, 1, 64, 64, g_Miko) == -1)return -1;

	
	return 0;
}