#pragma once
#include <atlstr.h>
#include <unordered_map>
#include <vector>

namespace Calculation
{
    /// <summary>
    /// モデル・アニメーションの管理を行うクラス
    /// </summary>
    class AssetManager final
    {
    public:
        /// <summary>
        /// インスタンス生成
        /// </summary>
        static void CreateInstance();

        /// <summary>
        /// インスタンス破棄
        /// </summary>
        static void DestroyInstance();

        /// <summary>
        /// メッシュ(モデル)ハンドルの取得
        /// </summary>
        /// <param name="meshFileName">モデルのファイルパス</param>
        /// <returns>メッシュハンドル</returns>
        static int GetMesh(std::string meshFileName);

        /// <summary>
        /// アニメーションハンドルの取得
        /// </summary>
        /// <param name="animationFileName">アニメーションのファイルパス</param>
        /// <returns>アニメーションハンドル</returns>
        static int GetAnimation(std::string animationFileName);

        /// <summary>
        /// メッシュ(モデル)の削除
        /// </summary>
        /// <param name="meshID">削除したいメッシュハンドル</param>
        static void ReleaseMesh(int meshID);

        /// <summary>
        /// 全メッシュ・アニメーションの削除
        /// </summary>
        static void ReleaseAllAsset();

    private:
        //シングルトン
        AssetManager() {}
        ~AssetManager() { ReleaseAllAsset(); }
        static AssetManager* Instance;

        //メッシュ原本(原本として保存だけ行い、Duplicateされたものを返す)
        std::unordered_map<std::string, int> MeshMap;
        //アニメーション原本
        std::unordered_map < std::string, int> AnimationMap;
        //メッシュをコピーしたもの(これを使用する)
        std::vector<int> DuplicatesMesh;
    };
}


