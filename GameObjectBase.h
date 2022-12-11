#pragma once
#include "DxLib.h"
#include "ObjectTag.h"
#include "CollisionType.h"
#include "LineSegment.h"
#include "Capsule.h"
#include "Sphere.h"

namespace Calculation
{
    /**ゲームオブジェクトの基底クラス*/
    class GameObjectBase
    {
    public:
        //コンストラクタ
        GameObjectBase(ObjectTag tag);
        GameObjectBase(ObjectTag tag, VECTOR pos);
        //デストラクタ
        virtual ~GameObjectBase();

        virtual void Initialize() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Draw() {}

        const VECTOR& GetPos()const { return Pos; }
        void SetPos(const VECTOR vec) { Pos = vec; }

        bool IsVisible()const { return Visible; }
        void SetVisible(bool visible) { Visible = visible; }

        bool IsAlive() const { return Alive; }
        void SetAlive(bool alive) { Alive = alive; }

        ObjectTag GetTag()const { return Tag; }

        //当たり判定関連
        //他のオブジェクトとぶつかったときのリアクション
        virtual void OnCollisionEnter(const GameObjectBase* other) {}
        //このオブジェクトとの当たり判定
        virtual void Collsion(GameObjectBase* other) {}

        //このオブジェクトが持っている当たり判定の種類を取得
        CollisionType GetCollisionType() const { return collisionType; }
        //当たり判定lineを返却
        LineSegment GetCollisionLine() const { return collisionLine; }
        //当たり判定球を返却
        Sphere GetCollisionSphere() const { return collisionSphere; }
        //当たり判定カプセルを返却
        Capsule GetCollisionCapsule() const { return collisionCapsule; }
        //当たり判定モデルを返却
        int GetCollisionModel() const { return CollisionModel; }

    protected:
        //当たり判定位置の更新
        void CollisionUpdate();
        //当たり判定の描画
        void DrawCollider();

        ObjectTag Tag;
        VECTOR Pos;
        int ModelHandle;
        bool Visible;
        bool Alive;

        //当たり判定関連
        CollisionType collisionType;
        LineSegment collisionLine;
        Sphere collisionSphere;
        Capsule collisionCapsule;
        int CollisionModel;
    };
}


