#include "Capsule.h"
#include "../../VectorCalculation/VectorCalculation.h"
namespace Calculation
{
    //カプセルの当たり判定コンストラクタ
    Capsule::Capsule(const VECTOR& start, const VECTOR& end, float radius)
    {
        LocalStart = start;
        LocalEnd = end;
        WorldStart = start;
        WorldEnd = end;
        Radius = radius;
    }

    /// <summary>
    /// 当たり判定のワールド座標の移動
    /// </summary>
    /// <param name="pos">対象のキャラクターの現在地</param>
    void Capsule::Move(const VECTOR& pos)
    {
        WorldStart = LocalStart + pos;
        WorldEnd = LocalEnd + pos;
    }
}