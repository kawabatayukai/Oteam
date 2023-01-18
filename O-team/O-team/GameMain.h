#pragma once

// 更新・計算(Update) と 描画(Draw)  の処理を分けると良いです

void GameMain_Init();    //ゲームメイン初期処理（コンストラクタの代わり）
void GameMain_Final();   //ゲームメイン終了処理（デストラクタの代わり）

void Armor_Update();     //防具  生成・更新・削除
void Attack_Update();    //攻撃  生成・更新・削除

void GameMain_Update();  //ゲームメイン更新・計算
void GameMain_Draw();    //ゲームメイン描画

void GameMain(int &gamemode);         //ゲームメイン

//ターン
enum class Turn
{
	CATCH,     //防具をとるターン
	ATTACK,    //攻撃に耐えるターン
	END,       //30秒時間切れ or プレイヤーが死亡した時
};