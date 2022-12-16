#pragma once
#include "DxLib.h"

class Rule
{
public:
    static Rule* CreateInstance();
    static void DestoryInstance();
    void Initialize();

    //ŽžŠÔŠÖŒWˆ—
    static void SetNowTime() { Instance->NowTime = GetNowCount(); }
    static void SetDeltaTime() { Instance->DeltaTime = (Instance->NowTime - Instance->PrevTime) / 1000.0f; }
    float GetDeltaTime()const { return DeltaTime; }
    static void SetPrevTime() { Instance->PrevTime = Instance->NowTime; }


private:
    Rule();
    ~Rule();
    static Rule* Instance;

    int NowTime;
    float DeltaTime;
    int PrevTime;
};

