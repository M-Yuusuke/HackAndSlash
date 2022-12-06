#include "DxLib.h"
#include "AssetManager.h"
#include "VectorCalculation.h"

namespace Calculation
{
    AssetManager* AssetManager::Instance = nullptr;
    AssetManager::~AssetManager()
    {
        ReleaseAllAsset();
    }

    /**
    * AssetManager�̃C���X�^���X�𐶐�����
    * @note static���\�b�h������Ŏg�p����ۂɕK�v
    */
    void Calculation::AssetManager::CreateInstance()
    {
        if (!Instance)
        {
            Instance = new AssetManager;
        }
    }

    /**
    * AssetManager�̌�n������
    * @detail �A�v���P�[�V�����I���O�ɌĂяo���A�}�l�[�W�����m�ۂ����̈��
    * �}�l�[�W�����g�̉���������s���B
    */
    void Calculation::AssetManager::DestoryInstance()
    {
        if (Instance)
        {
            delete Instance;
            Instance = nullptr;
        }
    }

    /**
    * ���b�V���̎擾
    * @param[in] meshFileName �擾���������b�V���t�@�C����
    * @return int ���b�V���n���h��
    * 
    * @detailes ���b�V��(���f��)�n���h�����擾����
    * �����t�@�C������2�x�ȏ�w�肵���Ƃ��̓t�@�C���ǂݍ��݂͍s��ꂸ�A�������ꂽ�n���h����Ԃ�
    * �t�@�C����������Ȃ��Ƃ���-1��Ԃ�
    */
    int AssetManager::GetMesh(std::string meshFileName)
    {
        int meshID = 0;
        //�A�z�z��ɓ����f�[�^���o�^����Ă��Ȃ����𒲂ׂ�
        auto iter = Instance->MeshMap.find(meshFileName);

        //������Ȃ������ꍇ�͓ǂݍ��݂��s���A�A�z�z��ɋL�^����
        if (iter == Instance->MeshMap.end())
        {
            meshID = MV1LoadModel(meshFileName.c_str());
            if (meshID == -1)
            {
                return -1;
            }
            Instance->MeshMap.emplace(meshFileName, meshID);
        }
        //�V�K�ǂݍ��݂�2��ߓǂݍ��݂��A�����������̂�Ԃ�
        //���b�V�����g���L�����N�^�[�����������ꍇ�ɁA���{���������ƑS�������č��邽��
        //���b�V���̃R�s�[�폜�p��DuplivateMash�ɕۑ�
        meshID = MV1DuplicateModel(Instance->MeshMap[meshFileName]);
        Instance->DuplicatesMesh.push_back(meshID);
        return meshID;
    }

    /**
    * �A�j���[�V�����̓ǂݍ���
    * @param[in] animaitonFileName �ǂݍ��݂����A�j���[�V�����t�@�C����
    * @return int �A�j���[�V�����n���h��
    * 
    * @details �A�j���[�V�������t�@�C���ǂݍ��݂��A�A�j���[�V�����n���h����Ԃ�
    * �����t�@�C������2�x�ȏ�ǂݍ��܂ꂽ�ꍇ�́A�ǂݍ��݂��s�킸�A�n���h���̂ݕԂ�
    * �A�j���[�V�����͕�������Ȃ�
    */
    int AssetManager::GetAnimation(std::string animationFileName)
    {
        int animID = 0;
        auto iter = Instance->AnimationMap.find(animationFileName);
        //������Ȃ������ꍇ�͓ǂݍ��݂��s���A�A�z�z��ɋL�^����
        if (iter == Instance->AnimationMap.end())
        {
            animID = MV1LoadModel(animationFileName.c_str());
            if (animID == -1)
            {
                return -1;
            }
            Instance->AnimationMap.emplace(animationFileName, animID);
        }
        //�o�^���ꂽ�A�j���[�V����ID��Ԃ�
        return Instance->AnimationMap[animationFileName];
    }

    /**
    * ���b�V���̉��
    * @param[in] meshID ������������f���n���h��
    * 
    * @details�@�����T�ꂽ���f���n���h�����������
    * �������ꂽ���f���n���h���Ȃ̂ŁA�S�������Ă����{�̃��f���n���h���͎c��
    */
    void AssetManager::ReleaseMesh(int meshID)
    {
        //Duplicate�̒��̃��b�V�����������A�폜
        auto iter = std::find(Instance->DuplicatesMesh.begin(), Instance->DuplicatesMesh.end(), meshID);
        if (iter == Instance->DuplicatesMesh.end())
        {
            //������Ȃ�����
            return;
        }
        MV1DeleteModel(meshID);
        //�����̃f�[�^�Ɠ���ւ��Ė������폜
        std::iter_swap(iter, Instance->DuplicatesMesh.end() - 1);
        Instance->DuplicatesMesh.pop_back();
    }

    /**
    * �S�Ẵ��b�V���̉��
    * 
    * @details �����A���{�̃��f���n���h���A�A�j���[�V������S�ĉ������
    * �A�v���P�[�V�����̏I������Dxlib_End()���O�ɌĂяo���K�v������B
    */
    void AssetManager::ReleaseAllAsset()
    {
        //�S�ẴA�j���[�V���������
        for (auto iter = Instance->AnimationMap.begin(); iter != Instance->AnimationMap.end(); iter++)
        {
            MV1DeleteModel(iter->second);
        }
        //�S�Ẵ��f�����������
        for (auto iter = Instance->MeshMap.begin(); iter != Instance->MeshMap.end(); iter++)
        {
            MV1DeleteModel(iter->second);
        }
        //�S�Ă̕������f�����폜�폜����
        for (auto iter = Instance->DuplicatesMesh.begin(); iter != Instance->DuplicatesMesh.end(); iter++)
        {
            MV1DeleteModel(*iter);
        }

        Instance->AnimationMap.clear();
        Instance->MeshMap.clear();
        Instance->DuplicatesMesh.clear();
    }
}