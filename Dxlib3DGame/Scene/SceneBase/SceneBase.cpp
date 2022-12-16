#include "SceneBase.h"
#include "../../System/Rule/Rule.h"

SceneBase::SceneBase() :
    rule(Rule::CreateInstance())
{
}

SceneBase::~SceneBase()
{
    Rule::DestoryInstance();
    rule = nullptr;
}
