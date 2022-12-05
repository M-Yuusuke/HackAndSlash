#pragma once
#include "SceneBase.h"
class Title : public SceneBase
{
public:
    //シングルトンの生成
    static Title* Create();
    //シングルトンの破棄
    static void Destroy();

    SceneBase* Update(SceneManager* sceneManager)override;
    void Draw()override;

private:
    Title();
    ~Title();
    static Title* Instance;
};

