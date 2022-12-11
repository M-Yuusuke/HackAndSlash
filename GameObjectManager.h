#pragma once
#include <vector>
#include <unordered_map>
#include "GameObjectBase.h"
#include "ObjectTag.h" 

//class GameObjectBase;
//class ObjectTag;

namespace Calculation
{
    class GameObjectManager final
    {
    public:
        //���̃C���X�^���X����
        static void CreateInstance();
        //���̃C���X�^���X�j��
        static void DestoryInstance();
        //�Q�[���I�u�W�F�N�g�̓o�^
        static void Entry(GameObjectBase* newObj);
        //�Q�[���I�u�W�F�N�g�̍폜
        static void Release(GameObjectBase* releaseObj);
        //�S�I�u�W�F�N�g�폜
        static void ReleaseAllObj();

        static void Init();
        static void Update(float deltaTime);
        static void Draw();

        //�����蔻��
        void Collision();
        static GameObjectBase* GetFirstGameObject(ObjectTag tag);

    private:
        //�V���O���g��
        GameObjectManager() {}
        ~GameObjectManager() { ReleaseAllObj(); }
        //�}�l�[�W���[�̃C���X�^���X
        static GameObjectManager* Instance;

        //�ꎞ�ҋ@�I�u�W�F�N�g
        std::vector<GameObjectBase*> PendingObjects;
        //Objects�@[�^�O][�I�u�W�F�N�g��]
        std::unordered_map<ObjectTag, std::vector<GameObjectBase*>> Objects;
    };
}


