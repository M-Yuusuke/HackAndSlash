#pragma once
#include "../SceneBase/SceneBase.h"

class Play : public SceneBase
{
public:
    //シングルトンの生成
    static Play* CreateInstance();
    //シングルトンの破棄
    static void DestroyInstance();

    SceneBase* Update()override;
    void Draw()override;

private:
    Play();
    ~Play();
    static Play* Instance;

};

