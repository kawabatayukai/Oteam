#include"DxLib.h"
#include"flying_object.h"

//コンストラクタ
Flying_object::Flying_object(float x, float y, float w, float h, float speed)
	: x(x), y(y), w(w), h(h), speed(speed)
{
	//　↑　初期化指定子で変数を初期化してます
}

//デストラクタ
Flying_object::~Flying_object()
{

}