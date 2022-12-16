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
    /// �R���X�g���N�^�i�V���O���g���j
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
    /// �f�X�g���N�^
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
    /// Player�N���X�̃C���X�^���X����
    /// </summary>
    /// <returns>Player�N���X�̃C���X�^���X</returns>
    Player* Player::CreateInstance()
    {
        if (!Instance)
        {
            Instance = new Player;
        }
        return Instance;
    }

    /// <summary>
    /// Player�N���X�̃C���X�^���X�j��
    /// </summary>
    void Player::DestoryInstance()
    {
        if (Instance)
        {
            delete Instance;
        }
    }

    /// <summary>
    /// ���f���̓ǂݍ���
    /// </summary>
    void Player::ModelLoad()
    {
        //���f�����[�h
        //modelHandle = AssetManager::GetMesh("../Data/Assets/Player/Model.mv1");
        modelHandle = AssetManager::GetMesh("../Data/Assets/UnityChan/unityChanModel.mv1");
        //���̂܂܂��ƃX�e�[�W�ɑ΂��ă��f�����傫���̂ŏk��
        MV1SetScale(modelHandle, PlayerScale);

        //�A�j���[�V�����R���g���[���[�̐���
        animControl = new AnimationController(modelHandle);

        ////�A�j���[�V�������[�h
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

        //�����蔻�苅�Z�b�g
        collisionType = CollisionType::Sphere;
        collisionSphere.SetLocalCenter(firstLocalPos);
        collisionSphere.SetRadius(Radius);

        //���������蔻������Z�b�g
        collisionLine = LineSegment(LineStart, LineEnd);
    }

    /// <summary>
    /// ����������
    /// </summary>
    void Player::Initialize()
    {
    }

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
    void Player::Update(float deltaTime)
    {
        animControl->AddAnimaitonTime(deltaTime);
        Rotate();
        Move(deltaTime);

        //�ړ�����
        pos += velocity;

        //3D���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle, pos);

        //�����ɍ��킹�ă��f������]
        //mixamo�̃��f����X�������Ό����ɏo��̂ł܂��x�N�g����180�x��]������
        MATRIX RotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
        VECTOR NegativeVec = VTransform(dir,RotYMat);

        //���f���ɉ�]���Z�b�g����
        MV1SetRotationZYAxis(modelHandle, NegativeVec, { 0,1.0f,0 }, 0);
        
        //�����蔻�胂�f�����ʒu�X�V
        CollisionUpdate();
    }

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Player::Draw()
    {
        //3D���f���̕`��
        MV1DrawModel(modelHandle);
        DrawCollider();
    }

    /// <summary>
    /// �����蔻�菈��
    /// </summary>
    /// <param name="other">�������Ă���I�u�W�F�N�g�̃|�C���^</param>
    void Player::OnCollisionEnter(const GameObjectBase* other)
    {
        ObjectTag tag = other->GetTag();

        //�X�e�[�W�Ƃ̏Փ�
        if (tag == ObjectTag::Stage)
        {
            OnCollisionStage(other);
        }
        if (tag == ObjectTag::Enemy)
        {

        }
    }

    /// <summary>
    /// ���͏���
    /// </summary>
    /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
    void Player::Move(float deltaTime)
    {
        //�L�[���͏�Ԏ擾
        GetJoypadXInputState(DX_INPUT_PAD1, &gamePadState);
        VECTOR UP = { 0,0,1 };
        VECTOR DOWN = { 0,0,-1 };
        VECTOR LEFT = { -1,0,0 };
        VECTOR RIGHT = { 1,0,0 };

        VECTOR inputVec = { 0,0,0 };
        bool input = false;

        //�����͂��Ă������ɐi��
        if (CheckHitKey(KEY_INPUT_W) || gamePadState.ThumbLY > 0)
        {
            inputVec += UP;
            input = true;
        }
        //������͂��Ă����牺�ɐi��
        if (CheckHitKey(KEY_INPUT_S) || gamePadState.ThumbLY < 0)
        {
            inputVec += DOWN;
            input = true;
        }
        //������͂��Ă����獶�ɐi��
        if (CheckHitKey(KEY_INPUT_A) || gamePadState.ThumbLX < 0)
        {
            inputVec += LEFT;
            input = true;
        }
        //�E����͂��Ă�����E�ɐi��
        if (CheckHitKey(KEY_INPUT_D) || gamePadState.ThumbLX > 0)
        {
            inputVec += RIGHT;
            input = true;
        }


        //���͂������������
        if (input)
        {
            //�㉺�E���E���������Ȃǂœ��̓x�N�g����0�̎��͖���
            if (VSquareSize(inputVec) < InputVecMin)
            {
                return;
            }
            //�����𐳋K��
            inputVec = VNorm(inputVec);

            //���͕����͌��݌����Ă�����ƈقȂ邩�H
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

            //�����ق��̃��[�V�������������瑖�胂�[�V������
            if (animTypeID != 1)
            {
                animTypeID = 1;
                animControl->StartAnimaiton(animTypeID);
            }
        }
        //���͂��Ȃ������猸��
        else
        {
            velocity *= 0.9f;
            //�����ق��̃��[�V��������������������[�V������
            if (animTypeID != 0)
            {
                animTypeID = 0;
                animControl->StartAnimaiton(animTypeID);
            }
        }
    }

    /// <summary>
    /// ��]����
    /// </summary>
    void Player::Rotate()
    {
        if (rotateNow)
        {
            //��]���ڕW�p�x�ɏ\���߂���Ή�]���[�h�I��
            if (IsNearAngle(aimDir, dir))
            {
                dir = aimDir;
                rotateNow = false;
            }
            else
            {
                //��]������
                VECTOR interPolateDir;
                interPolateDir = RotateForAimVecYAxis(dir, aimDir, RotateVelocity);

                //��]���ڕW�p�x�𒴂��Ă��Ȃ���
                VECTOR cross1, cross2;
                cross1 = VCross(dir, aimDir);
                cross2 = VCross(interPolateDir, aimDir);

                //�ڕW�p�x�𒴂�����I��
                if (cross1.y * cross2.y < 0)
                {
                    interPolateDir = aimDir;
                    rotateNow = false;
                }
                //�ڕW�x�N�g����10�x�����߂Â����p�x
                dir = interPolateDir;
            }
        }
    }

    /// <summary>
    /// �v���C���[�ƃX�e�[�W�̓����蔻��
    /// </summary>
    /// <param name="other">�������Ă���I�u�W�F�N�g�̃|�C���^</param>
    void Player::OnCollisionStage(const GameObjectBase* other)
    {
        int ColModel = other->GetCollisionModel();

        //�X�e�[�W�Ǝ����̋��E���Ƃ̓����蔻��
        MV1_COLL_RESULT_POLY_DIM colInfo;
        if (collisionFunction.CollisionPair(collisionSphere, ColModel, colInfo))
        {
            //�������Ă���ꍇ�͉����߂��ʂ��v�Z
            VECTOR pushBackVec = collisionFunction.CalcSpherePushBackVecFormMesh(collisionSphere, colInfo);
            pos += pushBackVec;

            //�R���W�������̉��
            MV1CollResultPolyDimTerminate(colInfo);
            CollisionUpdate();
        }

        //�X�e�[�W�Ƒ������������蔻��
        MV1_COLL_RESULT_POLY colInfoLine;
        if (collisionFunction.CollisionPair(collisionLine, ColModel, colInfoLine))
        {
            //�������Ă���ꍇ�͑������Փ˓_�ɍ��킹��
            pos = colInfoLine.HitPosition;
            CollisionUpdate();
        }
    }
}