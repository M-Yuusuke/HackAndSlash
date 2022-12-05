#include "DxLib.h"
#include "Title.h"
#include "SceneManager.h"

Title* Title::Instance = nullptr;

Title::Title()
{
}

Title::~Title()
{
}

Title* Title::Create()
{
    if (!Instance)
    {
        Instance = new Title;
    }
    return Instance;
}

void Title::Destroy()
{
    delete Instance;
    Instance = nullptr;
}

SceneBase* Title::Update(SceneManager* sceneManager)
{
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        return sceneManager->NextScene(this);
    }
    return this;
}

void Title::Draw()
{
    ClearDrawScreen();
    
    ScreenFlip();
}


