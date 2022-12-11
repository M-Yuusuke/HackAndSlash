#include "Sphere.h"
#include "../../VectorCalculation/VectorCalculation.h"

namespace Calculation
{
    //���̂̓����蔻��R���X�g���N�^
    Sphere::Sphere(const VECTOR& center, float radius)
    {
        LocalCenter = center;
        WorldCenter = center;
        Radius = radius;
    }

    //���̂̃��[���h���W���ړ�����
    void Sphere::Move(const VECTOR& pos)
    {
        WorldCenter = LocalCenter + pos;
    }
}