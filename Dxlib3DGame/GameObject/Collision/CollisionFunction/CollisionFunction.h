#pragma once
#include "../Sphere/Sphere.h"
#include "../LineSegment/LineSegment.h"
#include "../Capsule/Capsule.h"

namespace Calculation
{
    /// <summary>
    /// 当たり判定関数をまとめるクラス
    /// </summary>
    class CollisionFunction
    {
    public:
        //当たり判定の関数組み合わせ
        
        /// <summary>
        /// 球体同士の当たり判定処理
        /// </summary>
        /// <param name="sphereL">球体1</param>
        /// <param name="sphereR">球体2</param>
        /// <returns>衝突していればtrue、していなければfalse</returns>
        bool CollisionPair(const Sphere& sphereL, const Sphere& sphereR);

        /// <summary>
        /// 線分と球体の当たり判定処理
        /// </summary>
        /// <param name="line">線分</param>
        /// <param name="sphere">球体</param>
        /// <returns>衝突していればtrue、していなければfalse</returns>
        bool CollisionPair(const LineSegment& line, const Sphere& sphere);

        /// <summary>
        /// 球体とモデルの当たり判定処理
        /// </summary>
        /// <param name="sphere">球体</param>
        /// <param name="modelHandle">モデルハンドル</param>
        /// <param name="collisionInfo">コリジョン結果代入用ポリゴン配列</param>
        /// <returns>衝突していればtrue、していなければfalse</returns>
        bool CollisionPair(const Sphere& sphere, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& collisionInfo);


        /// <summary>
        /// カプセルとモデルの当たり判定処理
        /// </summary>
        /// <param name="capsule">カプセル</param>
        /// <param name="modelHandle">モデルハンドル</param>
        /// <param name="collisionInfo">コリジョン結果代入用ポリゴン配列</param>
        /// <returns>衝突していればtrue、していなければfalse</returns>
        bool CollisionPair(const Capsule& capsule, const int modelHandle, MV1_COLL_RESULT_POLY_DIM& collisionInfo);



        /// <summary>
        /// 線分とモデルの当たり判定処理
        /// </summary>
        /// <param name="line">線分</param>
        /// <param name="modelHandle">モデルハンドル</param>
        /// <param name="collisionInfo">コリジョン結果代入用ポリゴン配列</param>
        /// <returns>衝突していればtrue、していなければfalse</returns>
        bool CollisionPair(const LineSegment& line,const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo);

        /// <summary>
        /// 球体とメッシュとの押し戻し量計算
        /// </summary>
        /// <param name="sphere">球体</param>
        /// <param name="collisionInfo">コリジョン結果代入用ポリゴン配列</param>
        /// <returns>押し戻し量</returns>
        VECTOR CalcSpherePushBackVecFormMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo);
    };
}


