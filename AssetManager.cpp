#include "DxLib.h"
#include "AssetManager.h"
#include "VectorCalculation.h"

namespace Calculation
{
    AssetManager* AssetManager::Instance = nullptr;
    AssetManager::~AssetManager()
    {
        ReleaseAllAsset();
    }

    /**
    * AssetManagerのインスタンスを生成する
    * @note staticメソッドを内部で使用する際に必要
    */
    void Calculation::AssetManager::CreateInstance()
    {
        if (!Instance)
        {
            Instance = new AssetManager;
        }
    }

    /**
    * AssetManagerの後始末処理
    * @detail アプリケーション終了前に呼び出し、マネージャが確保した領域と
    * マネージャ自身の解放処理を行う。
    */
    void Calculation::AssetManager::DestoryInstance()
    {
        if (Instance)
        {
            delete Instance;
            Instance = nullptr;
        }
    }

    /**
    * メッシュの取得
    * @param[in] meshFileName 取得したいメッシュファイル名
    * @return int メッシュハンドル
    * 
    * @detailes メッシュ(モデル)ハンドルを取得する
    * 同じファイル名を2度以上指定したときはファイル読み込みは行われず、複製されたハンドルを返す
    * ファイルが見つからないときは-1を返す
    */
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
        //新規読み込みも2回め読み込みも、複製したものを返す
        //メッシュを使うキャラクターが複数いた場合に、原本を消されると全員消えて困るため
        //メッシュのコピー削除用にDuplivateMashに保存
        meshID = MV1DuplicateModel(Instance->MeshMap[meshFileName]);
        Instance->DuplicatesMesh.push_back(meshID);
        return meshID;
    }

    /**
    * アニメーションの読み込み
    * @param[in] animaitonFileName 読み込みたいアニメーションファイル名
    * @return int アニメーションハンドル
    * 
    * @details アニメーションをファイル読み込みし、アニメーションハンドルを返す
    * 同じファイル名で2度以上読み込まれた場合は、読み込みを行わず、ハンドルのみ返す
    * アニメーションは複製されない
    */
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

    /**
    * メッシュの解放
    * @param[in] meshID 解放したいモデルハンドル
    * 
    * @details　複製サれたモデルハンドルを解放する
    * 複製されたモデルハンドルなので、全部消しても原本のモデルハンドルは残る
    */
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

    /**
    * 全てのメッシュの解放
    * 
    * @details 複製、原本のモデルハンドル、アニメーションを全て解放する
    * アプリケーションの終了時にDxlib_End()より前に呼び出す必要がある。
    */
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