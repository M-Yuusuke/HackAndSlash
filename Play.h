#pragma once
#include "SceneBase.h"
class Play : public SceneBase
{
public:
    //シングルトンの生成
    static Play* Create();
    //シングルトンの破棄
    static void Destroy();

    SceneBase* Update(SceneManager* sceneManager)override;
    void Draw()override;

private:
    Play();
    ~Play();
    static Play* Instance;

};

