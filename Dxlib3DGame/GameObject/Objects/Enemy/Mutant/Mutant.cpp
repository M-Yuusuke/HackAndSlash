#include "Mutant.h"
#include "../GameObject/VectorCalculation/VectorCalculation.h"
#include "../GameObject/GameObjectManager/GameObjectManager.h"
#include "../GameObject/AssetManager/AssetManager.h"
#include "../GameObject/ObjectTag.h"
#include "../GameObject/Collision/Sphere/Sphere.h"

namespace Calculation
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Mutant::Mutant():
        CharacterBase(ObjectTag::Enemy)
    {
        ModelLoad();
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
        Rotate();
        Move(deltaTime);

        //�ړ�����
        pos += velocity;

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

    /// <summary>
    /// �����蔻�菈��
    /// </summary>
    /// <param name="other">�������Ă���I�u�W�F�N�g�̃|�C���^</param>
    void Mutant::OnCollisionEnter(const GameObjectBase* other)
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
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Idle.mv1");      //�ҋ@���[�V����
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Run.mv1");       //�ړ����[�V����
        animControl->AddAnimation("../Data/Assets/Enemy/Mutant/Punch.mv1");     //�U�����[�V����

        animControl->StartAnimaiton(animTypeID);
        pos = FirstPos;
        MV1SetPosition(modelHandle, pos);
        dir = { 0,0,1 };
        aimDir = dir;

        //�����蔻�苅�Z�b�g
        collisionType = CollisionType::Sphere;
        collisionSphere.SetLocalCenter(FirstLocalPos);
        collisionSphere.SetRadius(Radius);

        //���������蔻������Z�b�g
        collisionLine = LineSegment(LineStart, LineEnd);
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

        //�v���C���[�ƃG�l�~�[�̋��������G�͈͓��Ȃ�
        if (VSize(distance) < SearchRange)
        {
            VECTOR normVec = VNorm(distance);
            //�v���C���[�̕�������������
            RotateForAimVecYAxis(pos, normVec, RotateVelocity);
            dir = normVec;
        }

        VECTOR UP = { 0,0,1 };
        VECTOR DOWN = { 0,0,-1 };
        VECTOR LEFT = { -1,0,0 };
        VECTOR RIGHT = { 1,0,0 };

        VECTOR inputVec = { 0,0,0 };

        //��苗���܂Őڋ߂���
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
            //��苗���܂Őڋ߂�����U�����[�V�����ɐ؂�ւ���
            animTypeID = 2;
            animControl->StartAnimaiton(animTypeID);
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
}

