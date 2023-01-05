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
        void OnCollisionEnter(const GameObjectBase* other)override;

        /// <summary>
        /// �_���[�W���󂯂鏈��
        /// </summary>
        void OnDamage() { alive = false; }

        /// <summary>
        /// �`��
        /// </summary>
        void Draw()override;

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
        const VECTOR FirstPos = { 300.0f,0,0 };
        //���̏������[�J�����W
        const VECTOR FirstLocalPos = { 0, 50.0f, 0 };
        //��������̐����̎n�_
        const VECTOR LineStart = { 0, 20.0f, 0 };
        //��������̐����̏I�_
        const VECTOR LineEnd = { 0, -30.0f, 0 };
        //����̓����蔻��̔��a
        const float Radius = 50.0f;
        //�ړ����x
        const float MoveVelocity = 100.0f;

        //�ړ�����
        bool input;
        //�U������
        bool attack;
    };
}