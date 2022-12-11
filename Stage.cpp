#include "DxLib.h"
#include "Stage.h"
#include "VectorCalculation.h"
#include "ObjectTag.h"
#include "AssetManager.h"
#include "GameObjectManager.h"

namespace Calculation
{
    Stage* Stage::Instance = nullptr;

    Stage::Stage():
        GameObjectBase(ObjectTag::Stage)
    {
        Pos = StagePos;
        ModelLoad();
    }

    Stage::~Stage()
    {
        AssetManager::ReleaseMesh(ModelHandle);
        AssetManager::ReleaseMesh(CollisionModel);
        GameObjectManager::Release(Instance);
        ModelHandle = -1;
        CollisionModel = -1;
    }

    Stage* Stage::CreateInstance()
    {
        if (!Instance)
        {
            Instance = new Stage;
            //�X�e�[�W���Q�[���I�u�W�F�N�g�}�l�[�W���ɓo�^
            GameObjectManager::Entry(Instance);
        }
        return Instance;
    }

    void Stage::DestoryInstance()
    {
        if (Instance)
        {
            delete Instance;
            Instance = nullptr;
        }
    }

    /**�X�e�[�W���f���ǂݍ���*/
    void Stage::ModelLoad()
    {
        //�\�����f���ǂݍ���&�X�P�[�����O&�ʒu�Z�b�g
        ModelHandle = AssetManager::GetMesh("../Data/Assets/Stage/maptest2.mv1");
        MV1SetScale(ModelHandle, VGet(1.0f, 1.0f, 1.0f));
        MV1SetPosition(ModelHandle, Pos);

        //�����蔻�胂�f���ǂݍ���&�X�P�[�����O&�����蔻����\�z
        CollisionModel = AssetManager::GetMesh("../Data/Assets/Stage/HitMesh2rot.mv1");
        MV1SetScale(CollisionModel, VGet(1.0f, 1.0f, 1.0f));
        MV1SetOpacityRate(CollisionModel, 0.3f);

        //�\�����f���Ɠ����蔻�胂�f���̈ʒu�𒲐�
        MV1SetPosition(CollisionModel, Pos + VGet(-45, 200, -35));
        MV1SetupCollInfo(CollisionModel);
    }

    void Stage::Initialize()
    {
        //���f���f�[�^���Ȃ�������ǂݍ���
        if (ModelHandle == -1 && CollisionModel == -1)
        {
            ModelLoad();
        }
    }

    void Stage::Draw()
    {
        MV1DrawModel(ModelHandle);
        DrawCollider();
    }
}