#pragma once
#include "../../GameObjectBase/GameObjectBase.h"

namespace Calculation
{
    /// <summary>
    /// ステージ関連処理を行うクラス
    /// </summary>
    class Stage : public GameObjectBase
    {
    public:
        /// <summary>
        /// Stageクラスのインスタンスを生成
        /// </summary>
        /// <returns>Stageクラスのインスタンス</returns>
        static Stage* CreateInstance();

        /// <summary>
        /// Stageクラスのインスタンスを破棄
        /// </summary>
        static void DestoryInstance();

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Initialize()override;

        /// <summary>
        /// 更新処理
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime)override {}

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw()override;

    private:
        /// <summary>
        /// コンストラクタ（シングルトン）
        /// </summary>
        Stage();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Stage();

        /// <summary>
        /// モデルの読み込み
        /// </summary>
        void ModelLoad();

        //Stageクラスのインスタンスを保持
        static Stage* Instance;

        //ステージの初期座標
        const VECTOR StagePos = VGet(0, -255, 0);
    };
}

