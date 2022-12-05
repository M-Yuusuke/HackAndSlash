#pragma once
#include "SceneBase.h"
class Play : public SceneBase
{
public:
    //�V���O���g���̐���
    static Play* Create();
    //�V���O���g���̔j��
    static void Destroy();

    SceneBase* Update(SceneManager* sceneManager)override;
    void Draw()override;

private:
    Play();
    ~Play();
    static Play* Instance;

};

