#pragma once
#include "DxLib.h"
#include "../CollisionBase/CollisionBase.h"
namespace Calculation
{
    class LineSegment : public CollisionBase
    {
    public:
        LineSegment() {}
        LineSegment(const VECTOR& start, const VECTOR& end);
        void Move(const VECTOR& pos) override;
    };
}


