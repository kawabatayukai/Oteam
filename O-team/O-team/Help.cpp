#include"DxLib.h"
#include"Help.h"

//Help.hで宣言した関数の定義をここに書きます

//ヘルプ画面描画
void DrawHelp(int key, int& gamemode)
{
	//キー入力は"key",GameModeを変えたいときは"gamemode"を変更します
	DrawString(30, 30, "help", 0xffffff);
}

//ヘルプ画像読み込み
int LoadHelpImage()
{
	return 0;
}