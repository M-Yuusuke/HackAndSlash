#include "Camera.h"
#include "VectorCalculation.h"
#include "GameObjectManager.h"

namespace Calculation
{
    Camera* Camera::Instance = nullptr;
    Camera::Camera():
    Calculation::GameObjectBase(ObjectTag::Camera),
    LookPos(VGet(0, 0, 0)),
    CameraOffset(VGet(0,0,0)),
    AimCameraPos(VGet(0, 0, 0)),
    AimLookPos(VGet(0, 0, 0))
    {
    }

    Camera::~Camera()
    {
    }

    Camera* Camera::CreateInstance()
    {
        if (!Instance)
        {
            Instance = new Camera;
        }
        return Instance;
    }
    void Camera::DestroyInstance()
    {
        if (Instance)
        {
            delete Instance;
            Instance = nullptr;
        }
    }

    void Camera::Initialize()
    {
        //(0,80,-200)�̎��_����(0,80,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
        SetCameraPositionAndTarget_UpVecY(VGet(0, 80, -200), VGet(0, 80, 0));
        Instance->Pos = VGet(0, Instance->CameraYPos, Instance->CameraZPos);
        SetCameraNearFar(Instance->Near, Instance->Far);
        //�Q�[���I�u�W�F�N�g�}�l�[�W���[�ɃJ������o�^
        Calculation::GameObjectManager::Entry(Instance);
    }
    void Camera::Update(float deltaTime)
    {
        GameObjectBase* Player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);
        if (Player)
        {
            AimLookPos = Player->GetPos();
            AimCameraPos = AimLookPos + CameraOffset;

            //�J�����ʒu����ڕW�]�ڌ������x�N�g�����Z�o
            VECTOR LookMoveDir = AimLookPos - LookPos;
            VECTOR PosMoveDir = AimCameraPos - Pos;

            //�����_�ƃJ�����ʒu�����X�ɖڕW�n�_�ɋ߂Â���
            LookPos += LookMoveDir * CameraSpringStrength * deltaTime;
            Pos += PosMoveDir * CameraSpringStrength * deltaTime;

            SetCameraPositionAndTarget_UpVecY(Pos, LookPos);
        }
    }

}