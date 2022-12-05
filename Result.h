#pragma once
#include "SceneBase.h"
class Result : public SceneBase
{
public:
    //�V���O���g���̐���
    static Result* Create();
    //�V���O���g���̔j��
    static void Destroy();

    SceneBase* Update(SceneManager* sceneManager)override;
    void Draw()override;

private:
    Result();
    ~Result();
    static Result* Instance;
};

