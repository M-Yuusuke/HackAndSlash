#pragma once
class SceneManager;
class SceneBase
{
public:
    SceneBase();
    virtual ~SceneBase();
    virtual SceneBase* Update(SceneManager* sceneManager) = 0;
    virtual void Draw();
};

