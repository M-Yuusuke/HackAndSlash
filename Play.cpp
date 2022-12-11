#include "DxLib.h"
#include "Play.h"
#include "SceneManager.h"
#include "VectorCalculation.h"
#include "GameObjectManager.h"
#include "Rule.h"

Play* Play::Instance = nullptr;

Play::Play()
{
}

Play::~Play()
{
}
Play* Play::CreateInstance()
{
    if (!Instance)
    {
        Instance = new Play;
    }
    return Instance;
}

void Play::DestroyInstance()
{
    delete Instance;
    Instance = nullptr;
}

SceneBase* Play::Update()
{
    rule->SetNowTime();
    rule->SetDeltaTime();
    Calculation::GameObjectManager::Update(rule->GetDeltaTime());
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        return SceneManager::NextScene(this);
    }
    rule->SetPrevTime();
    return this;
}

void Play::Draw()
{
    ClearDrawScreen();
    Calculation::GameObjectManager::Draw();
    ScreenFlip();
}