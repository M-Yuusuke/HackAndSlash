#pragma once
#include "SceneBase.h"
//class SceneManager;
class Initialize : public SceneBase
{
public:
    //シングルトンの生成
    static Initialize* CreateInstance();
    //シングルトンの破棄
    static void DestroyInstance();

    SceneBase* Update()override;

private:
    Initialize();
    ~Initialize();
    //シングルトン
    static Initialize* Instance;
};

