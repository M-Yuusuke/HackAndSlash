#pragma once
#include "SceneBase.h"
//class SceneManager;
class Initialize : public SceneBase
{
public:
    //�V���O���g���̐���
    static Initialize* Create();
    //�V���O���g���̔j��
    static void Destroy();

    SceneBase* Update(SceneManager* sceneManager)override;

private:
    Initialize();
    ~Initialize();
    //�V���O���g��
    static Initialize* Instance;
};
