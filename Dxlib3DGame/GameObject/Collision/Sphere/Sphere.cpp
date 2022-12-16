#include "Sphere.h"
#include "../../VectorCalculation/VectorCalculation.h"

namespace Calculation
{
    //球体の当たり判定コンストラクタ
    Sphere::Sphere(const VECTOR& center, float radius)
    {
        LocalCenter = center;
        WorldCenter = center;
        Radius = radius;
    }

    //球体のワールド座標を移動する
    void Sphere::Move(const VECTOR& pos)
    {
        WorldCenter = LocalCenter + pos;
    }
}