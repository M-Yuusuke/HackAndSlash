#include "DxLib.h"
#include "Title.h"
#include "../SceneManager/SceneManager.h"

Title* Title::Instance = nullptr;

Title::Title()
{
}

Title::~Title()
{
}

Title* Title::CreateInstance()
{
    if (!Instance)
    {
        Instance = new Title;
    }
    return Instance;
}

void Title::DestroyInstance()
{
    delete Instance;
    Instance = nullptr;
}

SceneBase* Title::Update()
{
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        return SceneManager::NextScene(this);
    }
    return this;
}

void Title::Draw()
{
    ClearDrawScreen();
    DrawString(50, 50, "Title\n Start To Space", GetColor(255, 255, 255));
    ScreenFlip();
}


