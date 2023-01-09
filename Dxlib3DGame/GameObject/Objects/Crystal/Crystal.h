#pragma once
#include "../GameObject/GameObjectBase/GameObjectBase.h"

namespace Calculation
{
    class Crystal : public GameObjectBase
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Crystal(VECTOR pos);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Crystal();

        /// <summary>
        /// 更新処理
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime)override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw();

        /// <summary>
        /// 当たり判定処理
        /// </summary>
        /// <param name="other">衝突検知をしたいオブジェクト</param>
        void OnCollisionEnter(GameObjectBase* other)override;

    private:
        /// <summary>
        /// モデル読み込み
        /// </summary>
        void ModelLoad();

        //クリスタルのサイズ
        const VECTOR Scale = { 0.1f,0.1f,0.1f };
    };
}

