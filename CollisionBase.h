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
        //ローカル開始座標
        VECTOR LocalStart;
        //ローカル終了座標
        VECTOR LocalEnd;
        //ワールド開始座標
        VECTOR WorldStart;
        //ワールド終了座標
        VECTOR WorldEnd;
        //カプセルや球体の半径
        float Radius;
    };
}