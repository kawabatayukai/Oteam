#pragma once

//ランキング画面のみで使う変数・関数の宣言をここに書きます

//画像変数はshare.hに書いてください

struct RankingData                            // ランキングデータ構造体
{
	int  no;
	char name[11];
	long score;
};

void DrawRanking(int key, int& gamemode);      //ランキング描画
void InputRanking(int key, int& gamemode, int score);     //ランキング入力

void SortRanking(void);  // ランキングの並べ替え
int SaveRanking(void);   // ランキングデータの保存
int ReadRanking(void);   // ランキングデータの読込

int LoadRankingImage();                        //ランキング画像読み込み


