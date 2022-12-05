#include "DxLib.h"
#include "Result.h"
#include "SceneManager.h"

Result* Result::Instance = nullptr;
Result::Result()
{
}

Result::~Result()
{
}

Result* Result::Create()
{
    if (!Instance)
    {
        Instance = new Result;
    }
    return Instance;
}

void Result::Destroy()
{
    delete Instance;
    Instance = nullptr;
}

SceneBase* Result::Update(SceneManager* sceneManager)
{
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        return sceneManager->NextScene(this);
    }
    return this;
}

void Result::Draw()
{
    ClearDrawScreen();
    
    ScreenFlip();
}


