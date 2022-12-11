#pragma once
#include "DxLib.h"

class Rule
{
public:
    static Rule* CreateInstance();
    static void DestoryInstance();
    void Initialize();

    //時間関係処理
    void SetNowTime() { NowTime = GetNowCount(); }
    void SetDeltaTime() { DeltaTime = (NowTime - PrevTime) / 1000.0f; }
    float GetDeltaTime()const { return DeltaTime; }
    void SetPrevTime() { PrevTime = NowTime; }


private:
    Rule();
    ~Rule();
    static Rule* Instance;

    int NowTime;
    float DeltaTime;
    int PrevTime;
};

