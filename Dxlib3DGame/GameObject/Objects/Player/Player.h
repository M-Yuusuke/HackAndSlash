#pragma once
#include "../GameObject/Objects/CharacterBase/CharacterBase.h"

namespace Calculation
{
    /// <summary>
    /// �v���C���[�֘A�������s���N���X
    /// </summary>
    class Player : public CharacterBase
    {
    public:

        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Player();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Player();

        /// <summary>
        /// ����������
        /// </summary>
        void Initialize()override;

        /// <summary>
        /// �X�V����
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime)override;

        /// <summary>
        /// �`�揈��
        /// </summary>
        void Draw()override;

        /// <summary>
        /// �����蔻�菈��
        /// </summary>
        /// <param name="other">�������Ă���I�u�W�F�N�g�̃|�C���^</param>
        void OnCollisionEnter(GameObjectBase* other)override;



    private:
        /// <summary>
        /// ���f���̓ǂݍ���
        /// </summary>
        void ModelLoad()override;

        /// <summary>
        /// ���͏���
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Move(float deltaTime)override;

        /// <summary>
        /// �U���֘A����
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Attack(float deltaTime);

        /// <summary>
        /// �G�l�~�[�Ƃ̓����蔻��
        /// </summary>
        /// <param name="other">�G�l�~�[�̃|�C���^</param>
        void OnCollisionEnemy(CharacterBase* other);

        /// <summary>
        /// �_���[�W���󂯂鏈��
        /// </summary>
        void OnDamage()override;

        //�v���C���[�̑傫��
        const VECTOR PlayerScale = { 0.8f,0.8f, 0.8f };
        //�v���C���[�̏������W
        const VECTOR FirstPos = { 0,0,0 };
        //�v���C���[�̏�������
        const VECTOR FirstDir = { 0,0,1 };

        //���̏������[�J�����W
        const VECTOR FirstLocalPos = { 0, 50.0f, 0 };

        //�J�v�Z���̎n�_
        const VECTOR CapsuleStart = { 0, 100.0f, 0 };
        //�J�v�Z���̏I�_ 
        const VECTOR CapsuleEnd = { 0, 20.0f, 0 };

        //��̊p�x
        const float Theta = 0.5f;  //cos60��
        //�ʏ�U���͈̔�
        const float Range = 200.0f;

        ////��������̐����̎n�_
        //const VECTOR LineStart = { 0,20.0f,0 };
        ////��������̐����̏I�_
        //const VECTOR LineEnd = { 0,-30.0f,0 };

        //����̓����蔻��̔��a
        const float Radius = 40.0f;
        //���̓x�N�g���̍ŏ��l
        const float InputVecMin = 0.5f;
        //�ړ����x
        const float MoveVelocity = 200.0f;
        //��]���x
        const float RotateVelocity = 10.0f;
        //�̗͂̏���l
        const int MaxHP = 100;

        //�Q�[���p�b�h���͏��
        XINPUT_STATE gamePadState;
        int HP;
        bool attack;
    };
}