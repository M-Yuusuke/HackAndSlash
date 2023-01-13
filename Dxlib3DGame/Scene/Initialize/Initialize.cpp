#include "DxLib.h"
#include "Initialize.h"
#include "../SceneManager/SceneManager.h"
#include "../GameObject/GameObjectManager/GameObjectManager.h"
#include "../GameObject/Objects/Player/Player.h"
#include "../GameObject/Objects/Stage/Stage.h"
#include "../GameObject/Objects/Camera/Camera.h"
#include "../GameObject/Objects/Enemy/Mutant/Mutant.h"
#include "../../System/Rule/Rule.h"
#include "../GameObject/WaveManager/WaveManager.h"

Initialize* Initialize::Instance = nullptr;

Initialize::Initialize()
{

}

Initialize::~Initialize()
{

}

Initialize* Initialize::CreateInstance()
{
    if (!Instance)
    {
        Instance = new Initialize;
    }
    return Instance;
}

void Initialize::DestroyInstance()
{
    if (Instance)
    {
        delete Instance;
        Instance = nullptr;
    }
}

SceneBase* Initialize::Update()
{
    Calculation::GameObjectManager::Entry(new Calculation::Player);
    Calculation::GameObjectManager::Entry(new Calculation::Stage);
    Calculation::GameObjectManager::Entry(new Calculation::Camera);
    waveManager->Initialize();

    Calculation::GameObjectManager::Init();
    rule->SetNowTime();
    rule->SetDeltaTime();
    rule->SetPrevTime();
    return SceneManager::NextScene(this);
}


