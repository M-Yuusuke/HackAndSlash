#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace Calculation
{
    class AnimationController final
    {
    public:
        AnimationController(int modelHandle);
        ~AnimationController();
        //�A�j���[�V�����̒ǉ�
        int AddAnimation(std::string animFileName, float animFps = 30.0f, bool isLoop = true);

        //�A�j���[�V�����̎��Ԃ̃Z�b�g
        void AddAnimaitonTime(float deltaTime);
        //�A�j���[�V�����̍Đ��J�n
        void StartAnimaiton(int animID);
        //�A�j���[�V�����̍Đ����X�g�b�v
        void StopAnimation();
        //���ݍĐ�����
        bool IsPlaying();

    private:
        struct AnimData
        {
        public:
            AnimData();
            int AnimationHandle;
            //�A�^�b�`����A�j���[�V�����ԍ�
            int AnimationIndex;
            //�A�j���[�V�����̑��Đ�����
            float AnimationTotalTime;
            //�A�j���[�V�����̍Đ����x
            float AnimationPlayFps;
            //���[�v�Đ��������邩
            bool LoopAnimation;
        };

        int ModelHandle;
        //�A�j���[�V���������o�^�p
        std::vector<AnimData> AnimDatas;
        //���ݍĐ����̃A�j���[�V����ID
        int NowAnimTypeNum;
        //���t����̃C���f�b�N�X
        int AttachedIndex;
        //���ݍĐ����̃A�j���[�V��������
        float NowAnimTime;
    };
}

