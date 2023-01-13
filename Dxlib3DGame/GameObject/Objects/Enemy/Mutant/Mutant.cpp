#include "Mutant.h"
#include "../GameObject/VectorCalculation/VectorCalculation.h"
#include "../GameObject/GameObjectManager/GameObjectManager.h"
#include "../GameObject/AssetManager/AssetManager.h"
#include "../GameObject/ObjectTag.h"
#include "../GameObject/Collision/Sphere/Sphere.h"
#include "../GameObject/Objects/Player/Player.h"
#include "../GameObject/VectorCalculation/VectorCalculation.h"
#include "../GameObject/Objects/Crystal/Crystal.h"

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
        //���S�A�j���[�V�������Đ��I�����Ă�����o���l�𐶐����ăG�l�~�[���f�����폜
        if (animTypeID == 3 && !animControl->IsPlaying(3))
        {
            GameObjectManager::Entry(new Crystal(pos));
            GameObjectManager::Release(this);
        }
        //���S�A�j���[�V�������Đ�����Ă��Ȃ����
        else if(animTypeID != 3)
        {
            Rotate();
            Move(deltaTime);

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
        //�v���C���[�Ƃ̓����蔻��
        if (tag == ObjectTag::Player)
        {
            if (attack)
            {
                VECTOR distance = other->GetPos() - pos;
                float twoPointsDisatance = sqrt(pow(distance.x, 2.0f) + pow(distance.z, 2.0f));
                //��͈͓̔��ɑ��݂��Ă�����
                if (twoPointsDisatance < Range)
                {
                    //�x�N�g���̐��K��
                    VECTOR dirNorm = VNorm(dir);
                    distance = VNorm(distance);
                    //2�̃x�N�g���̓��ς����߂�
                    float dot = (dirNorm.x * distance.x) + (dirNorm.z * distance.z);
                    if (dot / 2 <= Theta)
                    {
                        static_cast<CharacterBase*>(other)->OnDamage();
                    }
                }
            }
        }
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
        dir = VNorm(distance);
        attack = false;
        //��苗���܂Őڋ߂���
        if (VSize(distance) > 100.0f)
        {
            velocity = dir * deltaTime * MoveVelocity;
            if (animTypeID != 1)
            {
                animTypeID = 1;
                animControl->StartAnimaiton(animTypeID);
            }
        }
        //��苗���܂Őڋ߂�����U���J�n
        else if (VSize(distance) <= 100.0f)
        {
            velocity = { 0,0,0 };
            if (animTypeID != 2)
            {
                attack = true;
                animTypeID = 2;
                animControl->StartAnimaiton(animTypeID);
            }
        }

        //�ړ�����
        pos += velocity;

        //3D���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle, pos);
    }
}

