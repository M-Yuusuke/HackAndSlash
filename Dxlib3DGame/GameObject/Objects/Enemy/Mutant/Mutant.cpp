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
    /// �R���X�g���N�^
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
    /// �f�X�g���N�^
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
    /// ������
    /// </summary>
    void Mutant::Initialize()
    {
    }

    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
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

            //�ړ�����
            //pos += velocity;

            //3D���f���̃|�W�V�����ݒ�
            MV1SetPosition(modelHandle, pos);

            //�����ɍ��킹�ă��f������]
            //mixamo�̃��f����X�������Ό����ɏo��̂ł܂��x�N�g����180�x��]������
            MATRIX RotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
            VECTOR NegativeVec = VTransform(dir, RotYMat);

            //���f���ɉ�]���Z�b�g����
            MV1SetRotationZYAxis(modelHandle, NegativeVec, { 0,1.0f,0 }, 0);

            //�����蔻�胂�f�����ʒu�X�V
            CollisionUpdate();
        }

    }

    /// <summary>
    /// �����蔻�菈��
    /// </summary>
    /// <param name="other">�������Ă���I�u�W�F�N�g�̃|�C���^</param>
    void Mutant::OnCollisionEnter(GameObjectBase* other)
    {
        ObjectTag tag = other->GetTag();

        //�X�e�[�W�Ƃ̏Փ�
        if (tag == ObjectTag::Stage)
        {
            OnCollisionStage(other);
        }
        ////�v���C���[�Ƃ̓����蔻��
        //if (tag == ObjectTag::Player)
        //{
        //    int ColModel = other->GetCollisionModel();

        //    //�����̋��E���ƃG�l�~�[���f���Ƃ̓����蔻��
        //    MV1_COLL_RESULT_POLY_DIM colInfo;

        //    //�����̋��E���ƃv���C���[�̃��f�����Փ˂��Ă�����_���[�W���󂯂�
        //    if (collisionFunction.CollisionPair(collisionCapsule, ColModel, colInfo))
        //    {
        //        OnDamage();
        //    }
        //}
    }

    /// <summary>
    /// �_���[�W���󂯂鏈��
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
    /// �`��
    /// </summary>
    void Mutant::Draw()
    {
        MV1DrawModel(modelHandle);
        DrawCollider();
    }


    /// <summary>
    /// ���f���E�A�j���[�V�����̓ǂݍ���
    /// </summary>
    void Mutant::ModelLoad()
    {
        //���f�����[�h
        modelHandle = AssetManager::GetMesh("../Data/Assets/Enemy/Mutant/Model.mv1");

        //���̂܂܂��ƃX�e�[�W�ɑ΂��ă��f�����傫���̂ŏk��
        MV1SetScale(modelHandle, Scale);

        //�A�j���[�V�����R���g���[���[�̐���
        animControl = new AnimationController(modelHandle);

        //�A�j���[�V�������[�h
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Idle.mv1");                  //�ҋ@���[�V����
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Run.mv1");                   //�ړ����[�V����
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Punch.mv1");                 //�U�����[�V����
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Dying.mv1",30.0f,false);     //���S���[�V����

        animControl->StartAnimaiton(animTypeID);
        MV1SetPosition(modelHandle, pos);
        dir = { 0,0,1 };
        aimDir = dir;

        ////�����蔻�苅�Z�b�g
        //collisionType = CollisionType::Sphere;
        //collisionSphere.SetLocalCenter(FirstLocalPos);
        //collisionSphere.SetRadius(Radius);

        //���������蔻������Z�b�g
        //collisionLine = LineSegment(LineStart, LineEnd);

        collisionType = CollisionType::Capsule;
        collisionCapsule = Capsule(CapsuleStart, CapsuleEnd, Radius);

        collisionModel = MV1SetupCollInfo(modelHandle);
    }

    /// <summary>
    /// �ړ�
    /// </summary>
    /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
    void Mutant::Move(float deltaTime)
    {
        GameObjectBase* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);
        //�v���C���[�̈ʒu�̎擾
        VECTOR playerPos = player->GetPos();
        //�v���C���[�ƃG�l�~�[�̋����v�Z
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

