#pragma once
#include "DxLib.h"
class Rule;
class WaveManager;
class SceneBase
{
public:
    SceneBase();
    virtual ~SceneBase();
    virtual SceneBase* Update() = 0;
    virtual void Draw() {};

protected:
    Rule* rule;
    WaveManager* waveManager;
    XINPUT_STATE gamePadState;
};

