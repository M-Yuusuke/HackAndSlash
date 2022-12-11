#include "SceneManager.h"
#include "Initialize.h"
#include "Title.h"
#include "Play.h"
#include "Result.h"

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

SceneManager* SceneManager::Create()
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

void SceneManager::Destroy()
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
