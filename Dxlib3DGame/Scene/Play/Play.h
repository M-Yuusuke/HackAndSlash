#pragma once
#include "../SceneBase/SceneBase.h"

class Play : public SceneBase
{
public:
    //�V���O���g���̐���
    static Play* CreateInstance();
    //�V���O���g���̔j��
    static void DestroyInstance();

    SceneBase* Update()override;
    void Draw()override;

private:
    Play();
    ~Play();
    static Play* Instance;

};
