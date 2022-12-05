#include "Capsule.h"
#include "VectorCalculation.h"
namespace Calculation
{
    //�J�v�Z���̓����蔻��R���X�g���N�^
    Capsule::Capsule(const VECTOR& start, const VECTOR& end, float radius)
    {
        LocalStart = start;
        LocalEnd = end;
        WorldStart = start;
        WorldEnd = end;
    }

    //�J�v�Z���̃��[���h���W���ړ�����
    void Capsule::Move(const VECTOR& pos)
    {
        WorldStart = LocalStart + pos;
        WorldEnd = LocalEnd + pos;
    }
}