#pragma once
#include "SceneBase.h"
class Title : public SceneBase
{
public:
    //�V���O���g���̐���
    static Title* Create();
    //�V���O���g���̔j��
    static void Destroy();

    SceneBase* Update(SceneManager* sceneManager)override;
    void Draw()override;

private:
    Title();
    ~Title();
    static Title* Instance;
};

