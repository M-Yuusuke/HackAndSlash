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
        //(0,80,-200)の視点から(0,80,0)のターゲットを見る角度にカメラを設置
        SetCameraPositionAndTarget_UpVecY(VGet(0, 80, -200), VGet(0, 80, 0));
        Instance->Pos = VGet(0, Instance->CameraYPos, Instance->CameraZPos);
        SetCameraNearFar(Instance->Near, Instance->Far);
        //ゲームオブジェクトマネージャーにカメラを登録
        Calculation::GameObjectManager::Entry(Instance);
    }
    void Camera::Update(float deltaTime)
    {
        GameObjectBase* Player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);
        if (Player)
        {
            AimLookPos = Player->GetPos();
            AimCameraPos = AimLookPos + CameraOffset;

            //カメラ位置から目標転移向かうベクトルを算出
            VECTOR LookMoveDir = AimLookPos - LookPos;
            VECTOR PosMoveDir = AimCameraPos - Pos;

            //注視点とカメラ位置を徐々に目標地点に近づける
            LookPos += LookMoveDir * CameraSpringStrength * deltaTime;
            Pos += PosMoveDir * CameraSpringStrength * deltaTime;

            SetCameraPositionAndTarget_UpVecY(Pos, LookPos);
        }
    }

}