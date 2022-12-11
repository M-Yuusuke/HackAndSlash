#pragma once
#include "DxLib.h"
#include "GameObjectBase.h"
namespace Calculation
{
    /**�X�e�[�W�I�u�W�F�N�g�N���X*/
    class Stage : public GameObjectBase
    {
    public:
        static Stage* CreateInstance();
        static void DestoryInstance();

        void ModelLoad();
        void Initialize()override;
        void Update(float deltaTime)override { ; }
        void Draw()override;
    private:
        Stage();
        ~Stage();
        static Stage* Instance;

        const VECTOR StagePos = VGet(0, -255, 0);
    };
}

