#pragma once
#include "CollisionBase.h"
namespace Calculation
{
    class Sphere : public CollisionBase
    {
    public:
        Sphere() {}
        Sphere(const VECTOR& center, float radius);
        void Move(const VECTOR& pos)override;

        VECTOR GetWorldCenter() const { return WorldCenter; }

    private:
        VECTOR LocalCenter;
        VECTOR WorldCenter;
    };
}


