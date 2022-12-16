#include "CollisionFunction.h"
#include "../../VectorCalculation/VectorCalculation.h"

namespace Calculation
{
    /**
    * �����m�̓����蔻��
    * @return �Փ˂��Ă���ꍇ�ɂ�true��Ԃ�
    */
    bool CollisionFunction::CollisionPair(const Sphere& sphereL, const Sphere& sphereR)
    {
        return HitCheck_Sphere_Sphere(sphereL.GetWorldCenter(),sphereL.GetRadius(), sphereR.GetWorldCenter(), sphereR.GetRadius());
    }

    /**
    * �����Ƌ��̓����蔻��
    * @return �Փ˂��Ă���ꍇ�ɂ�true��Ԃ�
    */
    bool CollisionFunction::CollisionPair(const LineSegment& line, const Sphere& sphere)
    {
        return HitCheck_Line_Sphere(line.GetWorldStart(), line.GetWorldEnd(), sphere.GetWorldCenter(), sphere.GetRadius());
    }

    /**
    * ���ƃ��b�V���̓����蔻��
    * @return �Փ˂��Ă���ꍇ�ɂ�true��Ԃ�
    */
    bool CollisionFunction::CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& collisionInfo)
    {
        collisionInfo = MV1CollCheck_Sphere(modelHandle, -1, sphere.GetWorldCenter(), sphere.GetRadius());
        if (collisionInfo.HitNum == 0)
        {
            return false;
        }
        return true;
    }

    /**
    * �����ƃ��b�V���̓����蔻��
    * @return �Փ˂��Ă���ꍇ�ɂ�true��Ԃ�
    */
    bool CollisionFunction::CollisionPair(const LineSegment& line, const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo)
    {
        collisionInfo = MV1CollCheck_Line(modelHandle, -1, line.GetWorldStart(), line.GetWorldEnd());
        return collisionInfo.HitFlag;
    }

    /**
    * ���ƃ��b�V���̂߂荞�݂��v�Z����
    * @return VECTOR �������b�V�����痣�������̈ړ��x�N�g����Ԃ�
    */
    VECTOR CollisionFunction::CalcSpherePushBackVecFormMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo)
    {
        //�Փˋ�

        //�����S
        VECTOR MoveCandidate = sphere.GetWorldCenter();
        //�����a
        float Radius = sphere.GetRadius();
        //�|���S�����ʖ@��
        VECTOR PlaneNormal;
        //�ړ��x�N�g��
        VECTOR MoveVec = VGet(0, 0, 0);
        //�ړ���
        float MoveLen = 0.0f;
        //�ړ����
        VECTOR NewCenter = MoveCandidate;
        for (int i = 0; i < collisionInfo.HitNum; i++)
        {
            //�Փ˃|���S���̕�
            VECTOR Edge1, Edge2;
            Edge1 = collisionInfo.Dim[i].Position[1] - collisionInfo.Dim[i].Position[0];
            Edge2 = collisionInfo.Dim[i].Position[2] - collisionInfo.Dim[i].Position[0];

            //�Փ˃|���S���̕ӂ��A�|���S���ʂ̖@���x�N�g�������߂�
            PlaneNormal = VCross(Edge1, Edge2);
            PlaneNormal = VNorm(PlaneNormal);

            //�����S�ɂ����Ƃ��Ⴂ�|���S�����ʂ̓_�����߂�
            VECTOR Distance = MoveCandidate - collisionInfo.Dim[i].Position[0];
            float Dot = VDot(PlaneNormal,Distance);

            //�Փ˓_
            VECTOR HitPos = MoveCandidate - (PlaneNormal * Dot);

            //�����ǂꂮ�炢�߂荞��ł��邩
            float Diff = VSize(MoveCandidate - HitPos);

            //�߂荞��ł���
            if (HitCheck_Sphere_Triangle(MoveCandidate, Radius,
                collisionInfo.Dim[i].Position[0],
                collisionInfo.Dim[i].Position[1],
                collisionInfo.Dim[i].Position[2]) == TRUE)
            {
                //�߂荞�݂���������܂ŉ����߂�
                VECTOR MoveVec;
                MoveVec = PlaneNormal * Diff;
                MoveCandidate += MoveVec;
            }
        }
        //�����߂��ʒu�̊m��
        NewCenter = MoveCandidate;

        //�����߂��ʂ�Ԃ�
        return NewCenter - sphere.GetWorldCenter();
    }
}