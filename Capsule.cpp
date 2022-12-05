#include "Capsule.h"
#include "VectorCalculation.h"
namespace Calculation
{
    //カプセルの当たり判定コンストラクタ
    Capsule::Capsule(const VECTOR& start, const VECTOR& end, float radius)
    {
        LocalStart = start;
        LocalEnd = end;
        WorldStart = start;
        WorldEnd = end;
    }

    //カプセルのワールド座標を移動する
    void Capsule::Move(const VECTOR& pos)
    {
        WorldStart = LocalStart + pos;
        WorldEnd = LocalEnd + pos;
    }
}