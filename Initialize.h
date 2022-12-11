#pragma once
#include "SceneBase.h"
//class SceneManager;
class Initialize : public SceneBase
{
public:
    //�V���O���g���̐���
    static Initialize* CreateInstance();
    //�V���O���g���̔j��
    static void DestroyInstance();

    SceneBase* Update()override;

private:
    Initialize();
    ~Initialize();
    //�V���O���g��
    static Initialize* Instance;
};

