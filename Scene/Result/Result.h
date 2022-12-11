#pragma once
#include "../SceneBase/SceneBase.h"

class Result : public SceneBase
{
public:
    //シングルトンの生成
    static Result* CreateInstance();
    //シングルトンの破棄
    static void DestroyInstance();

    SceneBase* Update()override;
    void Draw()override;

private:
    Result();
    ~Result();
    static Result* Instance;
};

