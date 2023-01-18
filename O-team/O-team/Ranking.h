#pragma once

//ランキング画面のみで使う変数・関数の宣言をここに書きます

//画像変数はshare.hに書いてください

struct RankingData                            // ランキングデータ構造体
{
	int  no;
	char name[11];
	long score;
};

void DrawRanking(int key, int& gamemode);                    //ランキング描画  "KeyFlg"  は　押した瞬間
void InputRanking(int nowkey, int& gamemode, int score);     //ランキング入力  "NowKey"　は　押している間　ﾃﾞｽ

void SortRanking(void);  // ランキングの並べ替え
int SaveRanking(void);   // ランキングデータの保存
int ReadRanking(void);   // ランキングデータの読込

int LoadRankingImage();                        //ランキング画像読み込み


