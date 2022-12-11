#include "DxLib.h"
#include "Stage.h"
#include "VectorCalculation.h"
#include "ObjectTag.h"
#include "AssetManager.h"
#include "GameObjectManager.h"

namespace Calculation
{
    Stage* Stage::Instance = nullptr;

    Stage::Stage():
        GameObjectBase(ObjectTag::Stage)
    {
        Pos = StagePos;
        ModelLoad();
    }

    Stage::~Stage()
    {
        AssetManager::ReleaseMesh(ModelHandle);
        AssetManager::ReleaseMesh(CollisionModel);
        GameObjectManager::Release(Instance);
        ModelHandle = -1;
        CollisionModel = -1;
    }

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

    void Stage::DestoryInstance()
    {
        if (Instance)
        {
            delete Instance;
            Instance = nullptr;
        }
    }

    /**ステージモデル読み込み*/
    void Stage::ModelLoad()
    {
        //表示モデル読み込み&スケーリング&位置セット
        ModelHandle = AssetManager::GetMesh("../Data/Assets/Stage/maptest2.mv1");
        MV1SetScale(ModelHandle, VGet(1.0f, 1.0f, 1.0f));
        MV1SetPosition(ModelHandle, Pos);

        //当たり判定モデル読み込み&スケーリング&当たり判定情報構築
        CollisionModel = AssetManager::GetMesh("../Data/Assets/Stage/HitMesh2rot.mv1");
        MV1SetScale(CollisionModel, VGet(1.0f, 1.0f, 1.0f));
        MV1SetOpacityRate(CollisionModel, 0.3f);

        //表示モデルと当たり判定モデルの位置を調整
        MV1SetPosition(CollisionModel, Pos + VGet(-45, 200, -35));
        MV1SetupCollInfo(CollisionModel);
    }

    void Stage::Initialize()
    {
        //モデルデータがなかったら読み込む
        if (ModelHandle == -1 && CollisionModel == -1)
        {
            ModelLoad();
        }
    }

    void Stage::Draw()
    {
        MV1DrawModel(ModelHandle);
        DrawCollider();
    }
}