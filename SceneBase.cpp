#include "SceneBase.h"
#include "Rule.h"

SceneBase::SceneBase() :
    rule(Rule::CreateInstance())
{
}

SceneBase::~SceneBase()
{
    Rule::DestoryInstance();
    rule = nullptr;
}
