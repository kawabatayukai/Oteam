#pragma once

//ランキング画面のみで使う変数・関数の宣言をここに書きます

//画像変数はshare.hに書いてください

void DrawRanking(int key, int& gamemode);      //ランキング描画
void InputRanking(int key, int& gamemode);     //ランキング入力

int LoadRankingImage();  //ランキング画像読み込み

