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
    /**�����蔻�菈�����`����N���X*/
    class Collision
    {
    public:
        //�����蔻��̊֐��g�ݍ��킹
        bool CollisionPair(const Sphere& sphereL, const Sphere& sphereR);
        bool CollisionPair(const LineSegment& line, const Sphere& sphere);
        bool CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& collisionInfo);
        bool CollisionPair(const LineSegment& line,const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo);

        //���̂ƃ��b�V���Ƃ̉����߂��ʌv�Z
        VECTOR CalcSpherePushBackVecFormMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo);
    };
}


