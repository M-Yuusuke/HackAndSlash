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
        //カメラの位置をセット
        pos = firstCameraPos;
        SetCameraNearFar(Near, Far);
        //カメラのポジションの視点からプレイヤーの位置のターゲットを見る角度にカメラを設置
        SetCameraPositionAndTarget_UpVecY(pos, GameObjectManager::GetFirstGameObject(ObjectTag::Player)->GetPos());
    }
    void Camera::Update(float deltaTime)
    {
        GameObjectBase* Player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);
        if (Player)
        {
            aimLookPos = Player->GetPos();
            aimCameraPos = aimLookPos + cameraOffset;

            //カメラ位置から目標転移向かうベクトルを算出
            VECTOR LookMoveDir = aimLookPos - lookPos;
            VECTOR PosMoveDir = aimCameraPos - pos;

            //注視点とカメラ位置を徐々に目標地点に近づける
            lookPos += LookMoveDir * CameraSpringStrength * deltaTime;
            pos += PosMoveDir * CameraSpringStrength * deltaTime;

            SetCameraPositionAndTarget_UpVecY(pos, lookPos);
        }
    }
}