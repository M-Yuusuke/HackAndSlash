#pragma once
#include "../GameObject/GameObjectBase/GameObjectBase.h"
#include "../GameObject/AnimationController/AnimationController.h"
namespace Calculation
{
    class CharacterBase : public GameObjectBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        CharacterBase(ObjectTag tag);
        CharacterBase(ObjectTag tag, VECTOR pos);

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~CharacterBase() {}

    protected:
        /// <summary>
        /// モデルとアニメーションの読み込み
        /// </summary>
        virtual void ModelLoad() = 0;
        /// <summary>
        /// 移動処理
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        virtual void Move(float deltaTime) = 0;
        /// <summary>
        /// 回転処理
        /// </summary>
        void Rotate();

        /// <summary>
        /// プレイヤーとステージの当たり判定
        /// </summary>
        /// <param name="other">当たっているオブジェクトのポインタ</param>
        void OnCollisionStage(const GameObjectBase* other);

        //回転速度
        const float RotateVelocity = 10.0f;
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
        //回転中かどうか
        bool rotateNow;
    };
}