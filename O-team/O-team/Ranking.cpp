#include"DxLib.h"
#include"Ranking.h"
#include"Keyboard.h"

#define RANKING_DATA 5    // ランキング上位５人 

//Ranking.hで宣言した関数の定義をここに書きます
int g_RankingImg;   // ランキング画像

struct RankingData g_Ranking[RANKING_DATA];    // ランキングデータの変数宣言

//ランキング描画
void DrawRanking(int key, int& gamemode)
{
	//キー入力は"key",GameModeを変えたいときは"gamemode"を変更します
	// スペースキーでメニューに戻る
	if (key & PAD_INPUT_B) gamemode = 0;

	// ランキング画像表示
	DrawGraph(0, 0, g_RankingImg, FALSE);

	// ランキング一覧を表示
	SetFontSize(40);
	for (int i = 0; i < RANKING_DATA; i++)
	{
		DrawFormatString(450, 200 + i * 86, 0xffffff, "%-10s  %10d",g_Ranking[i].name, g_Ranking[i].score);
	}

	SetFontSize(30);
	//DrawString(350, 650, "--- Bボタンを押してタイトルへ戻る ---", 0xffffff, 0);
}

//ランキング入力
void InputRanking(int nowkey, int& gamemode, int score)
{
	//キー入力は"key",GameModeを変えたいときは"gamemode"を変更します
	// ランキング画像表示
	DrawGraph(0, 0, g_RankingImg, FALSE);

	// フォントサイズの設定
	SetFontSize(20);

	// 名前入力指示文字列の描画
	DrawString(150, 240, "ランキングに登録します", 0xFFFFFF);
	DrawString(150, 270, "名前を英字で入力してください", 0xFFFFFF);

	//// 名前の入力
	//DrawString(150, 310, "> ", 0xFFFFFF);
	//DrawBox(160, 305, 300, 335, 0x000055, TRUE);
	//if (KeyInputSingleCharString(170, 310, 10, g_Ranking[RANKING_DATA - 1].name, FALSE) == 1)
	//{
	//	g_Ranking[RANKING_DATA - 1].score = score;   // ランキングデータにスコアを登録
	//	SortRanking();                               // ランキング並べ替え
	//	SaveRanking();                               // ランキングデータの保存
	//	gamemode = 3;                                // ゲームモードの変更
	//}

	//　　↓　一文字でも入力された状態で"OK"を押すと、"1"が返ってくる
	if (KeyBoard_PushB(nowkey, g_Ranking[RANKING_DATA - 1].name) == 1)
	{
		g_Ranking[RANKING_DATA - 1].score = score;   // ランキングデータにスコアを登録
		SortRanking();                               // ランキング並べ替え
		SaveRanking();                               // ランキングデータの保存
		gamemode = 3;                                // ゲームモードの変更
	}
	else    //入力完了していない時
	{
		KeyBoard_Draw();                             //キーボードの描画
		KeyBoard_Update(nowkey);                        //キーボードの更新・操作

		//DrawString(0, 0, "背景・キーボード・カーソルの色などは変更できます", 0xffffff);
	}
}

/******************************************
 * ランキング並べ替え
 ******************************************/
void SortRanking(void)
{
	int i, j;
	RankingData work;

	// 選択法ソート
	for (i = 0; i < RANKING_DATA - 1; i++)
	{
		for (j = i + 1; j < RANKING_DATA; j++)
		{
			if (g_Ranking[i].score <= g_Ranking[j].score)
			{
				work = g_Ranking[i];
				g_Ranking[i] = g_Ranking[j];
				g_Ranking[j] = work;
			}
		}
	}
	// 順位付け
	for (i = 0; i < RANKING_DATA; i++)
	{
		g_Ranking[i].no = 1;
	}
	// 得点が同じ場合は、同じ順位とする
	// 同順位があった場合の次の順位はデータ個数が加算された順位とする
	for (i = 0; i < RANKING_DATA - 1; i++)
	{
		for (j = i + 1; j < RANKING_DATA; j++)
		{
			if (g_Ranking[i].score > g_Ranking[j].score)
			{
				g_Ranking[j].no++;
			}
		}
	}
}

/***********************************************
 * ランキングデータの保存
 ***********************************************/
int  SaveRanking(void)
{
	FILE* fp;
#pragma warning(disable:4996)

	// ファイルオープン
	if ((fp = fopen("dat/rankingdata.txt", "w")) == NULL)
	{
		/* エラー処理 */
		printf("Ranking Data Error\n");
		return -1;
	}

	// ランキングデータ分配列データを書き込む
	for (int i = 0; i < RANKING_DATA; i++)
	{
		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	// ファイルクローズ
	fclose(fp);

	return 0;

}

/*************************************
 * ランキングデータ読み込み
 *************************************/
int ReadRanking(void)
{
	FILE* fp;
#pragma warning(disable:4996)

	// ファイルオープン
	if ((fp = fopen("dat/rankingdata.txt", "r")) == NULL)
	{
		// エラー処理
		printf("Ranking Data Error\n");
		return -1;
	}

	// ランキングデータ配分列データを読み込む
	for (int i = 0; i < RANKING_DATA; i++)
	{
		int dammy = fscanf(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
	}

	// ファイルクローズ
	fclose(fp);

	return 0;
}

//ランキング画像読み込み
int LoadRankingImage()
{
	// ランキング画像読込
	if ((g_RankingImg = LoadGraph("images/input.png")) == -1) return -1;

	//キーボード画像読込
	if (LoadKeyBoardImgaes() == -1) return -1;

	return 0;
}