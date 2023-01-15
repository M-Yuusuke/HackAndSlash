#pragma once
#include <vector>
#include <unordered_map>
#include "../GameObjectBase/GameObjectBase.h"
#include "../ObjectTag.h" 

namespace Calculation
{
    class GameObjectManager final
    {
    public:
        /// <summary>
        /// このクラスのインスタンス生成
        /// </summary>
        static GameObjectManager* CreateInstance();

        /// <summary>
        /// このクラスのインスタンス破棄
        /// </summary>
        static void DestroyInstance();

        /// <summary>
        /// ゲームオブジェクトの登録
        /// </summary>
        /// <param name="newObj">登録するオブジェクトのポインタ</param>
        static void Entry(GameObjectBase* newObj);
        
        /// <summary>
        /// ゲームオブジェクトの削除
        /// </summary>
        /// <param name="releaseObj">削除するオブジェクトのポインタ</param>
        static void Release(GameObjectBase* releaseObj);

        /// <summary>
        /// 全オブジェクト削除
        /// </summary>
        static void ReleaseAllObj();

        /// <summary>
        /// 登録されているオブジェクトの初期化処理
        /// </summary>
        static void Init();

        /// <summary>
        /// 登録されているオブジェクトの更新処理
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        static void Update(float deltaTime);

        /// <summary>
        /// 描画処理
        /// </summary>
        static void Draw();

        //当たり判定

        /// <summary>
        /// 他のオブジェクトとの当たり判定
        /// </summary>
        static void Collision();

        /// <summary>
        /// 対象のタグの生きている最初のオブジェクト
        /// </summary>
        /// <param name="tag">検索したいオブジェクトのタグ</param>
        /// <returns>対象のタグの一番最初に登録されているオブジェクトのポインタ</returns>
        static GameObjectBase* GetFirstGameObject(ObjectTag tag);

        /// <summary>
        /// 対象のタグの生きているオブジェクトの総数
        /// </summary>
        /// <param name="tag">検索したいオブジェクトのタグ</param>
        /// <returns>対象のタグの総数</returns>
        static int GetObjectSize(ObjectTag tag) { return (int)Instance->Objects[tag].size(); }

    private:
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


