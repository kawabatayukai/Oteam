#pragma once

//リザルト画面のみで使う変数・関数の宣言をここに書きます

//画像変数も書いてください

void DrawResult(int key,int& gamemode,int score);       //エンド描画
void DrawSentaku();										//エンド画面

int LoadResultImage();   //エンド画像読み込み