#pragma once
#include <Dxlib.h>

/// <summary>
/// 演算子オーバーロードを記述した名前空間
/// </summary>
namespace Calculation
{    /// <summary>
    /// ベクトル同士の合成
    /// </summary>
    /// <param name="lhs">合成したいベクトル1</param>
    /// <param name="rhs">合成したいベクトル2</param>
    /// <returns>合成後のベクトル</returns>
    VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);

    /// <summary>
    /// ベクトル同士の分解
    /// </summary>
    /// <param name="lhs">分解したいベクトル1</param>
    /// <param name="rhs">分解したいベクトル2</param>
    /// <returns>分解後のベクトル</returns>
    VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);

    /// <summary>
    /// ベクトルのスカラー倍
    /// </summary>
    /// <param name="lhs">スカラー倍したいベクトル</param>
    /// <param name="s">スカラー倍する係数</param>
    /// <returns>スカラー倍後のベクトル</returns>
    VECTOR operator*(const VECTOR& lhs ,float s);

    /// <summary>
    /// ベクトルの加算の複合代入演算子
    /// </summary>
    /// <param name="lhs">合成したいベクトル1</param>
    /// <param name="rhs">合成したいベクトル2</param>
    /// <returns>合成後のベクトル</returns>
    VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

    /// <summary>
    /// ベクトルの減算の複合代入演算子
    /// </summary>
    /// <param name="lhs">分解したいベクトル1</param>
    /// <param name="rhs">分解したいベクトル2</param>
    /// <returns>分解後のベクトル</returns>
    VECTOR operator-=(VECTOR& lhs, const VECTOR& rhs);

    /// <summary>
    /// ベクトルのスカラー倍の複合代入演算子
    /// </summary>
    /// <param name="lhs">スカラー倍したいベクトル</param>
    /// <param name="s">スカラー倍する係数</param>
    /// <returns>スカラー倍後のベクトル</returns>
    VECTOR operator*=(VECTOR& lhs, float s);

    /// <summary>
    /// 2つのベクトルの角度はほぼ同じか
    /// </summary>
    /// <param name="lhs"> 調査したいベクトル1 </param>
    /// <param name="rhs"> 調査したいベクトル2 </param>
    /// <returns>2つのベクトルの角度がほぼ同じであればtrue 異なればfalseを返す</returns>
    bool IsNearAngle(const VECTOR& lhs, const VECTOR& rhs);

    /// <summary>
    /// 今向いている方向から向きたい方向への最短の回転方向を調べる(Y軸回転)
    /// </summary>
    /// <param name="nowVec">今向いている方向</param>
    /// <param name="dirVec">向きたい方向</param>
    /// <returns>最短の回転方向</returns>
    float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);

    /// <summary>
    /// //NowVecからAimVecに向かってDegreeVelocityの速度でY回転する
    /// </summary>
    /// <param name="nowVec">今向いている方向</param>
    /// <param name="aimVec">向きたい方向</param>
    /// <param name="degreeVelocity">回転速度</param>
    /// <returns>回転方向</returns>
    VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);

    //内積の最大値
    const float dotMax = 0.99f;
}