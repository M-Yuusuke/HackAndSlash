#include "CollisionFunction.h"
#include "../../VectorCalculation/VectorCalculation.h"

namespace Calculation
{
    /**
    * 球同士の当たり判定
    * @return 衝突している場合にはtrueを返す
    */
    bool CollisionFunction::CollisionPair(const Sphere& sphereL, const Sphere& sphereR)
    {
        return HitCheck_Sphere_Sphere(sphereL.GetWorldCenter(),sphereL.GetRadius(), sphereR.GetWorldCenter(), sphereR.GetRadius());
    }

    /**
    * 線分と球の当たり判定
    * @return 衝突している場合にはtrueを返す
    */
    bool CollisionFunction::CollisionPair(const LineSegment& line, const Sphere& sphere)
    {
        return HitCheck_Line_Sphere(line.GetWorldStart(), line.GetWorldEnd(), sphere.GetWorldCenter(), sphere.GetRadius());
    }

    /**
    * 球とメッシュの当たり判定
    * @return 衝突している場合にはtrueを返す
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
    * 線分とメッシュの当たり判定
    * @return 衝突している場合にはtrueを返す
    */
    bool CollisionFunction::CollisionPair(const LineSegment& line, const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo)
    {
        collisionInfo = MV1CollCheck_Line(modelHandle, -1, line.GetWorldStart(), line.GetWorldEnd());
        return collisionInfo.HitFlag;
    }

    /**
    * 球とメッシュのめり込みを計算する
    * @return VECTOR 球がメッシュから離れる向きの移動ベクトルを返す
    */
    VECTOR CollisionFunction::CalcSpherePushBackVecFormMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo)
    {
        //衝突球

        //球中心
        VECTOR MoveCandidate = sphere.GetWorldCenter();
        //球半径
        float Radius = sphere.GetRadius();
        //ポリゴン平面法線
        VECTOR PlaneNormal;
        //移動ベクトル
        VECTOR MoveVec = VGet(0, 0, 0);
        //移動量
        float MoveLen = 0.0f;
        //移動候補
        VECTOR NewCenter = MoveCandidate;
        for (int i = 0; i < collisionInfo.HitNum; i++)
        {
            //衝突ポリゴンの辺
            VECTOR Edge1, Edge2;
            Edge1 = collisionInfo.Dim[i].Position[1] - collisionInfo.Dim[i].Position[0];
            Edge2 = collisionInfo.Dim[i].Position[2] - collisionInfo.Dim[i].Position[0];

            //衝突ポリゴンの辺より、ポリゴン面の法線ベクトルを求める
            PlaneNormal = VCross(Edge1, Edge2);
            PlaneNormal = VNorm(PlaneNormal);

            //球中心にもっとも違いポリゴン平面の点を求める
            VECTOR Distance = MoveCandidate - collisionInfo.Dim[i].Position[0];
            float Dot = VDot(PlaneNormal,Distance);

            //衝突点
            VECTOR HitPos = MoveCandidate - (PlaneNormal * Dot);

            //球がどれぐらいめり込んでいるか
            float Diff = VSize(MoveCandidate - HitPos);

            //めり込んでいる
            if (HitCheck_Sphere_Triangle(MoveCandidate, Radius,
                collisionInfo.Dim[i].Position[0],
                collisionInfo.Dim[i].Position[1],
                collisionInfo.Dim[i].Position[2]) == TRUE)
            {
                //めり込みが解消するまで押し戻す
                VECTOR MoveVec;
                MoveVec = PlaneNormal * Diff;
                MoveCandidate += MoveVec;
            }
        }
        //押し戻し位置の確定
        NewCenter = MoveCandidate;

        //押し戻し量を返す
        return NewCenter - sphere.GetWorldCenter();
    }
}