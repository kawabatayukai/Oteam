#include"DxLib.h"
#include"Title.h"

//Title.hで宣言した関数の定義をここに書きます

//変数宣言
int g_TitleImg;

//ゲームタイトル描画
void DrawGameTitle(int key, int& gamemode)
{


	static int menuNo = 0;
	static int M_PI = 0;
	static int gConeImg = 0;

	//タイトル画像
	DrawGraph(0, 0, g_TitleImg, FALSE);

	//メニューカーソルの移動処理
	if (key & PAD_INPUT_DOWN) {
		if (++menuNo > 3)menuNo = 0;
	}
	if (key & PAD_INPUT_UP) {
		if (--menuNo < 0)menuNo = 3;
	}

	//　タイトル、メニュー、カーソル画像の表示
	DrawRotaGraph(90, 220 + menuNo * 40, 0.7f, M_PI / 2, gConeImg, TRUE);
	DrawTriangle(860, 400 + menuNo * 80, 900, 430 + menuNo * 80, 860, 450 + menuNo * 80, 0x00ff00, TRUE);

	if (key & PAD_INPUT_B)
	{
		switch (menuNo)
		{
		case 0:
			gamemode = 1;	//ゲームメインに飛ぶ
			break;
		case 1:
			gamemode = 4;	//ヘルプに飛ぶ
			break;
		case 2:
			gamemode = 3;	//ランキングに飛ぶ
			break;
		case 3:
			gamemode = 7;	//エンドに飛ぶ
			break;
		}
	}

}

//タイトル画像読み込み
int LoadTitleImage()
{
	g_TitleImg = LoadGraph("images/titleimages.png");
	return 0;
}