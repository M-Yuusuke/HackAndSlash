#include "Player.h"
#include <math.h>
#include "../GameObject/VectorCalculation/VectorCalculation.h"
#include "../GameObject/ObjectTag.h"
#include "../GameObject/AssetManager/AssetManager.h"
#include "../GameObject/GameObjectManager/GameObjectManager.h"
#include "../GameObject/Collision/CollisionFunction/CollisionFunction.h"
#include "../Enemy/Mutant/Mutant.h"

namespace Calculation
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Player::Player() :
        CharacterBase(ObjectTag::Player)
    {
        dir = { 0,0,0 };
        aimDir = { 0,0,0 };
        velocity = { 0,0,0 };
        animControl = nullptr;
        animTypeID = 0;
        rotateNow = false;
        attack = false;
        ModelLoad();
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    Player::~Player()
    {
        AssetManager::ReleaseMesh(modelHandle);
        AssetManager::ReleaseMesh(collisionModel);
        delete animControl;
        modelHandle = -1;
        collisionModel = -1;
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Player::Initialize()
    {
        HP = MaxHP;
    }

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="deltaTime">1フレームの経過時間</param>
    void Player::Update(float deltaTime)
    {
        animControl->AddAnimaitonTime(deltaTime);

        Rotate();
        Move(deltaTime);
        Attack(deltaTime);
        MV1RefreshCollInfo(modelHandle);
        //移動処理
        pos += velocity;

        //3Dモデルのポジション設定
        MV1SetPosition(modelHandle, pos);

        //向きに合わせてモデルを回転
        //mixamoのモデルはX軸が反対向きに出るのでまずベクトルを180度回転させる
        MATRIX RotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
        VECTOR NegativeVec = VTransform(dir,RotYMat);

        //モデルに回転をセットする
        MV1SetRotationZYAxis(modelHandle, NegativeVec, { 0,1.0f,0 }, 0);
        
        //当たり判定モデルも位置更新
        CollisionUpdate();
    }

    /// <summary>
    /// 描画処理
    /// </summary>
    void Player::Draw()
    {
        //3Dモデルの描画
        MV1DrawModel(modelHandle);
        DrawCollider();
    }

    /// <summary>
    /// 当たり判定処理
    /// </summary>
    /// <param name="other">当たっているオブジェクトのポインタ</param>
    void Player::OnCollisionEnter(GameObjectBase* other)
    {
        ObjectTag tag = other->GetTag();

        //ステージとの衝突
        if (tag == ObjectTag::Stage)
        {
            OnCollisionStage(other);
        }
        if (tag == ObjectTag::Enemy)
        {
            if (attack)
            {
                VECTOR distance = other->GetPos() - pos;
                float twoPointsDisatance = sqrt(pow(distance.x, 2.0f) + pow(distance.z, 2.0f));
                //扇の範囲内に存在していたら
                if (twoPointsDisatance < Range)
                {
                    //ベクトルの正規化
                    VECTOR dirNorm = VNorm(dir);
                    distance = VNorm(distance);
                    //2つのベクトルの内積を求める
                    float dot = (dirNorm.x * distance.x) + (dirNorm.z * distance.z);
                    if (dot / 2 <= Theta)
                    {
                        dynamic_cast<CharacterBase*>(other)->OnDamage();
                    }
                }
            }

            
        }
    }

    

    /// <summary>
    /// モデルの読み込み
    /// </summary>
    void Player::ModelLoad()
    {
        //モデルロード
        modelHandle = AssetManager::GetMesh("../Data/Assets/Player/Model.mv1");

        //そのままだとステージに対してモデルが大きいので縮小
        MV1SetScale(modelHandle, PlayerScale);

        //アニメーションコントローラーの生成
        animControl = new AnimationController(modelHandle);

        //アニメーションロード
        animControl->AddAnimation("../Data/Assets/Player/Idle.mv1");                                //待機モーション
        animControl->AddAnimation("../Data/Assets/Player/Run.mv1");                                 //移動モーション
        animControl->AddAnimation("../Data/Assets/Player/Damage.mv1", 30.0f, false);                //ダメージモーション
        animControl->AddAnimation("../Data/Assets/Player/Deth.mv1", 30.0f, false);                  //死亡モーション
        animControl->AddAnimation("../Data/Assets/Player/Attack.mv1", 30.0f, false);                //通常攻撃モーション
        animControl->AddAnimation("../Data/Assets/Player/FrontRangeAttack.mv1", 30.0f, false);      //範囲攻撃モーション

        //待機モーションをセット
        animControl->StartAnimaiton(animTypeID);
        pos = FirstPos;
        dir = FirstDir;
        aimDir = dir;

        //当たり判定球セット
        collisionType = CollisionType::Sphere;
        collisionSphere.SetLocalCenter(FirstLocalPos);
        collisionSphere.SetRadius(Radius);

        collisionType = CollisionType::Capsule;
        collisionCapsule = Capsule(CapsuleStart, CapsuleEnd,Radius);

        //足元当たり判定線分セット
        //collisionLine = LineSegment(LineStart, LineEnd);

        collisionModel = MV1SetupCollInfo(modelHandle);
    }

    /// <summary>
    /// 入力処理
    /// </summary>
    /// <param name="deltaTime">1フレームの経過時間</param>
    void Player::Move(float deltaTime)
    {
        //キー入力状態取得
        GetJoypadXInputState(DX_INPUT_PAD1, &gamePadState);
        VECTOR UP = { 0,0,1 };
        VECTOR DOWN = { 0,0,-1 };
        VECTOR LEFT = { -1,0,0 };
        VECTOR RIGHT = { 1,0,0 };

        VECTOR inputVec = { 0,0,0 };
        //入力状態
        bool input = false;

        if (!attack)
        {
            //上を入力していたら上に進む
            if (CheckHitKey(KEY_INPUT_W) || gamePadState.ThumbLY > 0)
            {
                inputVec += UP;
                input = true;
            }
            //下を入力していたら下に進む
            if (CheckHitKey(KEY_INPUT_S) || gamePadState.ThumbLY < 0)
            {
                inputVec += DOWN;
                input = true;
            }
            //左を入力していたら左に進む
            if (CheckHitKey(KEY_INPUT_A) || gamePadState.ThumbLX < 0)
            {
                inputVec += LEFT;
                input = true;
            }
            //右を入力していたら右に進む
            if (CheckHitKey(KEY_INPUT_D) || gamePadState.ThumbLX > 0)
            {
                inputVec += RIGHT;
                input = true;
            }
        }

        //入力があったら加速
        if (input)
        {
            //上下・左右同時押しなどで入力ベクトルが0の時は無視
            if (VSquareSize(inputVec) < InputVecMin)
            {
                return;
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
        //入力がなかったら減速
        else
        {
            velocity *= 0.9f;
            //もし待機モーションでなければ待機モーションにする
            if (!attack && animTypeID != 0)
            {
                animTypeID = 0;
                animControl->StartAnimaiton(animTypeID);
            }
        }
    }

    /// <summary>
    /// 攻撃関連処理
    /// </summary>
    /// <param name="deltaTime">1フレームの経過時間</param>
    void Player::Attack(float deltaTime)
    {
        //キー入力状態取得
        GetJoypadXInputState(DX_INPUT_PAD1, &gamePadState);
        //FキーもしくはゲームパッドのBボタンが押された、かつ攻撃モーションが再生中でなければ攻撃モーションをセット
        if ((CheckHitKey(KEY_INPUT_F) || gamePadState.Buttons[13]) && !(animControl->IsPlaying(4)))
        {
            attack = true;
            animTypeID = 4;
            animControl->StartAnimaiton(animTypeID);
        }
        //RキーもしくはゲームパッドのYボタンが押された、かつ攻撃モーションが再生中でなければ範囲攻撃モーションをセット
        if ((CheckHitKey(KEY_INPUT_R) || gamePadState.Buttons[15]) && !(animControl->IsPlaying(5)))
        {
            attack = true;
            animTypeID = 5;
            animControl->StartAnimaiton(animTypeID);
        }

        //通常もしくは範囲攻撃モーション再生中でなければ攻撃フラグを倒す
        if (!animControl->IsPlaying(4) || !animControl->IsPlaying(5))
        {
            attack = false;
        }
    }

    /// <summary>
    /// エネミーとの当たり判定
    /// </summary>
    /// <param name="other">エネミーのポインタ</param>
    void Player::OnCollisionEnemy(CharacterBase* other)
    {
        if (attack)
        {
            VECTOR distance = other->GetPos() - pos;
            float twoPointsDisatance = sqrt(pow(distance.x, 2.0f) + pow(distance.z, 2.0f));
            //扇の範囲内に存在していたら
            if (twoPointsDisatance < Range)
            {
                //ベクトルの正規化
                VECTOR dirNorm = VNorm(dir);
                distance = VNorm(distance);
                //2つのベクトルの内積を求める
                float dot = (dirNorm.x * distance.x) + (dirNorm.z * distance.z);
                if (dot / 2 <= Theta)
                {
                    other->OnDamage();
                }
            }
        }
    }

    /// <summary>
    /// ダメージを受ける処理
    /// </summary>
    void Player::OnDamage()
    {
        if (HP > 0)
        {
            HP -= 2;
            animTypeID = 2;
            animControl->StartAnimaiton(animTypeID);
        }
        if (HP <= 0)
        {
            HP = 0;
            alive = false;
            animTypeID = 3;
            animControl->StartAnimaiton(animTypeID);
        }
    }
}