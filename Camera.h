#pragma once
#include "DxLib.h"
#include "GameObjectBase.h"

namespace Calculation 
{
    class Camera : public GameObjectBase
    {
    public:
        static Camera* CreateInstance();
        static void DestroyInstance();

        void Initialize()override;
        void Update(float deltaTime) override;

    private:
        Camera();
        ~Camera();
        static Camera* Instance;

        const float CameraSpringStrength = 2.0f;
        const float CameraYPos = 500;
        const float CameraZPos = -500;
        //�`�拗���̉���
        const float Near = 10.0f;
        //�`�拗���̏��
        const float Far = 3000.0f;

        //�J�����̒��ړ_
        VECTOR LookPos;
        //�v���C���[����̑��Έʒu
        VECTOR CameraOffset;
        //�J�����ڕW�ʒu
        VECTOR AimCameraPos;
        //�J�������ړ_�ڕW
        VECTOR AimLookPos;

    };
}


