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

        /// <summary>
        /// �A�j���[�V�����̒ǉ�
        /// </summary>
        /// <param name="animFileName">�A�j���[�V�����̃t�@�C���p�X</param>
        /// <param name="animFps">�A�j���[�V�����Đ��̃t���[�����[�g�i�f�t�H���g��30FPS�j</param>
        /// <param name="isLoop">�A�j���[�V�����̃��[�v�Đ�</param>
        /// <returns>�A�j���[�V�����Đ��ɕK�v��ID</returns>
        int AddAnimation(std::string animFileName, float animFps = 30.0f, bool isLoop = true);

        /// <summary>
        /// �A�j���[�V�����̎��Ԃ̃Z�b�g
        /// </summary>
        /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
        void AddAnimaitonTime(float deltaTime);
        
        /// <summary>
        /// �A�j���[�V�����̍Đ��J�n
        /// </summary>
        /// <param name="animID">�A�j���[�V����ID</param>
        void StartAnimaiton(int animID);

        /// <summary>
        /// �A�j���[�V�����̍Đ����X�g�b�v
        /// </summary>
        void StopAnimation();

        /// <summary>
        /// ���ݍĐ�����
        /// </summary>
        /// <returns>�Đ����Ȃ�true�A��~���Ă����false</returns>
        bool IsPlaying();

    private:
        struct AnimData
        {
        public:
            AnimData();
            int animationHandle;
            //�A�^�b�`����A�j���[�V�����ԍ�
            int animationIndex;
            //�A�j���[�V�����̑��Đ�����
            float animationTotalTime;
            //�A�j���[�V�����̍Đ����x
            float animationPlayFps;
            //���[�v�Đ��������邩
            bool loopAnimation;
        };

        int modelHandle;
        //�A�j���[�V���������o�^�p
        std::vector<AnimData> animDatas;
        //���ݍĐ����̃A�j���[�V����ID
        int nowAnimTypeNum;
        //���t����̃C���f�b�N�X
        int attachedIndex;
        //���ݍĐ����̃A�j���[�V��������
        float nowAnimTime;
    };
}

