#pragma once
#include <vector>
#include <unordered_map>
#include "GameObjectBase.h"
#include "ObjectTag.h" 

//class GameObjectBase;
//class ObjectTag;

namespace Calculation
{
    class GameObjectManager final
    {
    public:
        //このインスタンス生成
        static void CreateInstance();
        //このインスタンス破棄
        static void DestoryInstance();
        //ゲームオブジェクトの登録
        static void Entry(GameObjectBase* newObj);
        //ゲームオブジェクトの削除
        static void Release(GameObjectBase* releaseObj);
        //全オブジェクト削除
        static void ReleaseAllObj();

        static void Init();
        static void Update(float deltaTime);
        static void Draw();

        //当たり判定
        void Collision();
        static GameObjectBase* GetFirstGameObject(ObjectTag tag);

    private:
        //シングルトン
        GameObjectManager() {}
        ~GameObjectManager() { ReleaseAllObj(); }
        //マネージャーのインスタンス
        static GameObjectManager* Instance;

        //一時待機オブジェクト
        std::vector<GameObjectBase*> PendingObjects;
        //Objects　[タグ][オブジェクト個数]
        std::unordered_map<ObjectTag, std::vector<GameObjectBase*>> Objects;
    };
}


