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
    for (int i = 0; i < 20; i++)
    {
        Calculation::GameObjectManager::Entry(new Calculation::Mutant(VGet(200 + (GetRand(150) - GetRand(150)), 0, 200 + (GetRand(150) - GetRand(150)))));
    }
    Calculation::GameObjectManager::Entry(new Calculation::Stage);
    Calculation::GameObjectManager::Entry(new Calculation::Camera);
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
    Calculation::GameObjectManager::Init();
    return SceneManager::NextScene(this);
}


