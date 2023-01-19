#pragma once

//リザルト画面のみで使う変数・関数の宣言をここに書きます

//画像変数も書いてください

void DrawResult(int key,int& gamemode,int score);       //リザルト描画

//選択画面の巫女さん動き
void JampImg();		
void WalkImg();
void SleepImg();

int LoadResultImage();   //リザルト画像読み込み

