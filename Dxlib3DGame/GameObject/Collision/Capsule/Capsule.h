#pragma once
#include "../../Collision/CollisionBase/CollisionBase.h"
namespace Calculation
{
    /// <summary>
    /// カプセル状の当たり判定関連の処理を行うクラス
    /// </summary>
    class Capsule : public CollisionBase
    {
    public:
        Capsule() {}
        Capsule(const VECTOR& start, const VECTOR& end, float radius);
        /// <summary>
        /// 当たり判定のワールド座標の移動
        /// </summary>
        /// <param name="pos">対象のキャラクターの現在地</param>
        void Move(const VECTOR& pos)override;

        VECTOR GetWorldStartPos() { return WorldStart; }
        VECTOR GetWorldEndPos() { return WorldStart; }
    };
}


