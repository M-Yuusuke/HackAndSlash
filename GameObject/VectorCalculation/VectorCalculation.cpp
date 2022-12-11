#include "VectorCalculation.h"

namespace Calculation
{
    //�x�N�g�����m�̉��Z
    VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
    {
        VECTOR Ret;
        Ret.x = lhs.x + rhs.x;
        Ret.y = lhs.y + rhs.y;
        Ret.z = lhs.z + rhs.z;
        return Ret;
    }
    //�x�N�g�����m�̌��Z
    VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
    {
        VECTOR Ret;
        Ret.x = lhs.x - rhs.x;
        Ret.y = lhs.y - rhs.y;
        Ret.z = lhs.z - rhs.z;
        return Ret;
    }
    //�x�N�g���̃X�J���[�{
    VECTOR operator*(const VECTOR& lhs, float s)
    {
        VECTOR Ret;
        Ret.x = s * lhs.x;
        Ret.y = s * lhs.y;
        Ret.z = s * lhs.z;
        return Ret;
    }

    //�x�N�g���̉����̕���������Z�q
    VECTOR operator+=(VECTOR lhs, const VECTOR& rhs)
    {
        lhs = lhs + rhs;
        return lhs;
    }

    //�x�N�g���̌��Z�̕���������Z�q
    VECTOR operator-=(VECTOR lhs, const VECTOR& rhs)
    {
        lhs = lhs - rhs;
        return lhs;
    }

    //�x�N�g���̃X�J���[�{�̕���������Z�q
    VECTOR operator*=(VECTOR lhs, float s)
    {
        lhs = lhs * s;
        return lhs;
    }

    /**
    * �������Ă����������������������ւ̍ŒZ�̉�]�����𒲂ׂ�(Y����])
    * @param[in] nowVec �������Ă������
    * @param[in] dirVec ������������
    * @return float rad�ŉ�]������Ԃ�(�E���+1.0�A�����Ȃ�-1.0)
    */
    float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec)
    {
        VECTOR Axis;
        //�O�ω��Z
        Axis = VCross(nowVec, dirVec);
        if (Axis.y < 0.0f)
        {
            return -1.0f;
        }
        return 1.0f;
    }

    /**
    * nowVec����aimVec�Ɍ�������degreeVelocity�̑��x��Y��]����
    * @param[in] nowVec �������Ă������
    * @param[in] aimVec ������������
    * @param[in] degreeVelocity ��]���x
    * @return float rad�ŉ�]������Ԃ�
    */
    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity)
    {
        //�p���x(�x��)��rad�ɕϊ��A�E��肩����肩�𒲂ׂ�
        float RotRad = (DX_PI_F * degreeVelocity / 180.0f);
        RotRad *= CalcRotationDirectionYAxis(nowVec, aimVec);

        //Y����]�s����쐬����
        MATRIX YRotMat = MGetRotY(RotRad);

        //Y����]����
        VECTOR RotVec;
        RotVec = VTransform(nowVec, YRotMat);
        return RotVec;
    }
}

