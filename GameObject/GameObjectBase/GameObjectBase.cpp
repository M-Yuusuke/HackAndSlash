#include "GameObjectBase.h"
#include "../AssetManager/AssetManager.h"

namespace Calculation
{
    /**
    * �Q�[���I�u�W�F�N�g�x�[�X�R���X�g���N�^(�ʒu�w�薳��)
    * @param[in] tag �I�u�W�F�N�g�̎��
    */
    GameObjectBase::GameObjectBase(ObjectTag tag) :
        Tag(tag),
        Pos(),
        ModelHandle(-1),
        Visible(true),
        Alive(true),
        collisionType(),
        collisionLine(),
        collisionSphere(),
        collisionCapsule(),
        CollisionModel(-1)
    {
    }

    /**
    * �Q�[���I�u�W�F�N�g�x�[�X�R���X�g���N�^(�ʒu�w��L��)
    * @param[in] tag �I�u�W�F�N�g�̎��
    * @param[in] pos �I�u�W�F�N�g�̈ʒu
    */
    GameObjectBase::GameObjectBase(ObjectTag tag, VECTOR pos):
        Tag(tag),
        Pos(pos),
        ModelHandle(-1),
        Visible(true),
        Alive(true),
        collisionType(),
        collisionLine(),
        collisionSphere(),
        collisionCapsule(),
        CollisionModel(-1)
    {
    }

    /**�Q�[���I�u�W�F�N�g�f�X�g���N�^*/
    GameObjectBase::~GameObjectBase()
    {
        if (ModelHandle != -1)
        {
            //�R���W�������̌�n��
            MV1TerminateCollInfo(CollisionModel);
            //���f���f�[�^�̌�n��
            //AssetManager::ReleaseMesh(ModelHandle);
            ModelHandle = -1;
        }
    }

    /**
    * �����蔻��̍X�V����
    * @detail �I�u�W�F�N�g���ړ������Ƃ��ɂ͓����蔻��ʒu������ɍ��킹�čX�V����K�v������B
    * �����蔻�肪���f��(���b�V��)�̏ꍇ�A�|���S�����Ƃ̓����蔻������č\�z���邽�߁A�Ăяo���񐔂����炷�H�v���K�v�B
    * ���̑��̓����蔻��͖��t���[���Ăяo���Ă����Ȃ��B
    */
    void GameObjectBase::CollisionUpdate()
    {
        collisionSphere.Move(Pos);
        collisionLine.Move(Pos);
        collisionCapsule.Move(Pos);

        //���f���̓����蔻������č\�z
        if (CollisionModel != -1)
        {
            MV1SetPosition(CollisionModel, Pos);
            MV1SetupCollInfo(CollisionModel);
        }
    }

    //�R���C�_�[�̕`��
    void GameObjectBase::DrawCollider()
    {
        DrawLine3D(collisionLine.GetWorldStart(), collisionLine.GetWorldEnd(), GetColor(0, 0, 0));
        DrawSphere3D(collisionSphere.GetWorldCenter(), collisionSphere.GetRadius(), 8, GetColor(255, 0, 0), GetColor(0, 0, 0), FALSE);
        DrawCapsule3D(collisionCapsule.GetWorldStart(), collisionCapsule.GetWorldEnd(), collisionCapsule.GetRadius(), 8, GetColor(0, 255, 0), GetColor(0, 0, 0),FALSE);
        //�R���W�������f�������݂��Ă����甼�����`��
        if (CollisionModel != -1)
        {
            //�������ɂ���
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            MV1DrawModel(CollisionModel);
            //���ɖ߂�
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        }
    }
}