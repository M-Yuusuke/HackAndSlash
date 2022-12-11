#include "DxLib.h"
#include "Result.h"
#include "../SceneManager/SceneManager.h"

Result* Result::Instance = nullptr;
Result::Result()
{
}

Result::~Result()
{
}

Result* Result::CreateInstance()
{
    if (!Instance)
    {
        Instance = new Result;
    }
    return Instance;
}

void Result::DestroyInstance()
{
    delete Instance;
    Instance = nullptr;
}

SceneBase* Result::Update()
{
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        return SceneManager::NextScene(this);
    }
    return this;
}

void Result::Draw()
{
    ClearDrawScreen();
    
    ScreenFlip();
}


