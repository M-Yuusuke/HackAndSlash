#include "GameObjectManager.h"

namespace Calculation
{
    GameObjectManager* GameObjectManager::Instance = nullptr;

    /**
    * GameObjectManagerのインスタンスを生成する
    * @note staticメソッドを内部で使用する際に必要
    */
    void GameObjectManager::CreateInstance()
    {
        if (!Instance)
        {
            Instance = new GameObjectManager;
        }
    }

    /**
    * GameObjectManagerの後始末処理
    * @detail アプリケーション終了前に呼び出し、マネージャが確保した領域と
    * マネージャ自身の解放処理を行う。
    */
    void GameObjectManager::DestroyInstance()
    {
        if (Instance)
        {
            delete Instance;
            Instance = nullptr;
        }
    }

    /**
    * GameobjectをManagerに追加
    * @param[in] 新規作成ゲームオブジェクト
    * @detail 新規GameObjectをManagerに追加する
    * 内部で一時保管された後、Updateメソッド内でタグごとに分類され管理される
    */
    void GameObjectManager::Entry(GameObjectBase* newObj)
    {
        Instance->PendingObjects.push_back(newObj);
    }

    /**
    * GameObjectをManagerから削除
    * @param[in] releaseObj 削除したいオブジェクトのポインタ
    * @detail 削除したオブジェクトのポインタをManager内で検索し削除する
    */
    void GameObjectManager::Release(GameObjectBase* releaseObj)
    {
        //ペンディングオブジェクト内から検索
        auto itr = std::find(Instance->PendingObjects.begin(), Instance->PendingObjects.end(), releaseObj);
        if (itr != Instance->PendingObjects.end())
        {
            //見つけたオブジェクトを最後尾に移動してデータを消す
            std::iter_swap(itr, Instance->PendingObjects.end() - 1);
            Instance->PendingObjects.pop_back();

            return;
        }

        //解放するオブジェクトのタグを得る
        ObjectTag tag = releaseObj->GetTag();

        //アクティブオブジェクト内から削除オブジェクトを検索
        itr = std::find(Instance->Objects[tag].begin(), Instance->Objects[tag].end(), releaseObj);
        if (itr != Instance->Objects[tag].end())
        {
            //見つけたオブジェクトを末尾に移動し、削除
            std::iter_swap(itr, Instance->Objects[tag].end() - 1);
            delete Instance->Objects[tag].back();
        }
    }

    //全オブジェクト削除
    void GameObjectManager::ReleaseAllObj()
    {
        //末尾からペンディングオブジェクトを全て削除
        while (!Instance->PendingObjects.empty())
        {
            delete Instance->PendingObjects.back();
        }
        
        //全てのアクティブオブジェクトを削除
        for (auto& tag : ObjectTagAll)
        {
            //末尾から削除
            while (!Instance->Objects[tag].empty())
            {
                delete Instance->Objects[tag].back();
                Instance->Objects[tag].pop_back();
            }
        }
    }

    /**
    * 全オブジェクトの初期化処理
    */
    void GameObjectManager::Init()
    {
        for (auto& tag : ObjectTagAll)
        {
            for (int i = 0; i < Instance->Objects[tag].size(); i++)
            {
                Instance->Objects[tag][i]->Initialize();
            }
        }
    }

    /**
    * 全オブジェクトの更新処理
    * @detail 全オブジェクトのUpdateメソッドを呼んだ後、
    * 新規オブジェクトをアクティブリストに追加
    * 死亡オブジェクトをアクティブリストから削除
    */
    void GameObjectManager::Update(float deltaTime)
    {
        //全てのアクターの更新
        for (auto& tag : ObjectTagAll)
        {
            //該当タグにある全てのオブジェクトを更新
            for (int i = 0; i < Instance->Objects[tag].size(); i++)
            {
                Instance->Objects[tag][i]->Update(deltaTime);
            }
        }
        //ペンディング中のオブジェクトをアクティブリストに追加
        for (auto pending : Instance->PendingObjects)
        {
            ObjectTag tag = pending->GetTag();
            Instance->Objects[tag].emplace_back(pending);
        }
        Instance->PendingObjects.clear();

        //全てのアクター内で死んでいるアクターをDeadObjectへ一時保管
        std::vector<GameObjectBase*> DeadObjects;
        for (auto& tag : ObjectTagAll)
        {
            for (int i = 0; i < Instance->Objects[tag].size(); i++)
            {
                if (!Instance->Objects[tag][i]->IsAlive())
                {
                    DeadObjects.emplace_back(Instance->Objects[tag][i]);
                }
            }
        }

        //死んでいるオブジェクトを削除
        for (auto& DeadObj : DeadObjects)
        {
            delete DeadObj;
        }
        DeadObjects.clear();
    }

    //全オブジェクトの描画処理
    void GameObjectManager::Draw()
    {
        for (auto& tag : ObjectTagAll)
        {
            for (int i = 0; i < Instance->Objects[tag].size(); i++)
            {
                if (Instance->Objects[tag][i]->IsAlive())
                {
                    Instance->Objects[tag][i]->Draw();
                }
            }
        }
    }

    //全オブジェクトの当たり判定
    void GameObjectManager::Collision()
    {
        //プレイヤーとエネミーの当たり判定
        for (int enemynum = 0; enemynum < Instance->Objects[ObjectTag::Enemy].size(); enemynum++)
        {
            Instance->Objects[ObjectTag::Player][0]->OnCollisionEnter(Instance->Objects[ObjectTag::Enemy][enemynum]);
        }

        //プレイヤーとステージの当たり判定
        for (int bgnum = 0; bgnum < Instance->Objects[ObjectTag::Stage].size(); bgnum++)
        {
            Instance->Objects[ObjectTag::Player][0]->OnCollisionEnter(Instance->Objects[ObjectTag::Stage][bgnum]);
        }
    }

    /**
    * 指定タグの最初のオブジェクトを返す
    * @param[in] tag ObjectTagの種類
    */
    GameObjectBase* GameObjectManager::GetFirstGameObject(ObjectTag tag)
    {
        if (Instance->Objects[tag].size() == 0)
        {
            return nullptr;
        }
        return Instance->Objects[tag][0];
    }
}