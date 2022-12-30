#include "DxLib.h"
#include "Initialize.h"
#include "../SceneManager/SceneManager.h"
#include "../GameObject/GameObjectManager/GameObjectManager.h"
#include "../GameObject/Objects/Player/Player.h"
#include "../GameObject/Objects/Stage/Stage.h"
#include "../GameObject/Objects/Camera/Camera.h"
#include "../GameObject/Objects/Enemy/Mutant/Mutant.h"

Initialize* Initialize::Instance = nullptr;

Initialize::Initialize()
{
    Calculation::GameObjectManager::Entry(new Calculation::Player);
    Calculation::GameObjectManager::Entry(Calculation::Stage::CreateInstance());
    Calculation::GameObjectManager::Entry(Calculation::Camera::CreateInstance());
    Calculation::GameObjectManager::Entry(new Calculation::Mutant);
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
    ClearDrawScreen();
    Calculation::GameObjectManager::Init();
    ScreenFlip();
    return SceneManager::NextScene(this);
}


