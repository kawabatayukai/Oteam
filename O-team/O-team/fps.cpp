#include"DxLib.h"
#include"fps.h"

//コンストラクタ
FPSControll::FPSControll(float RefreshRate, int UpdateTime)
{
    Init(RefreshRate, UpdateTime);
}

//初期化
void FPSControll::Init(float RefreshRate, int UpdateTime)
{
    frame_time = (int)(1000.0f / RefreshRate); //1フレームの時間の計算
    update_time = UpdateTime;
    wait_time = 0;
    last_time = now_time = 0;
    count = 0.0f;
    fps = 0.0f;
    last_update = 0;
    //描画関係
    disp_x = 0;
    disp_y = 0;
}

//待ち時間の計算
void FPSControll::Wait()
{
    now_time = GetNowCount();
    wait_time = frame_time - (now_time - last_time);

    //待ち時間があれば
    if (wait_time > 0)
    {
        WaitTimer(wait_time); //指定時間待つ
    }
    last_time = GetNowCount();
}

//FPS値の計算
float FPSControll::Get()
{
    count += 1.0f;
    if (update_time < (last_time - last_update))
    { //アップデート時間になっていれば
        fps = count / (float)(last_time - last_update) * 1000.0f; //FPS値の計算
        last_update = last_time;
        count = 0.0f;
    }
    return (fps);
}

//描画処理
void FPSControll::Disp()
{
    DrawFormatString(disp_x, disp_y, 0xffffff, "fps:%0.1f", fps);
}