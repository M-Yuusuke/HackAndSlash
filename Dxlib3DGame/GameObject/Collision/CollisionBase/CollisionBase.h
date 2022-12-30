#pragma once
#include "DxLib.h"
namespace Calculation
{
    /// <summary>
    /// 当たり判定の基底クラス
    /// </summary>
    class CollisionBase
    {
    public:
        CollisionBase();

        /// <summary>
        /// 当たり判定のワールド座標の移動
        /// </summary>
        /// <param name="pos">対象のキャラクターの現在地</param>
        virtual void Move(const VECTOR& pos) = 0;

        /// <summary>
        /// ワールド座標上での開始座標のゲッター
        /// </summary>
        /// <returns>ワールド座標上での開始座標</returns>
        VECTOR GetWorldStart() const { return WorldStart; }

        /// <summary>
        /// ワールド座標上での終了座標のゲッター
        /// </summary>
        /// <returns>ワールド座標上での終了座標</returns>
        VECTOR GetWorldEnd() const { return WorldEnd; }

        /// <summary>
        /// 当たり判定の半径のゲッター
        /// </summary>
        /// <returns>当たり判定の半径</returns>
        float GetRadius()const { return Radius; }

    protected:
        //ローカル開始座標
        VECTOR LocalStart;
        //ローカル終了座標
        VECTOR LocalEnd;
        //ワールド開始座標
        VECTOR WorldStart;
        //ワールド終了座標
        VECTOR WorldEnd;
        //カプセルや球体の半径
        float Radius;
    };
}