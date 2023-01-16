#include"DxLib.h"
#include"flying_object.h"

//コンストラクタ
Flying_object::Flying_object(int x, int y, int w, int h, int speed)
	: x(x), y(y), w(w), h(h), speed(speed)
{
	//　↑　初期化指定子で変数を初期化してます
}

//デストラクタ
Flying_object::~Flying_object()
{

}

//画面外にいるかチェック　true : 画面外　false : 画面内
bool Flying_object::CheckScreenOut()
{
	// x が 0より小さい　または　1280より大きい
	if (x < -10) return true;
	if (y < -10 || y > 730) return true;

	//それ以外は画面内
	return false;
}

