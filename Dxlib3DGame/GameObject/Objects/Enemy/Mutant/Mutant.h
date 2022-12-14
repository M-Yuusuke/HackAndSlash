#pragma once
#include "../GameObject/Objects/CharacterBase/CharacterBase.h"

namespace Calculation
{
    class Mutant final : public CharacterBase 
    {
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Mutant();
        Mutant(VECTOR pos);

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Mutant();

        /// <summary>
        /// 初期化
        /// </summary>
        void Initialize()override;

        /// <summary>
        /// 更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime)override;

        /// <summary>
        /// 当たり判定処理
        /// </summary>
        /// <param name="other">当たっているオブジェクトのポインタ</param>
        void OnCollisionEnter(GameObjectBase* other)override;

        /// <summary>
        /// ダメージを受ける処理
        /// </summary>
        void OnDamage();

        /// <summary>
        /// 描画
        /// </summary>
        void Draw()override;

        /// <summary>
        /// 攻撃中か返す
        /// </summary>
        /// <returns>攻撃中ならtrue、そうでなければfalse</returns>
        bool GetAttack() { return attack; }

    private:
        /// <summary>
        /// モデル・アニメーションの読み込み
        /// </summary>
        void ModelLoad() override;

        /// <summary>
        /// 移動
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Move(float deltaTime)override;

        //拡大率
        const VECTOR Scale = { 1.0f,1.0f ,1.0f };
        //初期座標
        //const VECTOR FirstPos = { 300.0f,0,0 };

        ////球の初期ローカル座標
        const VECTOR FirstLocalPos = { 0, 50.0f, 0 };

        //カプセルの始点
        const VECTOR CapsuleStart = { 0, 120.0f, 0 };
        //カプセルの終点 
        const VECTOR CapsuleEnd = { 0, 20.0f, 0 };

        ////足元判定の線分の始点
        //const VECTOR LineStart = { 0, 20.0f, 0 };
        ////足元判定の線分の終点
        //const VECTOR LineEnd = { 0, -30.0f, 0 };

        //球状の当たり判定の半径
        const float Radius = 50.0f;
        //移動速度
        const float MoveVelocity = 100.0f;
        //扇の角度
        const float Theta = 0.5f;  //cos60°
        //通常攻撃の範囲
        const float Range = 150.0f;

        //移動中か
        bool input;
        //攻撃中か
        bool attack;
    };
}