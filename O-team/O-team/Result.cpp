#include"DxLib.h"
#include"Result.h"


//Result.hで宣言した関数の定義をここに書きます
int g_ResultImg;
int g_FontR[7]={0,0,0,0,0,0,0};		//リザルト
int g_SentakImg;		//選択画像用
int g_Miko[4]={0,0,0,0};		//巫女画像用
int g_kitune;	//狐のお面カーソル用
int page=0;		//ページ移動

//エンド描画
void DrawResult(int key, int& gamemode, int score)
{

	//リザルト画像表示
	DrawGraph(0, 0,g_ResultImg,FALSE);

	static int menuNo=0;

	//リザルト画面から選択画面に移動する用
	if (key & PAD_INPUT_A) {
		page = 1;

	}

	switch(page) {
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
		//DrawTriangle(140 + menuNo * 375, 310, 180 + menuNo * 375, 350, 130 + menuNo * 345, 350, 0x00ff00, TRUE);
		DrawGraph(120+menuNo*355, 290, g_kitune, TRUE);

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


		//巫女さんの画像切り替え
		switch (menuNo)
		{
		case 0:
			DrawGraph(180, 280, g_FontR[3], TRUE);
			DrawRotaGraph(655, 545, 2.5, 0, g_Miko[0], TRUE);
			break;
		case 1:
			DrawGraph(540, 290, g_FontR[4], TRUE);
			DrawRotaGraph(655, 545, 2.5, 0, g_Miko[1], TRUE);
			break;
		case 2:
			DrawGraph(890, 290, g_FontR[5], TRUE);
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
	if ((g_ResultImg = LoadGraph("images/ResultImg.png")) == -1)return -1;	//リザルト画像読込
	if ((g_SentakImg = LoadGraph("images/SentakImg.png")) == -1)return -1;	//選択画面画像読込
	if ((g_kitune = LoadGraph("images/kitsune.png")) == -1)return -1;	//狐のお面画像読込

	if (LoadDivGraph("images/FontResurt.png", 6, 1, 6, 350, 109, g_FontR) == -1)return -1; //フォント画像読込
	if (LoadDivGraph("images/SentakM.png", 3, 3, 1, 64, 64, g_Miko) == -1)return -1;	//巫女さん画像読込

	
	return 0;
}