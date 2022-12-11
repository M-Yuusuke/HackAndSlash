#pragma once
#include "DxLib.h"
#include "Sphere.h"
#include "LineSegment.h"
#include "Capsule.h"
//class Sphere;
//class LineSegment;
//class Capsule;

namespace Calculation
{
    /**当たり判定処理を定義するクラス*/
    class Collision
    {
    public:
        //当たり判定の関数組み合わせ
        bool CollisionPair(const Sphere& sphereL, const Sphere& sphereR);
        bool CollisionPair(const LineSegment& line, const Sphere& sphere);
        bool CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& collisionInfo);
        bool CollisionPair(const LineSegment& line,const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo);

        //球体とメッシュとの押し戻し量計算
        VECTOR CalcSpherePushBackVecFormMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo);
    };
}


