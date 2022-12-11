#include "LineSegment.h"
#include "../../VectorCalculation/VectorCalculation.h"

namespace Calculation
{
    //線分の当たり判定のコンストラクタ
    LineSegment::LineSegment(const VECTOR& start, const VECTOR& end)
    {
        LocalStart = start;
        LocalEnd = end;
        WorldStart = start;
        WorldEnd = end;
    }

    //線分のワールド座標を移動する
    void LineSegment::Move(const VECTOR& pos)
    {
        WorldStart = LocalStart + pos;
        WorldEnd = LocalEnd + pos;
    }
}