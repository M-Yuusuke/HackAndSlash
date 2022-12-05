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

Initialize* Initialize::Create()
{
    if (!Instance)
    {
        Instance = new Initialize;
    }
    return Instance;
}

void Initialize::Destroy()
{
    delete Instance;
    Instance = nullptr;
}

SceneBase* Initialize::Update(SceneManager* sceneManager)
{
    ClearDrawScreen();
    
    ScreenFlip();
    return sceneManager->NextScene(this);
}


