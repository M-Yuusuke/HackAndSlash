#include "DxLib.h"
#include "Initialize.h"
#include "SceneManager.h"
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
    ClearDrawScreen();
    
    ScreenFlip();
    return SceneManager::NextScene(this);
}


