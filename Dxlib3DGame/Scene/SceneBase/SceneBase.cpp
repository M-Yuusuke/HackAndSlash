#include "SceneBase.h"
#include "../../System/Rule/Rule.h"
#include "../GameObject/WaveManager/WaveManager.h"

SceneBase::SceneBase() :
    rule(Rule::CreateInstance()),
    waveManager(new WaveManager)
{
}

SceneBase::~SceneBase()
{
    Rule::DestoryInstance();
    rule = nullptr;
}
