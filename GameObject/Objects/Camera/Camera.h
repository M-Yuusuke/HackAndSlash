#pragma once
#include "../../GameObjectBase/GameObjectBase.h"

namespace Calculation 
{
    /// <summary>
    /// カメラ関連処理を行うクラス
    /// </summary>
    class Camera : public GameObjectBase
    {
    public:
        /// <summary>
        /// Cameraクラスのインスタンス生成
        /// </summary>
        /// <returns>Cameraクラスのインスタンス</returns>
        static Camera* CreateInstance();

        /// <summary>
        /// Cameraクラスのインスタンス破棄
        /// </summary>
        static void DestroyInstance();

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Initialize()override;

        /// <summary>
        /// 更新処理
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime) override;

    private:
        /// <summary>
        /// コンストラクタ（シングルトン）
        /// </summary>
        Camera();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Camera();
        //Cameraクラスのインスタンスを保持
        static Camera* Instance;

        //カメラのバネ定数
        const float CameraSpringStrength = 2.0f;
        //カメラの初期座標
        const VECTOR firstCameraPos = { 0,500,-500 };

        //描画距離の下限
        const float Near = 10.0f;
        //描画距離の上限
        const float Far = 3000.0f;

        //カメラの注目点
        VECTOR lookPos;
        //プレイヤーからの相対位置
        VECTOR cameraOffset;
        //カメラ目標位置
        VECTOR aimCameraPos;
        //カメラ注目点目標
        VECTOR aimLookPos;

    };
}


