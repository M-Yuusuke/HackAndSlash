#pragma once
#include "../CollisionBase/CollisionBase.h"
namespace Calculation
{
    class Sphere : public CollisionBase
    {
    public:
        Sphere() {}
        Sphere(const VECTOR& center, float radius);
        void Move(const VECTOR& pos)override;

        void SetLocalCenter(const VECTOR& pos) { LocalCenter = pos; }
        void SetRadius(const float radius) { Radius = radius; }


        VECTOR GetWorldCenter() const { return WorldCenter; }

    private:
        VECTOR LocalCenter;
        VECTOR WorldCenter;
    };
}


