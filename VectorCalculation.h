#pragma once
#include <Dxlib.h>

/**演算子オーバーロードを記述した名前空間*/

namespace Calculation
{
    //ベクトル同士の加算
    VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);
    //ベクトル同士の減算
    VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);
    //ベクトルのスカラー倍
    VECTOR operator*(const VECTOR& lhs ,float s);

    //ベクトルの加算の複合代入演算子
    VECTOR operator+=(VECTOR lhs, const VECTOR& rhs);
    //ベクトルの減算の複合代入演算子
    VECTOR operator-=(VECTOR lhs, const VECTOR& rhs);
    //ベクトルのスカラー倍の複合代入演算子
    VECTOR operator*=(VECTOR lhs, float s);

    //今向いている方向から向きたい方向への最短の回転方向を調べる(Y軸回転)
    float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
    //NowVecからAimVecに向かってDegreeVelocityの速度でY回転する
    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);
}