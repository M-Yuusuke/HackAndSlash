#pragma once
#include "../../GameObjectBase/GameObjectBase.h"

namespace Calculation 
{
    /// <summary>
    /// �J�����֘A�������s���N���X
    /// </summary>
    class Camera : public GameObjectBase
    {
    public:
        /// <summary>
        /// Camera�N���X�̃C���X�^���X����
        /// </summary>
        /// <returns>Camera�N���X�̃C���X�^���X</returns>
        static Camera* CreateInstance();

        /// <summary>
        /// Camera�N���X�̃C���X�^���X�j��
        /// </summary>
        static void DestroyInstance();

        /// <summary>
        /// ����������
        /// </summary>
        void Initialize()override;

        /// <summary>
        /// �X�V����
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime) override;

    private:
        /// <summary>
        /// �R���X�g���N�^�i�V���O���g���j
        /// </summary>
        Camera();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Camera();
        //Camera�N���X�̃C���X�^���X��ێ�
        static Camera* Instance;

        //�J�����̃o�l�萔
        const float CameraSpringStrength = 2.0f;
        //�J�����̏������W
        const VECTOR firstCameraPos = { 0,500,-500 };

        //�`�拗���̉���
        const float Near = 10.0f;
        //�`�拗���̏��
        const float Far = 3000.0f;

        //�J�����̒��ړ_
        VECTOR lookPos;
        //�v���C���[����̑��Έʒu
        VECTOR cameraOffset;
        //�J�����ڕW�ʒu
        VECTOR aimCameraPos;
        //�J�������ړ_�ڕW
        VECTOR aimLookPos;

    };
}


