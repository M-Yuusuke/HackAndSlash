#include "VectorCalculation.h"

namespace Calculation
{
    //ベクトル同士の加算
    VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
    {
        VECTOR Ret;
        Ret.x = lhs.x + rhs.x;
        Ret.y = lhs.y + rhs.y;
        Ret.z = lhs.z + rhs.z;
        return Ret;
    }
    //ベクトル同士の減算
    VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
    {
        VECTOR Ret;
        Ret.x = lhs.x - rhs.x;
        Ret.y = lhs.y - rhs.y;
        Ret.z = lhs.z - rhs.z;
        return Ret;
    }
    //ベクトルのスカラー倍
    VECTOR operator*(const VECTOR& lhs, float s)
    {
        VECTOR Ret;
        Ret.x = s * lhs.x;
        Ret.y = s * lhs.y;
        Ret.z = s * lhs.z;
        return Ret;
    }

    //ベクトルの加減の複合代入演算子
    VECTOR operator+=(VECTOR lhs, const VECTOR& rhs)
    {
        lhs = lhs + rhs;
        return lhs;
    }

    //ベクトルの減算の複合代入演算子
    VECTOR operator-=(VECTOR lhs, const VECTOR& rhs)
    {
        lhs = lhs - rhs;
        return lhs;
    }

    //ベクトルのスカラー倍の複合代入演算子
    VECTOR operator*=(VECTOR lhs, float s)
    {
        lhs = lhs * s;
        return lhs;
    }

    /**
    * 今向いている方向から向きたい方向への最短の回転方向を調べる(Y軸回転)
    * @param[in] nowVec 今向いている方向
    * @param[in] dirVec 向きたい方向
    * @return float radで回転方向を返す(右回り+1.0、左回りなら-1.0)
    */
    float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec)
    {
        VECTOR Axis;
        //外積演算
        Axis = VCross(nowVec, dirVec);
        if (Axis.y < 0.0f)
        {
            return -1.0f;
        }
        return 1.0f;
    }

    /**
    * nowVecからaimVecに向かってdegreeVelocityの速度でY回転する
    * @param[in] nowVec 今向いている方向
    * @param[in] aimVec 向きたい方向
    * @param[in] degreeVelocity 回転速度
    * @return float radで回転方向を返す
    */
    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity)
    {
        //角速度(度数)をradに変換、右回りか左回りかを調べる
        float RotRad = (DX_PI_F * degreeVelocity / 180.0f);
        RotRad *= CalcRotationDirectionYAxis(nowVec, aimVec);

        //Y軸回転行列を作成する
        MATRIX YRotMat = MGetRotY(RotRad);

        //Y軸回転する
        VECTOR RotVec;
        RotVec = VTransform(nowVec, YRotMat);
        return RotVec;
    }
}

