#pragma once
#include "../../GameObjectBase/GameObjectBase.h"

namespace Calculation
{
    /// <summary>
    /// �X�e�[�W�֘A�������s���N���X
    /// </summary>
    class Stage : public GameObjectBase
    {
    public:
        /// <summary>
        /// Stage�N���X�̃C���X�^���X�𐶐�
        /// </summary>
        /// <returns>Stage�N���X�̃C���X�^���X</returns>
        static Stage* CreateInstance();

        /// <summary>
        /// Stage�N���X�̃C���X�^���X��j��
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
        void Update(float deltaTime)override {}

        /// <summary>
        /// �`�揈��
        /// </summary>
        void Draw()override;

    private:
        /// <summary>
        /// �R���X�g���N�^�i�V���O���g���j
        /// </summary>
        Stage();

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Stage();

        /// <summary>
        /// ���f���̓ǂݍ���
        /// </summary>
        void ModelLoad();

        //Stage�N���X�̃C���X�^���X��ێ�
        static Stage* Instance;

        //�X�e�[�W�̏������W
        const VECTOR StagePos = VGet(0, -255, 0);
    };
}

