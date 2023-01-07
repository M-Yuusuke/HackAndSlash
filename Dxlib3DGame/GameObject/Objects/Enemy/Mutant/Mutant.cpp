#include "Mutant.h"
#include "../GameObject/VectorCalculation/VectorCalculation.h"
#include "../GameObject/GameObjectManager/GameObjectManager.h"
#include "../GameObject/AssetManager/AssetManager.h"
#include "../GameObject/ObjectTag.h"
#include "../GameObject/Collision/Sphere/Sphere.h"
#include "../GameObject/Objects/Player/Player.h"
#include "../GameObject/VectorCalculation/VectorCalculation.h"

namespace Calculation
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Mutant::Mutant():
        CharacterBase(ObjectTag::Enemy)
    {
        ModelLoad();
        input = false;
        attack = false;
    }

    Mutant::Mutant(VECTOR pos):
        CharacterBase(ObjectTag::Enemy,pos)
    {
        ModelLoad();
        input = false;
        attack = false;
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
        if (animTypeID == 3 && !animControl->IsPlaying(3))
        {
            GameObjectManager::Release(this);
        }
        else if(animTypeID != 3)
        {
            Rotate();
            Move(deltaTime);
            MV1RefreshCollInfo(modelHandle);

            //移動処理
            //pos += velocity;

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

    }

    /// <summary>
    /// 当たり判定処理
    /// </summary>
    /// <param name="other">当たっているオブジェクトのポインタ</param>
    void Mutant::OnCollisionEnter(GameObjectBase* other)
    {
        ObjectTag tag = other->GetTag();

        //ステージとの衝突
        if (tag == ObjectTag::Stage)
        {
            OnCollisionStage(other);
        }
        ////プレイヤーとの当たり判定
        //if (tag == ObjectTag::Player)
        //{
        //    int ColModel = other->GetCollisionModel();

        //    //自分の境界球とエネミーモデルとの当たり判定
        //    MV1_COLL_RESULT_POLY_DIM colInfo;

        //    //自分の境界球とプレイヤーのモデルが衝突していたらダメージを受ける
        //    if (collisionFunction.CollisionPair(collisionCapsule, ColModel, colInfo))
        //    {
        //        OnDamage();
        //    }
        //}
    }

    /// <summary>
    /// ダメージを受ける処理
    /// </summary>
    void Mutant::OnDamage()
    {
        if (animTypeID != 3)
        {
            animTypeID = 3;
            animControl->StartAnimaiton(animTypeID);
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
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Idle.mv1");                  //待機モーション
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Run.mv1");                   //移動モーション
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Punch.mv1");                 //攻撃モーション
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Dying.mv1",30.0f,false);     //死亡モーション

        animControl->StartAnimaiton(animTypeID);
        MV1SetPosition(modelHandle, pos);
        dir = { 0,0,1 };
        aimDir = dir;

        ////当たり判定球セット
        //collisionType = CollisionType::Sphere;
        //collisionSphere.SetLocalCenter(FirstLocalPos);
        //collisionSphere.SetRadius(Radius);

        //足元当たり判定線分セット
        //collisionLine = LineSegment(LineStart, LineEnd);

        collisionType = CollisionType::Capsule;
        collisionCapsule = Capsule(CapsuleStart, CapsuleEnd, Radius);

        collisionModel = MV1SetupCollInfo(modelHandle);
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
        dir = VNorm(distance) * deltaTime * MoveVelocity;

        if (VSize(distance) > 100.0f)
        {
            velocity = dir;
            if (animTypeID != 1)
            {
                animTypeID = 1;
                animControl->StartAnimaiton(animTypeID);
            }
        }
        else if (VSize(distance) <= 100.0f)
        {
            velocity = { 0,0,0 };
            if (animTypeID != 2)
            {
                animTypeID = 2;
                animControl->StartAnimaiton(animTypeID);
            }
        }
    }
}

