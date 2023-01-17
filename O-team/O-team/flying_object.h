#pragma once


//飛行物体　のベース（基底クラス）
class Flying_object
{
public:
	//コンストラクタ
	Flying_object(int x, int y, int w, int h, int speed);

	//デストラクタ
	~Flying_object();

	virtual void Update() = 0;   //更新
	virtual void Draw() = 0;     //描画

	bool CheckScreenOut();       //画面外にいるかチェック　true : 画面外　false : 画面内

private:

protected:

	int x;     //ｘ座標
	int y;     //ｙ座標
	const int w;     //幅
	const int h;     //高さ

	int speed; //スピード
};