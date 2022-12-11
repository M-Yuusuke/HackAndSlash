#include "Rule.h"

Rule* Rule::Instance = nullptr;

Rule::Rule() :
    NowTime(0),
    DeltaTime(0),
    PrevTime(0)
{
}

Rule::~Rule()
{
    NowTime = NULL;
    DeltaTime = NULL;
    PrevTime = NULL;
}

/**
* Ruleのインスタンスを生成する
* @note staticメソッドを内部で使用する際に必要
*/
Rule* Rule::CreateInstance()
{
    if (!Instance)
    {
        Instance = new Rule;
    }
    return Instance;
}

/**
* Ruleの後始末処理
* @detail アプリケーション終了前に呼び出し、ルールクラスが確保した領域と
* ルールクラス自身の解放処理を行う。
*/
void Rule::DestoryInstance()
{
    if (Instance)
    {
        delete Instance;
        Instance = nullptr;
    }
}

void Rule::Initialize()
{
    NowTime = 0;
    DeltaTime = 0;
    PrevTime = 0;
}