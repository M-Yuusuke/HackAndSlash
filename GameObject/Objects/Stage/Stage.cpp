#include "Stage.h"
#include "../../VectorCalculation/VectorCalculation.h"
#include "../../ObjectTag.h"
#include "../../AssetManager/AssetManager.h"
#include "../../GameObjectManager/GameObjectManager.h"

namespace Calculation
{
    Stage* Stage::Instance = nullptr;

    /// <summary>
    /// コンストラクタ（シングルトン）
    /// </summary>
    Stage::Stage():
        GameObjectBase(ObjectTag::Stage)
    {
        pos = StagePos;
        ModelLoad();
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    Stage::~Stage()
    {
        AssetManager::ReleaseMesh(modelHandle);
        AssetManager::ReleaseMesh(collisionModel);
        GameObjectManager::Release(Instance);
        modelHandle = -1;
        collisionModel = -1;
    }

    /// <summary>
    /// Stageクラスのインスタンスを生成
    /// </summary>
    /// <returns>Stageクラスのインスタンスを返す</returns>
    Stage* Stage::CreateInstance()
    {
        if (!Instance)
        {
            Instance = new Stage;
            //ステージをゲームオブジェクトマネージャに登録
            GameObjectManager::Entry(Instance);
        }
        return Instance;
    }

    /// <summary>
    /// Stageクラスのインスタンスを破棄
    /// </summary>
    void Stage::DestoryInstance()
    {
        if (Instance)
        {
            delete Instance;
            Instance = nullptr;
        }
    }

    /// <summary>
    /// モデルの読み込み
    /// </summary>
    void Stage::ModelLoad()
    {
        //表示モデル読み込み&スケーリング&位置セット
        modelHandle = AssetManager::GetMesh("../Data/Assets/Stage/maptest2.mv1");
        MV1SetScale(modelHandle, VGet(1.0f, 1.0f, 1.0f));
        MV1SetPosition(modelHandle, pos);

        //当たり判定モデル読み込み&スケーリング&当たり判定情報構築
        collisionModel = AssetManager::GetMesh("../Data/Assets/Stage/HitMesh2rot.mv1");
        MV1SetScale(collisionModel, VGet(1.0f, 1.0f, 1.0f));
        MV1SetOpacityRate(collisionModel, 0.3f);

        //表示モデルと当たり判定モデルの位置を調整
        MV1SetPosition(collisionModel, pos + VGet(-45, 200, -35));
        MV1SetupCollInfo(collisionModel);
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Stage::Initialize()
    {
        //モデルデータがなかったら読み込む
        if (modelHandle == -1 && collisionModel == -1)
        {
            ModelLoad();
        }
    }

    /// <summary>
    /// 描画処理
    /// </summary>
    void Stage::Draw()
    {
        MV1DrawModel(modelHandle);
        DrawCollider();
    }
}