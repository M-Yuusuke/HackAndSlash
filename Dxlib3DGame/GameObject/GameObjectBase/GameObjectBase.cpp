#include "GameObjectBase.h"
#include "../AssetManager/AssetManager.h"
#include "../VectorCalculation/VectorCalculation.h"

namespace Calculation
{
    /**
    * �Q�[���I�u�W�F�N�g�x�[�X�R���X�g���N�^(�ʒu�w�薳��)
    * @param[in] tag �I�u�W�F�N�g�̎��
    */
    GameObjectBase::GameObjectBase(ObjectTag tag) :
        tag(tag),
        pos(),
        modelHandle(-1),
        visible(true),
        alive(true),
        collisionType(),
        collisionLine(),
        collisionSphere(),
        collisionCapsule(),
        collisionModel(-1)
    {
    }

    /**
    * �Q�[���I�u�W�F�N�g�x�[�X�R���X�g���N�^(�ʒu�w��L��)
    * @param[in] tag �I�u�W�F�N�g�̎��
    * @param[in] pos �I�u�W�F�N�g�̈ʒu
    */
    GameObjectBase::GameObjectBase(ObjectTag tag, VECTOR pos):
        tag(tag),
        pos(pos),
        modelHandle(-1),
        visible(true),
        alive(true),
        collisionType(),
        collisionLine(),
        collisionSphere(),
        collisionCapsule(),
        collisionModel(-1)
    {
    }

    /**�Q�[���I�u�W�F�N�g�f�X�g���N�^*/
    GameObjectBase::~GameObjectBase()
    {
        if (modelHandle != -1)
        {
            //�R���W�������̌�n��
            MV1TerminateCollInfo(collisionModel);
            //���f���f�[�^�̌�n��
            AssetManager::ReleaseMesh(modelHandle);
            modelHandle = -1;
        }
    }

    /**
    * �����蔻��̍X�V����
    * @detail �I�u�W�F�N�g���ړ������Ƃ��ɂ͓����蔻��ʒu������ɍ��킹�čX�V����K�v������B
    * �����蔻�肪���f��(���b�V��)�̏ꍇ�A�|���S�����Ƃ̓����蔻������č\�z���邽�߁A�Ăяo���񐔂����炷�H�v���K�v�B
    * ���̑��̓����蔻��͖��t���[���Ăяo���Ă����Ȃ��B
    */

    /// <summary>
    /// �����߂�
    /// </summary>
    /// <param name="pushBack">�����߂��x�N�g��</param>
    void GameObjectBase::PushBack(VECTOR pushBack)
    {
        pos -= pushBack;
        MV1SetPosition(modelHandle, pos);
    }
    void GameObjectBase::CollisionUpdate()
    {
        collisionSphere.Move(pos);
        collisionLine.Move(pos);
        collisionCapsule.Move(pos);

        //���f���̓����蔻������č\�z
        if (collisionModel != -1)
        {
            MV1SetPosition(collisionModel, pos);
            MV1SetupCollInfo(collisionModel);
        }
    }

    //�R���C�_�[�̕`��
    void GameObjectBase::DrawCollider()
    {
        //DrawLine3D(collisionLine.GetWorldStart(), collisionLine.GetWorldEnd(), GetColor(0, 0, 0));
        //DrawSphere3D(collisionSphere.GetWorldCenter(), collisionSphere.GetRadius(), 8, GetColor(255, 0, 0), GetColor(0, 0, 0), FALSE);
        //DrawCapsule3D(collisionCapsule.GetWorldStart(), collisionCapsule.GetWorldEnd(), collisionCapsule.GetRadius(), 8, GetColor(0, 255, 0), GetColor(0, 0, 0),FALSE);
        ////�R���W�������f�������݂��Ă����甼�����`��
        //if (collisionModel != -1)
        //{
        //    //�������ɂ���
        //    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
        //    MV1DrawModel(collisionModel);
        //    //���ɖ߂�
        //    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        //}
    }
}