#include "SceneManager.h"
#include "../Initialize/Initialize.h"
#include "../Title/Title.h"
#include "../Play/Play.h"
#include "../Result/Result.h"

SceneManager* SceneManager::Instance = nullptr;
Initialize* SceneManager::initialize = nullptr;
Title* SceneManager::title = nullptr;
Play* SceneManager::play = nullptr;
Result* SceneManager::result = nullptr;
SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
    Initialize::DestroyInstance();
    Title::DestroyInstance();
    Play::DestroyInstance();
    Result::DestroyInstance();
    initialize = nullptr;
    title = nullptr;
    play = nullptr;
    result = nullptr;
}

SceneManager* SceneManager::CreateInstance()
{
    if (!Instance)
    {
        Instance = new SceneManager;
        Instance->initialize = Initialize::CreateInstance();
        Instance->title = Title::CreateInstance();
        Instance->play = Play::CreateInstance();
        Instance->result = Result::CreateInstance();
    }
    return Instance;
}

void SceneManager::DestroyInstance()
{
    if (Instance)
    {
        delete Instance;
        Instance = nullptr;
    }
}

SceneBase* SceneManager::NextScene(SceneBase* NowScene)
{
    if (NowScene == initialize)
    {
        return title;
    }    
    if (NowScene == title)
    {
        return play;
    }    
    if (NowScene == play)
    {
        return result;
    }    
    if (NowScene == result || NowScene == nullptr)
    {
        return initialize;
    }

    return nullptr;
}
