#include "GameObjectBase.h"
#include "../AssetManager/AssetManager.h"
#include "../VectorCalculation/VectorCalculation.h"

namespace Calculation
{
    /**
    * ゲームオブジェクトベースコンストラクタ(位置指定無し)
    * @param[in] tag オブジェクトの種類
    */
    GameObjectBase::GameObjectBase(ObjectTag tag) :
        tag(tag),
        pos(),
        modelHandle(-1),
        visible(true),
        alive(true),
        collisionType(),
        collisionLine(),
        collisionSphere(),
        collisionCapsule(),
        collisionModel(-1)
    {
    }

    /**
    * ゲームオブジェクトベースコンストラクタ(位置指定有り)
    * @param[in] tag オブジェクトの種類
    * @param[in] pos オブジェクトの位置
    */
    GameObjectBase::GameObjectBase(ObjectTag tag, VECTOR pos):
        tag(tag),
        pos(pos),
        modelHandle(-1),
        visible(true),
        alive(true),
        collisionType(),
        collisionLine(),
        collisionSphere(),
        collisionCapsule(),
        collisionModel(-1)
    {
    }

    /**ゲームオブジェクトデストラクタ*/
    GameObjectBase::~GameObjectBase()
    {
        if (modelHandle != -1)
        {
            //コリジョン情報の後始末
            MV1TerminateCollInfo(collisionModel);
            //モデルデータの後始末
            AssetManager::ReleaseMesh(modelHandle);
            modelHandle = -1;
        }
    }

    /**
    * 当たり判定の更新処理
    * @detail オブジェクトが移動したときには当たり判定位置もそれに合わせて更新する必要がある。
    * 当たり判定がモデル(メッシュ)の場合、ポリゴンごとの当たり判定情報を再構築するため、呼び出し回数を減らす工夫が必要。
    * その他の当たり判定は毎フレーム呼び出しても問題ない。
    */

    /// <summary>
    /// 押し戻し
    /// </summary>
    /// <param name="pushBack">押し戻すベクトル</param>
    void GameObjectBase::PushBack(VECTOR pushBack)
    {
        pos -= pushBack;
        MV1SetPosition(modelHandle, pos);
    }
    void GameObjectBase::CollisionUpdate()
    {
        collisionSphere.Move(pos);
        collisionLine.Move(pos);
        collisionCapsule.Move(pos);

        //モデルの当たり判定情報を再構築
        if (collisionModel != -1)
        {
            MV1SetPosition(collisionModel, pos);
            MV1SetupCollInfo(collisionModel);
        }
    }

    //コライダーの描画
    void GameObjectBase::DrawCollider()
    {
        //DrawLine3D(collisionLine.GetWorldStart(), collisionLine.GetWorldEnd(), GetColor(0, 0, 0));
        //DrawSphere3D(collisionSphere.GetWorldCenter(), collisionSphere.GetRadius(), 8, GetColor(255, 0, 0), GetColor(0, 0, 0), FALSE);
        //DrawCapsule3D(collisionCapsule.GetWorldStart(), collisionCapsule.GetWorldEnd(), collisionCapsule.GetRadius(), 8, GetColor(0, 255, 0), GetColor(0, 0, 0),FALSE);
        ////コリジョンモデルが存在していたら半透明描画
        //if (collisionModel != -1)
        //{
        //    //半透明にする
        //    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        //    MV1DrawModel(collisionModel);
        //    //元に戻す
        //    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        //}
    }
}