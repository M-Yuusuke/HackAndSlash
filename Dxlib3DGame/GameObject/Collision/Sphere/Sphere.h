#pragma once
#include "../CollisionBase/CollisionBase.h"
namespace Calculation
{
    class Sphere : public CollisionBase
    {
    public:
        Sphere() { WorldCenter = { 0, 0, 0 }, LocalCenter = { 0,0,0 } ;}
        Sphere(const VECTOR& center, float radius);
        void Move(const VECTOR& pos)override;

        void SetLocalCenter(const VECTOR& pos) { LocalCenter = pos; WorldCenter = LocalCenter; }
        void SetRadius(const float radius) { Radius = radius; }


        VECTOR GetWorldCenter() const { return WorldCenter; }

    private:
        VECTOR LocalCenter;
        VECTOR WorldCenter;
    };
}


