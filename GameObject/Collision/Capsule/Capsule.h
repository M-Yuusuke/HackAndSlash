#pragma once
#include "../../Collision/CollisionBase/CollisionBase.h"
namespace Calculation
{
    class Capsule : public CollisionBase
    {
    public:
        Capsule() {}
        Capsule(const VECTOR& start, const VECTOR& end, float radius);
        void Move(const VECTOR& pos)override;
    };
}


