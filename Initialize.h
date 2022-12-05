#pragma once
#include "SceneBase.h"
//class SceneManager;
class Initialize : public SceneBase
{
public:
    //シングルトンの生成
    static Initialize* Create();
    //シングルトンの破棄
    static void Destroy();

    SceneBase* Update(SceneManager* sceneManager)override;

private:
    Initialize();
    ~Initialize();
    //シングルトン
    static Initialize* Instance;
};

