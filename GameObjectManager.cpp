#include "DxLib.h"
#include "GameObjectManager.h"
#include "GameObjectBase.h"

namespace Calculation
{
    GameObjectManager* GameObjectManager::Instance = nullptr;

    GameObjectManager::~GameObjectManager()
    {
        ReleaseAllObj();
    }

    /**
    * GameObjectManagerのインスタンスを生成する
    * @note staticメソッドを内部で使用する際に必要
    */
    void GameObjectManager::InstanceCreate()
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
    void GameObjectManager::InstanceDestory()
    {
        ReleaseAllObj();
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

        //アクティブオブジェクトないから削除オブジェクトを検索
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
    * 全オブジェクトの更新処理
    * @detail 全オブジェクトのUpdateメソッドを呼んだ後、
    * 新規オブジェクトをアクティブリストに追加
    * 死亡オブジェクトをアクティブリストから削除
    */
    void GameObjectManager::Update(float deltaTime)
    {
        for (auto& tag : ObjectTagAll)
        {
            for (int i = 0; i < Instance->Objects[tag].size(); i++)
            {
                Instance->Objects[tag][i]->Update(deltaTime);
            }
        }
    }

    void GameObjectManager::Draw()
    {
    }

    void GameObjectManager::Collision()
    {
    }

    GameObjectBase* GameObjectManager::GetFirstGameObject(ObjectTag tag)
    {
        return nullptr;
    }


}