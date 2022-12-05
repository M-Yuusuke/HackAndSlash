#include "SceneManager.h"
#include "Initialize.h"
#include "Title.h"
#include "Play.h"
#include "Result.h"

SceneManager* SceneManager::Instance = nullptr;
SceneManager::SceneManager() :
    initialize(Initialize::Create()),
    title(Title::Create()),
    play(Play::Create()),
    result(Result::Create())
{
}

SceneManager::~SceneManager()
{
    Initialize::Destroy();
    Title::Destroy();
    Play::Destroy();
    Result::Destroy();
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
    }
    return Instance;
}

void SceneManager::Destroy()
{
    delete Instance;
    Instance = nullptr;
}

SceneBase* SceneManager::NextScene(SceneBase* NowScene) const
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
