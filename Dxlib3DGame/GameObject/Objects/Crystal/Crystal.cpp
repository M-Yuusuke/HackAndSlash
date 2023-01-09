#include "Crystal.h"
#include "../GameObject/AssetManager/AssetManager.h"

namespace Calculation
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Crystal::Crystal(VECTOR pos):
        GameObjectBase(ObjectTag::Crystal, pos)
    {
        ModelLoad();
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    Crystal::~Crystal()
    {
    }

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">1フレームの経過時間</param>
    void Crystal::Update(float deltaTime)
    {
    }

    /// <summary>
    /// 描画処理
    /// </summary>
    void Crystal::Draw()
    {
        MV1DrawModel(modelHandle);
    }

    /// <summary>
    /// 当たり判定処理
    /// </summary>
    /// <param name="other">衝突検知をしたいオブジェクト</param>
    void Crystal::OnCollisionEnter(GameObjectBase* other)
    {
        ObjectTag tag = other->GetTag();
        if (ObjectTag::Player == tag)
        {
            //プレイヤーと衝突した場合の処理
        }
    }

    /// <summary>
    /// モデル読み込み
    /// </summary>
    void Crystal::ModelLoad()
    {
        //モデルロード
        modelHandle = AssetManager::GetMesh("../Data/Assets/EXP/Model.mv1");

        //そのままだとステージに対してモデルが大きいので縮小
        MV1SetScale(modelHandle, Scale);
        //モデルを配置
        MV1SetPosition(modelHandle, pos);
    }
}