#pragma once
#include "SceneBase.h"
class Result : public SceneBase
{
public:
    //シングルトンの生成
    static Result* Create();
    //シングルトンの破棄
    static void Destroy();

    SceneBase* Update(SceneManager* sceneManager)override;
    void Draw()override;

private:
    Result();
    ~Result();
    static Result* Instance;
};

