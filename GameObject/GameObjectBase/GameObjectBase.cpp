#include "GameObjectBase.h"
#include "../AssetManager/AssetManager.h"

namespace Calculation
{
    /**
    * ゲームオブジェクトベースコンストラクタ(位置指定無し)
    * @param[in] tag オブジェクトの種類
    */
    GameObjectBase::GameObjectBase(ObjectTag tag) :
        Tag(tag),
        Pos(),
        ModelHandle(-1),
        Visible(true),
        Alive(true),
        collisionType(),
        collisionLine(),
        collisionSphere(),
        collisionCapsule(),
        CollisionModel(-1)
    {
    }

    /**
    * ゲームオブジェクトベースコンストラクタ(位置指定有り)
    * @param[in] tag オブジェクトの種類
    * @param[in] pos オブジェクトの位置
    */
    GameObjectBase::GameObjectBase(ObjectTag tag, VECTOR pos):
        Tag(tag),
        Pos(pos),
        ModelHandle(-1),
        Visible(true),
        Alive(true),
        collisionType(),
        collisionLine(),
        collisionSphere(),
        collisionCapsule(),
        CollisionModel(-1)
    {
    }

    /**ゲームオブジェクトデストラクタ*/
    GameObjectBase::~GameObjectBase()
    {
        if (ModelHandle != -1)
        {
            //コリジョン情報の後始末
            MV1TerminateCollInfo(CollisionModel);
            //モデルデータの後始末
            //AssetManager::ReleaseMesh(ModelHandle);
            ModelHandle = -1;
        }
    }

    /**
    * 当たり判定の更新処理
    * @detail オブジェクトが移動したときには当たり判定位置もそれに合わせて更新する必要がある。
    * 当たり判定がモデル(メッシュ)の場合、ポリゴンごとの当たり判定情報を再構築するため、呼び出し回数を減らす工夫が必要。
    * その他の当たり判定は毎フレーム呼び出しても問題ない。
    */
    void GameObjectBase::CollisionUpdate()
    {
        collisionSphere.Move(Pos);
        collisionLine.Move(Pos);
        collisionCapsule.Move(Pos);

        //モデルの当たり判定情報を再構築
        if (CollisionModel != -1)
        {
            MV1SetPosition(CollisionModel, Pos);
            MV1SetupCollInfo(CollisionModel);
        }
    }

    //コライダーの描画
    void GameObjectBase::DrawCollider()
    {
        DrawLine3D(collisionLine.GetWorldStart(), collisionLine.GetWorldEnd(), GetColor(0, 0, 0));
        DrawSphere3D(collisionSphere.GetWorldCenter(), collisionSphere.GetRadius(), 8, GetColor(255, 0, 0), GetColor(0, 0, 0), FALSE);
        DrawCapsule3D(collisionCapsule.GetWorldStart(), collisionCapsule.GetWorldEnd(), collisionCapsule.GetRadius(), 8, GetColor(0, 255, 0), GetColor(0, 0, 0),FALSE);
        //コリジョンモデルが存在していたら半透明描画
        if (CollisionModel != -1)
        {
            //半透明にする
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            MV1DrawModel(CollisionModel);
            //元に戻す
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        }
    }
}