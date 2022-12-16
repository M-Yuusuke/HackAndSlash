#pragma once
#include "../SceneBase/SceneBase.h"

class Title : public SceneBase
{
public:
    //シングルトンの生成
    static Title* CreateInstance();
    //シングルトンの破棄
    static void DestroyInstance();

    SceneBase* Update()override;
    void Draw()override;

private:
    Title();
    ~Title();
    static Title* Instance;
};

