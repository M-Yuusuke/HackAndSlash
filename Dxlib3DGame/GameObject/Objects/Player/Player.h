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
        void OnCollisionEnter(const GameObjectBase* other)override;

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

        ///// <summary>
        ///// �v���C���[�ƃX�e�[�W�̓����蔻��
        ///// </summary>
        ///// <param name="other">�������Ă���I�u�W�F�N�g�̃|�C���^</param>
        //void OnCollisionStage(const GameObjectBase* other);


        //�v���C���[�̑傫��
        const VECTOR PlayerScale = { 0.8f,0.8f, 0.8f };
        //�v���C���[�̏������W
        const VECTOR FirstPos = { 100.0f,0,0 };
        //�v���C���[�̏�������
        const VECTOR FirstDir = { 0,0,1 };
        //���̏������[�J�����W
        const VECTOR FirstLocalPos = { 0, 50.0f, 0 };
        //��������̐����̎n�_
        const VECTOR LineStart = { 0, 20.0f, 0 };
        //��������̐����̏I�_
        const VECTOR LineEnd = { 0, -30.0f, 0 };

        //����̓����蔻��̔��a
        const float Radius = 30.0f;
        //���̓x�N�g���̍ŏ��l
        const float InputVecMin = 0.5f;
        //�ړ����x
        const float MoveVelocity = 200.0f;
        //��]���x
        const float RotateVelocity = 10.0f;

        //�Q�[���p�b�h���͏��
        XINPUT_STATE gamePadState;
        //���͏��
        bool input;
        bool attack;
    };
}