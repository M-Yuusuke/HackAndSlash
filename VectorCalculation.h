#pragma once
#include <Dxlib.h>

/**���Z�q�I�[�o�[���[�h���L�q�������O���*/

namespace Calculation
{
    //�x�N�g�����m�̉��Z
    VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);
    //�x�N�g�����m�̌��Z
    VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);
    //�x�N�g���̃X�J���[�{
    VECTOR operator*(const VECTOR& lhs ,float s);

    //�x�N�g���̉��Z�̕���������Z�q
    VECTOR operator+=(VECTOR lhs, const VECTOR& rhs);
    //�x�N�g���̌��Z�̕���������Z�q
    VECTOR operator-=(VECTOR lhs, const VECTOR& rhs);
    //�x�N�g���̃X�J���[�{�̕���������Z�q
    VECTOR operator*=(VECTOR lhs, float s);

    //�������Ă����������������������ւ̍ŒZ�̉�]�����𒲂ׂ�(Y����])
    float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
    //NowVec����AimVec�Ɍ�������DegreeVelocity�̑��x��Y��]����
    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);
}