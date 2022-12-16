#pragma once
#include "../GameObject/GameObjectBase/GameObjectBase.h"
#include "../GameObject/AnimationController/AnimationController.h"

namespace Calculation
{
    /// <summary>
    /// Player関連処理を行うクラス
    /// </summary>
    class Player : public GameObjectBase
    {
    public:
        /// <summary>
        /// Playerクラスのインスタンス生成
        /// </summary>
        /// <returns>Playerクラスのインスタンス</returns>
        static Player* CreateInstance();

        /// <summary>
        /// Playerクラスのインスタンス破棄
        /// </summary>
        static void DestoryInstance();

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Initialize()override;

        /// <summary>
        /// 更新処理
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime)override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw()override;

        /// <summary>
        /// 当たり判定処理
        /// </summary>
        /// <param name="other">当たっているオブジェクトのポインタ</param>
        void OnCollisionEnter(const GameObjectBase* other)override;

    private:
        /// <summary>
        /// コンストラクタ（シングルトン）
        /// </summary>
        Player();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Player();
        /// <summary>
        /// モデルの読み込み
        /// </summary>
        void ModelLoad();

        /// <summary>
        /// 入力処理
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Move(float deltaTime);

        /// <summary>
        /// 回転処理
        /// </summary>
        void Rotate();

        //Playerクラスのインスタンスを保持
        static Player* Instance;

        //プレイヤーの大きさ
        //const VECTOR PlayerScale = { 0.8f,0.8f, 0.8f };
        const VECTOR PlayerScale = { 0.01f,0.01f, 0.01f };
        //球の初期ローカル座標
        const VECTOR firstLocalPos = { 0, 50.0f, 0 };
        //足元判定の線分の始点
        const VECTOR LineStart = { 0, 20.0f, 0 };
        //足元判定の線分の終点
        const VECTOR LineEnd = { 0, -30.0f, 0 };

        //球状の当たり判定の半径
        const float Radius = 30.0f;
        //入力ベクトルの最小値
        const float InputVecMin = 0.5f;
        //移動速度
        const float MoveVelocity = 200.0f;
        //回転速度
        const float RotateVelocity = 10.0f;

        //ゲームパッド入力状態
        XINPUT_STATE gamePadState;
        //向き
        VECTOR dir;
        //目標向き
        VECTOR aimDir;
        //速度
        VECTOR velocity;

        //アニメーション管理用
        AnimationController* animControl;
        //アニメーション種類ID
        int animTypeID;

        //回転中か
        bool rotateNow;
    };
}