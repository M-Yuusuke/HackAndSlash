#include "DxLib.h"
#include "Play.h"
#include "SceneManager.h"

Play* Play::Instance = nullptr;

Play::Play()
{
}

Play::~Play()
{
}
Play* Play::Create()
{
    if (!Instance)
    {
        Instance = new Play;
    }
    return Instance;
}

void Play::Destroy()
{
    delete Instance;
    Instance = nullptr;
}

SceneBase* Play::Update(SceneManager* sceneManager)
{
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        return sceneManager->NextScene(this);
    }
    return this;
}

void Play::Draw()
{
    ClearDrawScreen();
    
    ScreenFlip();
}