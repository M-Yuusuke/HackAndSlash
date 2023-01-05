#pragma once
#include "DxLib.h"
#include "../ObjectTag.h"
#include "../Collision/CollisionType.h"
#include "../Collision/CollisionFunction/CollisionFunction.h"
#include "../Collision/LineSegment/LineSegment.h"
#include "../Collision/Capsule/Capsule.h"
#include "../Collision/Sphere/Sphere.h"

namespace Calculation
{
    /// <summary>
    /// ゲームオブジェクトの基底クラス
    /// </summary>
    class GameObjectBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="tag">オブジェクトタグ</param>
        GameObjectBase(ObjectTag tag);

        /// <summary>
        /// コンストラクタ（初期位置指定）
        /// </summary>
        /// <param name="tag">オブジェクトタグ</param>
        /// <param name="pos">オブジェクトの初期座標</param>
        GameObjectBase(ObjectTag tag, VECTOR pos);

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~GameObjectBase();

        /// <summary>
        /// 初期化処理（純粋仮想関数）
        /// </summary>
        virtual void Initialize() = 0;
        /// <summary>
        /// 更新処理（純粋仮想関数）
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        virtual void Update(float deltaTime) = 0;
        /// <summary>
        /// 描画処理（仮想関数）
        /// </summary>
        virtual void Draw() {}

        /// <summary>
        /// 位置取得
        /// </summary>
        /// <returns>対象のオブジェクトのポジション</returns>
        const VECTOR& GetPos()const { return pos; }

        /// <summary>
        /// 位置をセット
        /// </summary>
        /// <param name="vec">セットしたいポジション</param>
        void SetPos(const VECTOR vec) { pos = vec; }

        /// <summary>
        /// 可視状態の取得
        /// </summary>
        /// <returns></returns>
        bool IsVisible()const { return visible; }

        /// <summary>
        /// 可視状態のセット
        /// </summary>
        /// <param name="visible"></param>
        void SetVisible(bool visible) { visible = visible; }

        /// <summary>
        /// ゲームオブジェクトが生きているか
        /// </summary>
        /// <returns>ゲームオブジェクトが生きていればtrue、死んでいればfalse</returns>
        bool IsAlive() const { return alive; }

        /// <summary>
        /// ゲームオブジェクトの生死をセット
        /// </summary>
        /// <param name="alive">生きているかどうかのフラグ</param>
        void SetAlive(bool alive) { alive = alive; }

        /// <summary>
        /// オブジェクトタグの取得
        /// </summary>
        /// <returns>オブジェクトタグ</returns>
        ObjectTag GetTag()const { return tag; }

        //当たり判定関連
        
        /// <summary>
        /// 他のオブジェクトと衝突したときのリアクション
        /// </summary>
        /// <param name="other"></param>
        virtual void OnCollisionEnter(const GameObjectBase* other) {}
        
        /// <summary>
        /// このオブジェクトとの当たり判定
        /// </summary>
        /// <param name="other">当たっているオブジェクトのポインタ</param>
        virtual void Collsion(GameObjectBase* other) {}

        /// <summary>
        /// このオブジェクトが持っている当たり判定の種類を取得
        /// </summary>
        /// <returns>当たり判定の種類</returns>
        CollisionType GetCollisionType() const { return collisionType; }

        /// <summary>
        /// 当たり判定線分を取得
        /// </summary>
        /// <returns>LineSegmentのインスタンス</returns>
        LineSegment GetCollisionLine() const { return collisionLine; }

        /// <summary>
        /// 当たり判定球を取得
        /// </summary>
        /// <returns>Sphereのインスタンス</returns>
        Sphere GetCollisionSphere() const { return collisionSphere; }

        /// <summary>
        /// 当たり判定カプセルを取得
        /// </summary>
        /// <returns>Capsuleのインスタンス</returns>
        Capsule GetCollisionCapsule() const { return collisionCapsule; }

        /// <summary>
        /// 当たり判定モデルの取得
        /// </summary>
        /// <returns>collisionModel</returns>
        int GetCollisionModel() const { return collisionModel; }

        /// <summary>
        /// ダメージを受ける処理
        /// </summary>
        virtual void OnDamage() {}

    protected:
        //当たり判定位置の更新
        void CollisionUpdate();

        //当たり判定の描画
        void DrawCollider();

        //オブジェクトの種類を判別するためのタグ
        ObjectTag tag;
        //現在座標
        VECTOR pos;
        //モデルハンドル
        int modelHandle;
        //可視化するか
        bool visible;
        //生きているか
        bool alive;

        //当たり判定関連

        //当たり判定の種類
        CollisionType collisionType;
        //当たり判定関数クラスのインスタンス
        CollisionFunction collisionFunction;
        //線分の当たり判定クラスのインスタンス
        LineSegment collisionLine;
        //球体の当たり判定クラスのインスタンス
        Sphere collisionSphere;
        //カプセルの当たり判定クラスのインスタンス
        Capsule collisionCapsule;
        //メッシュの当たり判定
        int collisionModel;
    };
}


