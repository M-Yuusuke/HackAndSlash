#pragma once
#include <atlstr.h>
#include <unordered_map>
#include <vector>

namespace Calculation
{
    class AssetManager final
    {
    public:
        //インスタンス生成
        static void CreateInstance();
        //インスタンス破棄
        static void DestroyInstance();
        //メッシュ(モデル)の取得
        static int GetMesh(std::string meshFileName);
        //アニメーションの取得
        static int GetAnimation(std::string animationFileName);
        //メッシュ(モデル)の削除
        static void ReleaseMesh(int meshID);
        //全メッシュ・アニメーションの削除
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


