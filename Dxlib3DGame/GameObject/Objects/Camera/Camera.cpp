#include "Camera.h"
#include "../../VectorCalculation/VectorCalculation.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../../ObjectTag.h"

namespace Calculation
{
    //Camera* Camera::Instance = nullptr;
    Camera::Camera():
    Calculation::GameObjectBase(ObjectTag::Camera),
    lookPos({0,0,0}),
    cameraOffset({ 0,0,0 }),
    aimCameraPos({ 0,0,0 }),
    aimLookPos({ 0,0,0 })
    {
        cameraOffset = firstCameraPos;
    }

    Camera::~Camera()
    {
    }

    void Camera::Initialize()
    {
        //�J�����̈ʒu���Z�b�g
        pos = firstCameraPos;
        SetCameraNearFar(Near, Far);
        //�J�����̃|�W�V�����̎��_����v���C���[�̈ʒu�̃^�[�Q�b�g������p�x�ɃJ������ݒu
        SetCameraPositionAndTarget_UpVecY(pos, GameObjectManager::GetFirstGameObject(ObjectTag::Player)->GetPos());
    }
    void Camera::Update(float deltaTime)
    {
        GameObjectBase* Player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);
        if (Player)
        {
            aimLookPos = Player->GetPos();
            aimCameraPos = aimLookPos + cameraOffset;

            //�J�����ʒu����ڕW�]�ڌ������x�N�g�����Z�o
            VECTOR LookMoveDir = aimLookPos - lookPos;
            VECTOR PosMoveDir = aimCameraPos - pos;

            //�����_�ƃJ�����ʒu�����X�ɖڕW�n�_�ɋ߂Â���
            lookPos += LookMoveDir * CameraSpringStrength * deltaTime;
            pos += PosMoveDir * CameraSpringStrength * deltaTime;

            SetCameraPositionAndTarget_UpVecY(pos, lookPos);
        }
    }
}