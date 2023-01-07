#pragma once
#include "../GameObject/Objects/CharacterBase/CharacterBase.h"

namespace Calculation
{
    /// <summary>
    /// プレイヤー関連処理を行うクラス
    /// </summary>
    class Player : public CharacterBase
    {
    public:

        /// <summary>
        /// コンストラクタ
        /// </summary>
        Player();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Player();

        /// <summary>
        /// 初期化処理
        /// </summary>
        void Initialize()override;

        /// <summary>
        /// 更新処理
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Update(float deltaTime)override;

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw()override;

        /// <summary>
        /// 当たり判定処理
        /// </summary>
        /// <param name="other">当たっているオブジェクトのポインタ</param>
        void OnCollisionEnter(GameObjectBase* other)override;



    private:
        /// <summary>
        /// モデルの読み込み
        /// </summary>
        void ModelLoad()override;

        /// <summary>
        /// 入力処理
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Move(float deltaTime)override;

        /// <summary>
        /// 攻撃関連処理
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void Attack(float deltaTime);

        /// <summary>
        /// エネミーとの当たり判定
        /// </summary>
        /// <param name="other">エネミーのポインタ</param>
        void OnCollisionEnemy(CharacterBase* other);

        /// <summary>
        /// ダメージを受ける処理
        /// </summary>
        void OnDamage()override;

        //プレイヤーの大きさ
        const VECTOR PlayerScale = { 0.8f,0.8f, 0.8f };
        //プレイヤーの初期座標
        const VECTOR FirstPos = { 0,0,0 };
        //プレイヤーの初期向き
        const VECTOR FirstDir = { 0,0,1 };

        //球の初期ローカル座標
        const VECTOR FirstLocalPos = { 0, 50.0f, 0 };

        //カプセルの始点
        const VECTOR CapsuleStart = { 0, 100.0f, 0 };
        //カプセルの終点 
        const VECTOR CapsuleEnd = { 0, 20.0f, 0 };

        //扇の角度
        const float Theta = 0.5f;  //cos60°
        //通常攻撃の範囲
        const float Range = 200.0f;

        ////足元判定の線分の始点
        //const VECTOR LineStart = { 0,20.0f,0 };
        ////足元判定の線分の終点
        //const VECTOR LineEnd = { 0,-30.0f,0 };

        //球状の当たり判定の半径
        const float Radius = 40.0f;
        //入力ベクトルの最小値
        const float InputVecMin = 0.5f;
        //移動速度
        const float MoveVelocity = 200.0f;
        //回転速度
        const float RotateVelocity = 10.0f;
        //体力の上限値
        const int MaxHP = 100;

        //ゲームパッド入力状態
        XINPUT_STATE gamePadState;
        int HP;
        bool attack;
    };
}