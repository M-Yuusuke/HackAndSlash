#include "Crystal.h"
#include "../GameObject/AssetManager/AssetManager.h"

namespace Calculation
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Crystal::Crystal(VECTOR pos):
        GameObjectBase(ObjectTag::Crystal, pos)
    {
        ModelLoad();
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    Crystal::~Crystal()
    {
    }

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
    void Crystal::Update(float deltaTime)
    {
    }

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Crystal::Draw()
    {
        MV1DrawModel(modelHandle);
    }

    /// <summary>
    /// �����蔻�菈��
    /// </summary>
    /// <param name="other">�Փˌ��m���������I�u�W�F�N�g</param>
    void Crystal::OnCollisionEnter(GameObjectBase* other)
    {
        ObjectTag tag = other->GetTag();
        if (ObjectTag::Player == tag)
        {
            //�v���C���[�ƏՓ˂����ꍇ�̏���
        }
    }

    /// <summary>
    /// ���f���ǂݍ���
    /// </summary>
    void Crystal::ModelLoad()
    {
        //���f�����[�h
        modelHandle = AssetManager::GetMesh("../Data/Assets/EXP/Model.mv1");

        //���̂܂܂��ƃX�e�[�W�ɑ΂��ă��f�����傫���̂ŏk��
        MV1SetScale(modelHandle, Scale);
        //���f����z�u
        MV1SetPosition(modelHandle, pos);
    }
}