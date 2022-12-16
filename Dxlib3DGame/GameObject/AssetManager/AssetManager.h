#pragma once
#include <atlstr.h>
#include <unordered_map>
#include <vector>

namespace Calculation
{
    class AssetManager final
    {
    public:
        //�C���X�^���X����
        static void CreateInstance();
        //�C���X�^���X�j��
        static void DestroyInstance();
        //���b�V��(���f��)�̎擾
        static int GetMesh(std::string meshFileName);
        //�A�j���[�V�����̎擾
        static int GetAnimation(std::string animationFileName);
        //���b�V��(���f��)�̍폜
        static void ReleaseMesh(int meshID);
        //�S���b�V���E�A�j���[�V�����̍폜
        static void ReleaseAllAsset();

    private:
        //�V���O���g��
        AssetManager() {}
        ~AssetManager() { ReleaseAllAsset(); }
        static AssetManager* Instance;

        //���b�V�����{(���{�Ƃ��ĕۑ������s���ADuplicate���ꂽ���̂�Ԃ�)
        std::unordered_map<std::string, int> MeshMap;
        //�A�j���[�V�������{
        std::unordered_map < std::string, int> AnimationMap;
        //���b�V�����R�s�[��������(������g�p����)
        std::vector<int> DuplicatesMesh;
    };
}


