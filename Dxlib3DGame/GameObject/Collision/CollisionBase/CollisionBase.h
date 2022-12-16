#pragma once
#include "DxLib.h"
namespace Calculation
{
    class CollisionBase
    {
    public:
        CollisionBase();
        virtual void Move(const VECTOR& pos) = 0;

        VECTOR GetWorldStart() const { return WorldStart; }
        VECTOR GetWorldEnd() const { return WorldEnd; }
        float GetRadius()const { return Radius; }

    protected:
        //���[�J���J�n���W
        VECTOR LocalStart;
        //���[�J���I�����W
        VECTOR LocalEnd;
        //���[���h�J�n���W
        VECTOR WorldStart;
        //���[���h�I�����W
        VECTOR WorldEnd;
        //�J�v�Z���⋅�̂̔��a
        float Radius;
    };
}