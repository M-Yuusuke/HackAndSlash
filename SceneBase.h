#pragma once
class SceneManager;
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
};

