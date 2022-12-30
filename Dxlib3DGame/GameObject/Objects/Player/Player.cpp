#include "Player.h"
#include "../GameObject/VectorCalculation/VectorCalculation.h"
#include "../GameObject/ObjectTag.h"
#include "../GameObject/AssetManager/AssetManager.h"
#include "../GameObject/GameObjectManager/GameObjectManager.h"
#include "../GameObject/Collision/CollisionFunction/CollisionFunction.h"

namespace Calculation
{
    /// <summary>
    /// �R���X�g���N�^
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
        input = false;
        attack = false;
        ModelLoad();
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    Player::~Player()
    {
        AssetManager::ReleaseMesh(modelHandle);
        AssetManager::ReleaseMesh(collisionModel);
        //GameObjectManager::Release(this);
        delete animControl;
        modelHandle = -1;
        collisionModel = -1;
    }

    /// <summary>
    /// ���f���̓ǂݍ���
    /// </summary>
    void Player::ModelLoad()
    {
        //���f�����[�h
        modelHandle = AssetManager::GetMesh("../Data/Assets/Player/Model.mv1");

        //���̂܂܂��ƃX�e�[�W�ɑ΂��ă��f�����傫���̂ŏk��
        MV1SetScale(modelHandle, PlayerScale);

        //�A�j���[�V�����R���g���[���[�̐���
        animControl = new AnimationController(modelHandle);

        //�A�j���[�V�������[�h
        animControl->AddAnimation("../Data/Assets/Player/Idle.mv1");                                //�ҋ@���[�V����
        animControl->AddAnimation("../Data/Assets/Player/Run.mv1");                                 //�ړ����[�V����
        animControl->AddAnimation("../Data/Assets/Player/Damage.mv1");                              //�_���[�W���[�V����
        animControl->AddAnimation("../Data/Assets/Player/Deth.mv1");                                //���S���[�V����
        animControl->AddAnimation("../Data/Assets/Player/Attack.mv1", 30.0f, false);                //�ʏ�U�����[�V����
        animControl->AddAnimation("../Data/Assets/Player/FrontRangeAttack.mv1", 30.0f, false);      //�͈͍U�����[�V����

        //�ҋ@���[�V�������Z�b�g
        animControl->StartAnimaiton(animTypeID);
        pos = FirstPos;
        dir = FirstDir;
        aimDir = dir;

        //�����蔻�苅�Z�b�g
        collisionType = CollisionType::Sphere;
        collisionSphere.SetLocalCenter(FirstLocalPos);
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
        Attack(deltaTime);

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
        input = false;
        if (!attack)
        {
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
            //�����ҋ@���[�V�����łȂ���Αҋ@���[�V�����ɂ���
            if (!attack && animTypeID != 0)
            {
                animTypeID = 0;
                animControl->StartAnimaiton(animTypeID);
            }
        }
    }

    /// <summary>
    /// �U���֘A����
    /// </summary>
    /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
    void Player::Attack(float deltaTime)
    {
        //�L�[���͏�Ԏ擾
        GetJoypadXInputState(DX_INPUT_PAD1, &gamePadState);
        //F�L�[�������̓Q�[���p�b�h��B�{�^���������ꂽ�A���U�����[�V�������Đ����łȂ���΍U�����[�V�������Z�b�g
        if ((CheckHitKey(KEY_INPUT_F) || gamePadState.Buttons[13]) && !(animControl->IsPlaying(4)))
        {
            attack = true;
            animTypeID = 4;
            animControl->StartAnimaiton(animTypeID);
        }
        //R�L�[�������̓Q�[���p�b�h��Y�{�^���������ꂽ�A���U�����[�V�������Đ����łȂ���Δ͈͍U�����[�V�������Z�b�g
        if ((CheckHitKey(KEY_INPUT_R) || gamePadState.Buttons[15]) && !(animControl->IsPlaying(5)))
        {
            attack = true;
            animTypeID = 5;
            animControl->StartAnimaiton(animTypeID);
        }

        //�ʏ�������͔͈͍U�����[�V�����Đ����łȂ���΍U���t���O��|��
        if (!animControl->IsPlaying(4) || !animControl->IsPlaying(5))
        {
            attack = false;
        }
    }

    /// <summary>
    /// �v���C���[�ƃX�e�[�W�̓����蔻��
    /// </summary>
    /// <param name="other">�������Ă���I�u�W�F�N�g�̃|�C���^</param>
    //void Player::OnCollisionStage(const GameObjectBase* other)
    //{
    //    int ColModel = other->GetCollisionModel();

    //    //�X�e�[�W�Ǝ����̋��E���Ƃ̓����蔻��
    //    MV1_COLL_RESULT_POLY_DIM colInfo;
    //    if (collisionFunction.CollisionPair(collisionSphere, ColModel, colInfo))
    //    {
    //        //�������Ă���ꍇ�͉����߂��ʂ��v�Z
    //        VECTOR pushBackVec = collisionFunction.CalcSpherePushBackVecFormMesh(collisionSphere, colInfo);
    //        pos += pushBackVec;

    //        //�R���W�������̉��
    //        MV1CollResultPolyDimTerminate(colInfo);
    //        CollisionUpdate();
    //    }

    //    //�X�e�[�W�Ƒ������������蔻��
    //    MV1_COLL_RESULT_POLY colInfoLine;
    //    if (collisionFunction.CollisionPair(collisionLine, ColModel, colInfoLine))
    //    {
    //        //�������Ă���ꍇ�͑������Փ˓_�ɍ��킹��
    //        pos = colInfoLine.HitPosition;
    //        CollisionUpdate();
    //    }
    //}
}