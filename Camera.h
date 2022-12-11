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
        //描画距離の下限
        const float Near = 10.0f;
        //描画距離の上限
        const float Far = 3000.0f;

        //カメラの注目点
        VECTOR LookPos;
        //プレイヤーからの相対位置
        VECTOR CameraOffset;
        //カメラ目標位置
        VECTOR AimCameraPos;
        //カメラ注目点目標
        VECTOR AimLookPos;

    };
}


