#include "DxLib.h"
#include "GameObjectManager.h"
#include "GameObjectBase.h"

namespace Calculation
{
    GameObjectManager* GameObjectManager::Instance = nullptr;

    GameObjectManager::~GameObjectManager()
    {
        ReleaseAllObj();
    }

    /**
    * GameObjectManager�̃C���X�^���X�𐶐�����
    * @note static���\�b�h������Ŏg�p����ۂɕK�v
    */
    void GameObjectManager::InstanceCreate()
    {
        if (!Instance)
        {
            Instance = new GameObjectManager;
        }
    }

    /**
    * GameObjectManager�̌�n������
    * @detail �A�v���P�[�V�����I���O�ɌĂяo���A�}�l�[�W�����m�ۂ����̈��
    * �}�l�[�W�����g�̉���������s���B
    */
    void GameObjectManager::InstanceDestory()
    {
        ReleaseAllObj();
        if (Instance)
        {
            delete Instance;
            Instance = nullptr;
        }
    }

    /**
    * Gameobject��Manager�ɒǉ�
    * @param[in] �V�K�쐬�Q�[���I�u�W�F�N�g
    * @detail �V�KGameObject��Manager�ɒǉ�����
    * �����ňꎞ�ۊǂ��ꂽ��AUpdate���\�b�h���Ń^�O���Ƃɕ��ނ���Ǘ������
    */
    void GameObjectManager::Entry(GameObjectBase* newObj)
    {
        Instance->PendingObjects.push_back(newObj);
    }

    /**
    * GameObject��Manager����폜
    * @param[in] releaseObj �폜�������I�u�W�F�N�g�̃|�C���^
    * @detail �폜�����I�u�W�F�N�g�̃|�C���^��Manager���Ō������폜����
    */
    void GameObjectManager::Release(GameObjectBase* releaseObj)
    {
        //�y���f�B���O�I�u�W�F�N�g�����猟��
        auto itr = std::find(Instance->PendingObjects.begin(), Instance->PendingObjects.end(), releaseObj);
        if (itr != Instance->PendingObjects.end())
        {
            //�������I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������
            std::iter_swap(itr, Instance->PendingObjects.end() - 1);
            Instance->PendingObjects.pop_back();

            return;
        }

        //�������I�u�W�F�N�g�̃^�O�𓾂�
        ObjectTag tag = releaseObj->GetTag();

        //�A�N�e�B�u�I�u�W�F�N�g�Ȃ�����폜�I�u�W�F�N�g������
        itr = std::find(Instance->Objects[tag].begin(), Instance->Objects[tag].end(), releaseObj);
        if (itr != Instance->Objects[tag].end())
        {
            //�������I�u�W�F�N�g�𖖔��Ɉړ����A�폜
            std::iter_swap(itr, Instance->Objects[tag].end() - 1);
            delete Instance->Objects[tag].back();
        }
    }

    //�S�I�u�W�F�N�g�폜
    void GameObjectManager::ReleaseAllObj()
    {
        //��������y���f�B���O�I�u�W�F�N�g��S�č폜
        while (!Instance->PendingObjects.empty())
        {
            delete Instance->PendingObjects.back();
        }
        
        //�S�ẴA�N�e�B�u�I�u�W�F�N�g���폜
        for (auto& tag : ObjectTagAll)
        {
            //��������폜
            while (!Instance->Objects[tag].empty())
            {
                delete Instance->Objects[tag].back();
                Instance->Objects[tag].pop_back();
            }
        }
    }

    /**
    * �S�I�u�W�F�N�g�̍X�V����
    * @detail �S�I�u�W�F�N�g��Update���\�b�h���Ă񂾌�A
    * �V�K�I�u�W�F�N�g���A�N�e�B�u���X�g�ɒǉ�
    * ���S�I�u�W�F�N�g���A�N�e�B�u���X�g����폜
    */
    void GameObjectManager::Update(float deltaTime)
    {
        for (auto& tag : ObjectTagAll)
        {
            for (int i = 0; i < Instance->Objects[tag].size(); i++)
            {
                Instance->Objects[tag][i]->Update(deltaTime);
            }
        }
    }

    void GameObjectManager::Draw()
    {
    }

    void GameObjectManager::Collision()
    {
    }

    GameObjectBase* GameObjectManager::GetFirstGameObject(ObjectTag tag)
    {
        return nullptr;
    }


}