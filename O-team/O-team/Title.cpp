#include"DxLib.h"
#include"Title.h"

//Title.hで宣言した関数の定義をここに書きます

//ゲームタイトル描画
void DrawGameTitle(int key, int& gamemode)
{
	//キー入力は"key",GameModeを変えたいときは"gamemode"を変更します
	DrawString(0, 0, "test", 0xffffff);
}

//タイトル画像読み込み
int LoadTitleImage()
{
	return 0;
}