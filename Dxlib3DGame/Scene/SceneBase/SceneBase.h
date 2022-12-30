#pragma once
#include "DxLib.h"
class Rule;
class SceneBase
{
public:
    SceneBase();
    virtual ~SceneBase();
    virtual SceneBase* Update() = 0;
    virtual void Draw() {};

protected:
    Rule* rule;
    XINPUT_STATE gamePadState;
};

