#pragma once
#include "../GameObject/GameObjectBase/GameObjectBase.h"
#include "../GameObject/AnimationController/AnimationController.h"
namespace Calculation
{
    class CharacterBase : public GameObjectBase
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        CharacterBase(ObjectTag tag);
        CharacterBase(ObjectTag tag, VECTOR pos);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        virtual ~CharacterBase() {}

    protected:
        /// <summary>
        /// ���f���ƃA�j���[�V�����̓ǂݍ���
        /// </summary>
        virtual void ModelLoad() = 0;
        /// <summary>
        /// �ړ�����
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        virtual void Move(float deltaTime) = 0;
        /// <summary>
        /// ��]����
        /// </summary>
        void Rotate();

        /// <summary>
        /// �v���C���[�ƃX�e�[�W�̓����蔻��
        /// </summary>
        /// <param name="other">�������Ă���I�u�W�F�N�g�̃|�C���^</param>
        void OnCollisionStage(const GameObjectBase* other);

        //��]���x
        const float RotateVelocity = 10.0f;
        //����
        VECTOR dir;
        //�ڕW����
        VECTOR aimDir;
        //���x
        VECTOR velocity;


        //�A�j���[�V�����Ǘ��p
        AnimationController* animControl;
        //�A�j���[�V�������ID
        int animTypeID;
        //��]�����ǂ���
        bool rotateNow;
    };
}