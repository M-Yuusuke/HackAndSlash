#pragma once
#include "../GameObject/GameObjectBase/GameObjectBase.h"

namespace Calculation
{
    class Crystal : public GameObjectBase
    {
    public:
        /// <summary>
        /// �R���X�g���N�^
        /// </summary>
        Crystal(VECTOR pos);

        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~Crystal();

        /// <summary>
        /// �X�V����
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void Update(float deltaTime)override;

        /// <summary>
        /// �`�揈��
        /// </summary>
        void Draw();

        /// <summary>
        /// �����蔻�菈��
        /// </summary>
        /// <param name="other">�Փˌ��m���������I�u�W�F�N�g</param>
        void OnCollisionEnter(GameObjectBase* other)override;

    private:
        /// <summary>
        /// ���f���ǂݍ���
        /// </summary>
        void ModelLoad();

        //�N���X�^���̃T�C�Y
        const VECTOR Scale = { 0.1f,0.1f,0.1f };
    };
}

