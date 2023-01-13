#include "DxLib.h"
#include "Play.h"
#include "../SceneManager/SceneManager.h"
#include "../../GameObject/VectorCalculation/VectorCalculation.h"
#include "../../GameObject/GameObjectManager/GameObjectManager.h"
#include "../../System/Rule/Rule.h"
#include "../GameObject/WaveManager/WaveManager.h"
#include "../System/UI/PlayerUI/PlayerUI.h"

Play* Play::Instance = nullptr;

Play::Play():
    playerUI(new PlayerUI)
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
    waveManager->Update();
    Calculation::GameObjectManager::Collision();
    playerUI->Update();
    rule->SetPrevTime();
    return this;
}

void Play::Draw()
{
    ClearDrawScreen();
    Calculation::GameObjectManager::Draw();
    //HPƒQ[ƒW‚ÆEXPƒQ[ƒW‚Ì•`‰æ
    playerUI->Draw();
    ScreenFlip();
}