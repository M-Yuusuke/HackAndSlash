#include "Player.h"
#include "../GameObject/VectorCalculation/VectorCalculation.h"
#include "../GameObject/ObjectTag.h"
#include "../GameObject/AssetManager/AssetManager.h"
#include "../GameObject/GameObjectManager/GameObjectManager.h"
#include "../GameObject/Collision/CollisionFunction/CollisionFunction.h"

namespace Calculation
{
    Player* Player::Instance = nullptr;

    /// <summary>
    /// コンストラクタ（シングルトン）
    /// </summary>
    Player::Player() :
        GameObjectBase(ObjectTag::Player),
        dir({ 0,0,0 }),
        aimDir({ 0,0,0 }),
        velocity({ 0,0,0 }),
        animControl(nullptr),
        animTypeID(0),
        rotateNow(false)
    {
        ModelLoad();
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    Player::~Player()
    {
        AssetManager::ReleaseMesh(modelHandle);
        AssetManager::ReleaseMesh(collisionModel);
        GameObjectManager::Release(Instance);
        modelHandle = -1;
        collisionModel = -1;
    }

    /// <summary>
    /// Playerクラスのインスタンス生成
    /// </summary>
    /// <returns>Playerクラスのインスタンス</returns>
    Player* Player::CreateInstance()
    {
        if (!Instance)
        {
            Instance = new Player;
        }
        return Instance;
    }

    /// <summary>
    /// Playerクラスのインスタンス破棄
    /// </summary>
    void Player::DestoryInstance()
    {
        if (Instance)
        {
            delete Instance;
        }
    }

    /// <summary>
    /// モデルの読み込み
    /// </summary>
    void Player::ModelLoad()
    {
        //モデルロード
        //modelHandle = AssetManager::GetMesh("../Data/Assets/Player/Model.mv1");
        modelHandle = AssetManager::GetMesh("../Data/Assets/UnityChan/unityChanModel.mv1");
        //そのままだとステージに対してモデルが大きいので縮小
        MV1SetScale(modelHandle, PlayerScale);

        //アニメーションコントローラーの生成
        animControl = new AnimationController(modelHandle);

        ////アニメーションロード
        //animControl->AddAnimation("../Data/Assets/Player/Idle.mv1");
        //animControl->AddAnimation("../Data/Assets/Player/Run.mv1");
        //animControl->AddAnimation("../Data/Assets/Player/Attack.mv1");

        animControl->AddAnimation("../Data/Assets/UnityChan/unityChanAnimIdle.mv1");
        animControl->AddAnimation("../Data/Assets/UnityChan/unityChanAnimRun.mv1");
        animControl->AddAnimation("../Data/Assets/UnityChan/unityChanAnimPunch.mv1");

        animControl->StartAnimaiton(animTypeID);
        pos = { 0,0,0 };
        dir = { 1,0,0 };
        aimDir = dir;

        //当たり判定球セット
        collisionType = CollisionType::Sphere;
        collisionSphere.SetLocalCenter(firstLocalPos);
        collisionSphere.SetRadius(Radius);

        //足元当たり判定線分セット
        collisionLine = LineSegment(LineStart, LineEnd);
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Player::Initialize()
    {
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
    void Player::OnCollisionEnter(const GameObjectBase* other)
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
        bool input = false;

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
            //もしほかのモーション中だったら歩きモーションへ
            if (animTypeID != 0)
            {
                animTypeID = 0;
                animControl->StartAnimaiton(animTypeID);
            }
        }
    }

    /// <summary>
    /// 回転処理
    /// </summary>
    void Player::Rotate()
    {
        if (rotateNow)
        {
            //回転が目標角度に十分近ければ回転モード終了
            if (IsNearAngle(aimDir, dir))
            {
                dir = aimDir;
                rotateNow = false;
            }
            else
            {
                //回転させる
                VECTOR interPolateDir;
                interPolateDir = RotateForAimVecYAxis(dir, aimDir, RotateVelocity);

                //回転が目標角度を超えていないか
                VECTOR cross1, cross2;
                cross1 = VCross(dir, aimDir);
                cross2 = VCross(interPolateDir, aimDir);

                //目標角度を超えたら終了
                if (cross1.y * cross2.y < 0)
                {
                    interPolateDir = aimDir;
                    rotateNow = false;
                }
                //目標ベクトルに10度だけ近づけた角度
                dir = interPolateDir;
            }
        }
    }

    /// <summary>
    /// プレイヤーとステージの当たり判定
    /// </summary>
    /// <param name="other">当たっているオブジェクトのポインタ</param>
    void Player::OnCollisionStage(const GameObjectBase* other)
    {
        int ColModel = other->GetCollisionModel();

        //ステージと自分の境界球との当たり判定
        MV1_COLL_RESULT_POLY_DIM colInfo;
        if (collisionFunction.CollisionPair(collisionSphere, ColModel, colInfo))
        {
            //当たっている場合は押し戻し量を計算
            VECTOR pushBackVec = collisionFunction.CalcSpherePushBackVecFormMesh(collisionSphere, colInfo);
            pos += pushBackVec;

            //コリジョン情報の解放
            MV1CollResultPolyDimTerminate(colInfo);
            CollisionUpdate();
        }

        //ステージと足元線分当たり判定
        MV1_COLL_RESULT_POLY colInfoLine;
        if (collisionFunction.CollisionPair(collisionLine, ColModel, colInfoLine))
        {
            //当たっている場合は足元を衝突点に合わせる
            pos = colInfoLine.HitPosition;
            CollisionUpdate();
        }
    }
}