#include "Mutant.h"
#include "../GameObject/VectorCalculation/VectorCalculation.h"
#include "../GameObject/GameObjectManager/GameObjectManager.h"
#include "../GameObject/AssetManager/AssetManager.h"
#include "../GameObject/ObjectTag.h"
#include "../GameObject/Collision/Sphere/Sphere.h"

namespace Calculation
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Mutant::Mutant():
        CharacterBase(ObjectTag::Enemy)
    {
        ModelLoad();
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    Mutant::~Mutant()
    {
        AssetManager::ReleaseMesh(modelHandle);
        AssetManager::ReleaseMesh(collisionModel);
        delete animControl;
        modelHandle = -1;
        collisionModel = -1;
    }

    /// <summary>
    /// 初期化
    /// </summary>
    void Mutant::Initialize()
    {
    }

    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="deltaTime">1フレームの経過時間</param>
    void Mutant::Update(float deltaTime)
    {
        animControl->AddAnimaitonTime(deltaTime);
        Rotate();
        Move(deltaTime);

        //移動処理
        pos += velocity;

        //3Dモデルのポジション設定
        MV1SetPosition(modelHandle, pos);

        //向きに合わせてモデルを回転
        //mixamoのモデルはX軸が反対向きに出るのでまずベクトルを180度回転させる
        MATRIX RotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
        VECTOR NegativeVec = VTransform(dir, RotYMat);

        //モデルに回転をセットする
        MV1SetRotationZYAxis(modelHandle, NegativeVec, { 0,1.0f,0 }, 0);

        //当たり判定モデルも位置更新
        CollisionUpdate();
    }

    /// <summary>
    /// 当たり判定処理
    /// </summary>
    /// <param name="other">当たっているオブジェクトのポインタ</param>
    void Mutant::OnCollisionEnter(const GameObjectBase* other)
    {
        ObjectTag tag = other->GetTag();

        //ステージとの衝突
        if (tag == ObjectTag::Stage)
        {
            OnCollisionStage(other);
        }
        if (tag == ObjectTag::Enemy)
        {

        }
    }

    /// <summary>
    /// 描画
    /// </summary>
    void Mutant::Draw()
    {
        MV1DrawModel(modelHandle);
        DrawCollider();
    }


    /// <summary>
    /// モデル・アニメーションの読み込み
    /// </summary>
    void Mutant::ModelLoad()
    {
        //モデルロード
        modelHandle = AssetManager::GetMesh("../Data/Assets/Enemy/Mutant/Model.mv1");

        //そのままだとステージに対してモデルが大きいので縮小
        MV1SetScale(modelHandle, Scale);

        //アニメーションコントローラーの生成
        animControl = new AnimationController(modelHandle);

        //アニメーションロード
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Idle.mv1");      //待機モーション
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Run.mv1");       //移動モーション
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Punch.mv1");     //攻撃モーション

        animControl->StartAnimaiton(animTypeID);
        pos = FirstPos;
        MV1SetPosition(modelHandle, pos);
        dir = { 0,0,1 };
        aimDir = dir;

        //当たり判定球セット
        collisionType = CollisionType::Sphere;
        collisionSphere.SetLocalCenter(FirstLocalPos);
        collisionSphere.SetRadius(Radius);

        //足元当たり判定線分セット
        collisionLine = LineSegment(LineStart, LineEnd);
    }

    /// <summary>
    /// 移動
    /// </summary>
    /// <param name="deltaTime">1フレームの経過時間</param>
    void Mutant::Move(float deltaTime)
    {
        GameObjectBase* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);
        //プレイヤーの位置の取得
        VECTOR playerPos = player->GetPos();
        //プレイヤーとエネミーの距離計算
        VECTOR distance = playerPos - pos;

        //プレイヤーとエネミーの距離が索敵範囲内なら
        if (VSize(distance) < SearchRange)
        {
            VECTOR normVec = VNorm(distance);
            //プレイヤーの方向を向かせる
            RotateForAimVecYAxis(pos, normVec, RotateVelocity);
            dir = normVec;
        }

        VECTOR UP = { 0,0,1 };
        VECTOR DOWN = { 0,0,-1 };
        VECTOR LEFT = { -1,0,0 };
        VECTOR RIGHT = { 1,0,0 };

        VECTOR inputVec = { 0,0,0 };

        //一定距離まで接近する
        if (VSize(distance) > 300.0f)
        {
            //if (distance.x >= 0)
            //{
            //    inputVec += RIGHT;
            //}
            //if (distance.x < 0)
            //{
            //    inputVec += LEFT;
            //}
            //if (distance.z >= 0)
            //{
            //    inputVec += UP;
            //}
            //if (distance.z < 0)
            //{
            //    inputVec += DOWN;
            //}
            //inputVec += UP;
        }
        else
        {
            //一定距離まで接近したら攻撃モーションに切り替える
            animTypeID = 2;
            animControl->StartAnimaiton(animTypeID);
        }
        
        //方向を正規化
        inputVec = VNorm(inputVec);

        //入力方向は現在向いてる向きと異なるか？
        if (IsNearAngle(inputVec, dir))
        {
            dir = inputVec;
        }
        else
        {
            rotateNow = true;
            aimDir = inputVec;
        }
        velocity = inputVec + (inputVec * deltaTime * MoveVelocity);

        //もしほかのモーション中だったら走りモーションへ
        if (animTypeID != 1)
        {
            animTypeID = 1;
            animControl->StartAnimaiton(animTypeID);
        }
    }
}

