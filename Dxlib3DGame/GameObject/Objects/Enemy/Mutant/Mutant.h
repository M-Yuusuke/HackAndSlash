#pragma once
#include "../GameObject/Objects/CharacterBase/CharacterBase.h"

namespace Calculation
{
    class Mutant final : public CharacterBase 
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Mutant();
        Mutant(VECTOR pos);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Mutant();

        /// <summary>
        /// ������
        /// </summary>
        void Initialize()override;

        /// <summary>
        /// �X�V
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime)override;

        /// <summary>
        /// �����蔻�菈��
        /// </summary>
        /// <param name="other">�������Ă���I�u�W�F�N�g�̃|�C���^</param>
        void OnCollisionEnter(GameObjectBase* other)override;

        /// <summary>
        /// �_���[�W���󂯂鏈��
        /// </summary>
        void OnDamage()override;

        /// <summary>
        /// �`��
        /// </summary>
        void Draw()override;

        /// <summary>
        /// �U�������Ԃ�
        /// </summary>
        /// <returns>�U�����Ȃ�true�A�����łȂ����false</returns>
        bool GetAttack() { return attack; }

    private:
        /// <summary>
        /// ���f���E�A�j���[�V�����̓ǂݍ���
        /// </summary>
        void ModelLoad() override;

        /// <summary>
        /// �ړ�
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Move(float deltaTime)override;

        //�g�嗦
        const VECTOR Scale = { 1.0f,1.0f ,1.0f };
        //�������W
        //const VECTOR FirstPos = { 300.0f,0,0 };

        ////���̏������[�J�����W
        const VECTOR FirstLocalPos = { 0, 50.0f, 0 };

        //�J�v�Z���̎n�_
        const VECTOR CapsuleStart = { 0, 120.0f, 0 };
        //�J�v�Z���̏I�_ 
        const VECTOR CapsuleEnd = { 0, 20.0f, 0 };

        ////��������̐����̎n�_
        //const VECTOR LineStart = { 0, 20.0f, 0 };
        ////��������̐����̏I�_
        //const VECTOR LineEnd = { 0, -30.0f, 0 };

        //����̓����蔻��̔��a
        const float Radius = 50.0f;
        //�ړ����x
        const float MoveVelocity = 100.0f;
        //��̊p�x
        const float Theta = 0.5f;  //cos60��
        //�ʏ�U���͈̔�
        const float Range = 150.0f;

        //�ړ�����
        bool input;
        //�U������
        bool attack;
    };
}