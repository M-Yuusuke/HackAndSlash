#include "VectorCalculation.h"

namespace Calculation
{
    /// <summary>
    /// ベクトル同士の合成
    /// </summary>
    /// <param name="lhs">合成したいベクトル1</param>
    /// <param name="rhs">合成したいベクトル2</param>
    /// <returns>合成したベクトル</returns>
    VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs)
    {
        VECTOR Ret;
        Ret.x = lhs.x + rhs.x;
        Ret.y = lhs.y + rhs.y;
        Ret.z = lhs.z + rhs.z;
        return Ret;
    }

    /// <summary>
    /// ベクトル同士の分解
    /// </summary>
    /// <param name="lhs">分解したいベクトル1</param>
    /// <param name="rhs">分解したいベクトル2</param>
    /// <returns>分解したベクトル</returns>
    VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs)
    {
        VECTOR Ret;
        Ret.x = lhs.x - rhs.x;
        Ret.y = lhs.y - rhs.y;
        Ret.z = lhs.z - rhs.z;
        return Ret;
    }

    /// <summary>
    /// ベクトルのスカラー倍
    /// </summary>
    /// <param name="lhs">スカラー倍したいベクトル</param>
    /// <param name="s">スカラー倍する係数</param>
    /// <returns>スカラー倍後のベクトル</returns>
    VECTOR operator*(const VECTOR& lhs, float s)
    {
        VECTOR Ret;
        Ret.x = s * lhs.x;
        Ret.y = s * lhs.y;
        Ret.z = s * lhs.z;
        return Ret;
    }

    /// <summary>
    /// ベクトルの加算の複合代入演算子
    /// </summary>
    /// <param name="lhs">合成したいベクトル1</param>
    /// <param name="rhs">合成したいベクトル2</param>
    /// <returns>合成後のベクトル</returns>
    VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs)
    {
        lhs = lhs + rhs;
        return lhs;
    }

    /// <summary>
    /// ベクトルの減算の複合代入演算子
    /// </summary>
    /// <param name="lhs">分解したいベクトル1</param>
    /// <param name="rhs">分解したいベクトル2</param>
    /// <returns>分解後のベクトル</returns>
    VECTOR operator-=(VECTOR& lhs, const VECTOR& rhs)
    {
        lhs = lhs - rhs;
        return lhs;
    }

    /// <summary>
    /// ベクトルのスカラー倍の複合代入演算子
    /// </summary>
    /// <param name="lhs">スカラー倍したいベクトル</param>
    /// <param name="s">スカラー倍する係数</param>
    /// <returns>スカラー倍後のベクトル</returns>
    VECTOR operator*=(VECTOR& lhs, float s)
    {
        lhs = lhs * s;
        return lhs;
    }

    /// <summary>
    /// 2つのベクトルの角度はほぼ同じか
    /// </summary>
    /// <param name="lhs"> 調査したいベクトル1 </param>
    /// <param name="rhs"> 調査したいベクトル2 </param>
    /// <returns>2つのベクトルの角度がほぼ同じであればtrue 異なればfalseを返す</returns>
    bool IsNearAngle(const VECTOR& lhs, const VECTOR& rhs)
    {
        float dot = VDot(lhs, rhs);
        if (dot > dotMax)
        {
            return true;
        }
        return false;
    }

    /// <summary>
    /// 今向いている方向から向きたい方向への最短の回転方向を調べる(Y軸回転)
    /// </summary>
    /// <param name="nowVec">今向いている方向</param>
    /// <param name="dirVec">向きたい方向</param>
    /// <returns>最短の回転方向（右回りなら1.0、左回りなら-1.0）</returns>
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

    /// <summary>
    /// //NowVecからAimVecに向かってDegreeVelocityの速度でY回転する
    /// </summary>
    /// <param name="nowVec">今向いている方向</param>
    /// <param name="aimVec">向きたい方向</param>
    /// <param name="degreeVelocity">回転速度</param>
    /// <returns>回転方向</returns>
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

