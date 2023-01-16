#pragma once


//飛行物体　のベース（基底クラス）
class Flying_object
{
public:
	//コンストラクタ
	Flying_object(float x, float y, float w, float h, float speed);

	//デストラクタ
	~Flying_object();

	virtual void Update() = 0;   //更新
	virtual void Draw() = 0;     //描画

private:

protected:

	float x;     //ｘ座標
	float y;     //ｙ座標
	const float w;     //幅
	const float h;     //高さ

	float speed; //スピード
};