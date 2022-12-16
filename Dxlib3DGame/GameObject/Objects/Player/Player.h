#pragma once
#include "../GameObject/GameObjectBase/GameObjectBase.h"
#include "../GameObject/AnimationController/AnimationController.h"

namespace Calculation
{
    /// <summary>
    /// Player�֘A�������s���N���X
    /// </summary>
    class Player : public GameObjectBase
    {
    public:
        /// <summary>
        /// Player�N���X�̃C���X�^���X����
        /// </summary>
        /// <returns>Player�N���X�̃C���X�^���X</returns>
        static Player* CreateInstance();

        /// <summary>
        /// Player�N���X�̃C���X�^���X�j��
        /// </summary>
        static void DestoryInstance();

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
        /// �R���X�g���N�^�i�V���O���g���j
        /// </summary>
        Player();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Player();
        /// <summary>
        /// ���f���̓ǂݍ���
        /// </summary>
        void ModelLoad();

        /// <summary>
        /// ���͏���
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Move(float deltaTime);

        /// <summary>
        /// ��]����
        /// </summary>
        void Rotate();

        //Player�N���X�̃C���X�^���X��ێ�
        static Player* Instance;

        //�v���C���[�̑傫��
        //const VECTOR PlayerScale = { 0.8f,0.8f, 0.8f };
        const VECTOR PlayerScale = { 0.01f,0.01f, 0.01f };
        //���̏������[�J�����W
        const VECTOR firstLocalPos = { 0, 50.0f, 0 };
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

        //��]����
        bool rotateNow;
    };
}