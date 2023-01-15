#include "SceneBase.h"
#include "../SceneManager/SceneManager.h"
#include "../../System/Rule/Rule.h"
#include "../GameObject/WaveManager/WaveManager.h"

SceneBase::SceneBase() :
    sceneManager(SceneManager::CreateInstance()),
    rule(Rule::CreateInstance()),
    waveManager(new WaveManager)
{
}

SceneBase::~SceneBase()
{
    Rule::DestoryInstance();
    rule = nullptr;
}
