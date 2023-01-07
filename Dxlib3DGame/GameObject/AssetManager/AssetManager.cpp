#include "DxLib.h"
#include "AssetManager.h"
#include "../VectorCalculation/VectorCalculation.h"

namespace Calculation
{
    AssetManager* AssetManager::Instance = nullptr;

    /// <summary>
    /// インスタンス生成
    /// </summary>
    void Calculation::AssetManager::CreateInstance()
    {
        if (!Instance)
        {
            Instance = new AssetManager;
        }
    }

    /// <summary>
    /// インスタンス破棄
    /// </summary>
    void Calculation::AssetManager::DestroyInstance()
    {
        if (Instance)
        {
            delete Instance;
            Instance = nullptr;
        }
    }

    /// <summary>
    /// メッシュ(モデル)ハンドルの取得
    /// </summary>
    /// <param name="meshFileName">モデルのファイルパス</param>
    /// <returns>メッシュハンドル</returns>
    int AssetManager::GetMesh(std::string meshFileName)
    {
        int meshID = 0;
        //連想配列に同じデータが登録されていないかを調べる
        auto iter = Instance->MeshMap.find(meshFileName);

        //見つからなかった場合は読み込みを行い、連想配列に記録する
        if (iter == Instance->MeshMap.end())
        {
            meshID = MV1LoadModel(meshFileName.c_str());
            if (meshID == -1)
            {
                return -1;
            }
            Instance->MeshMap.emplace(meshFileName, meshID);
        }
        //新規読み込みも2回目以降の読み込みも、複製したものを返す
        //メッシュを使うキャラクターが複数いた場合に、原本を消されると全員消えて困るため
        //メッシュのコピー削除用にDuplivateMashに保存
        meshID = MV1DuplicateModel(Instance->MeshMap[meshFileName]);
        Instance->DuplicatesMesh.push_back(meshID);
        return meshID;
    }

    /// <summary>
    /// アニメーションハンドルの取得
    /// </summary>
    /// <param name="animationFileName">アニメーションのファイルパス</param>
    /// <returns>アニメーションハンドル</returns>
    int AssetManager::GetAnimation(std::string animationFileName)
    {
        int animID = 0;
        auto iter = Instance->AnimationMap.find(animationFileName);
        //見つからなかった場合は読み込みを行い、連想配列に記録する
        if (iter == Instance->AnimationMap.end())
        {
            animID = MV1LoadModel(animationFileName.c_str());
            if (animID == -1)
            {
                return -1;
            }
            Instance->AnimationMap.emplace(animationFileName, animID);
        }
        //登録されたアニメーションIDを返す
        return Instance->AnimationMap[animationFileName];
    }

    /// <summary>
    /// メッシュ(モデル)の削除
    /// </summary>
    /// <param name="meshID">削除したいメッシュハンドル</param>
    void AssetManager::ReleaseMesh(int meshID)
    {
        //Duplicateの中のメッシュを検索し、削除
        auto iter = std::find(Instance->DuplicatesMesh.begin(), Instance->DuplicatesMesh.end(), meshID);
        if (iter == Instance->DuplicatesMesh.end())
        {
            //見つからなかった
            return;
        }
        MV1DeleteModel(meshID);
        //末尾のデータと入れ替えて末尾を削除
        std::iter_swap(iter, Instance->DuplicatesMesh.end() - 1);
        Instance->DuplicatesMesh.pop_back();
    }

    /// <summary>
    /// 全メッシュ・アニメーションの削除
    /// </summary>
    void AssetManager::ReleaseAllAsset()
    {
        //全てのアニメーションを解放
        for (auto iter = Instance->AnimationMap.begin(); iter != Instance->AnimationMap.end(); iter++)
        {
            MV1DeleteModel(iter->second);
        }
        //全てのモデルを解放する
        for (auto iter = Instance->MeshMap.begin(); iter != Instance->MeshMap.end(); iter++)
        {
            MV1DeleteModel(iter->second);
        }
        //全ての複製モデルを削除削除する
        for (auto iter = Instance->DuplicatesMesh.begin(); iter != Instance->DuplicatesMesh.end(); iter++)
        {
            MV1DeleteModel(*iter);
        }

        Instance->AnimationMap.clear();
        Instance->MeshMap.clear();
        Instance->DuplicatesMesh.clear();
    }
}