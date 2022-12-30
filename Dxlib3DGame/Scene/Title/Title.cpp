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
    GetJoypadXInputState(DX_INPUT_PAD1, &gamePadState);
    if (CheckHitKey(KEY_INPUT_SPACE) || gamePadState.Buttons[13])
    {
        return SceneManager::NextScene(this);
    }
    return this;
}

void Title::Draw()
{
    ClearDrawScreen();
    DrawString(50, 50, "Title\n Start To Space or B", GetColor(255, 255, 255));
    ScreenFlip();
}


