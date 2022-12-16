#include "DxLib.h"
#include "Play.h"
#include "../SceneManager/SceneManager.h"
#include "../../GameObject/VectorCalculation/VectorCalculation.h"
#include "../../GameObject/GameObjectManager/GameObjectManager.h"
#include "../../System/Rule/Rule.h"

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
    Calculation::GameObjectManager::Collision();
    rule->SetPrevTime();
    return this;
}

void Play::Draw()
{
    ClearDrawScreen();
    Calculation::GameObjectManager::Draw();
    ScreenFlip();
}