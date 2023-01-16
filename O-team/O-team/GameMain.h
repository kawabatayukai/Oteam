#pragma once

// 更新・計算 と 描画  の処理を分けると良いです

void GameMain_Init();    //ゲームメイン初期処理（コンストラクタの代わり）
void GameMain_Update();  //ゲームメイン更新・計算
void GameMain_Draw();    //ゲームメイン描画

void GameMain();         //ゲームメイン