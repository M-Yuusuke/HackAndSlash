#include "DxLib.h"
#include "AnimationController.h"
#include "../AssetManager/AssetManager.h"

namespace Calculation
{
    /**
    * �R���X�g���N�^
    * @param[in] modelHandle �A�j���[�V������K�p���郂�f���n���h��
    */
    AnimationController::AnimationController(int modelHandle) :
        ModelHandle(modelHandle),
        NowAnimTypeNum(-1),
        NowAnimTime(0),
        AttachedIndex(0)
    {
    }

    AnimationController::~AnimationController()
    {
    }

    /**
    * �A�j���[�V�����̒ǉ�
    * @param[in] animFileName �ǉ��������A�j���[�V�����t�@�C����
    * @param[in] animFps �A�j���[�V�����̍Đ����x(�ȗ��B�f�t�H���g��30fps)
    * @param[in] isLoop �A�j���[�V���������[�v�����邩(�ȗ��B�f�t�H���g�Ń��[�v������)
    * @return int �A�j���[�V�����Đ��pID
    * @details �R���X�g���N�^�Ŏw�肵�����f���n���h���ɑ΂��A�A�j���[�V������ǉ�����
    * �A�j���[�V�������ǉ��ł������̓A�j���[�V�����Đ�ID��Ԃ��B���s����-1��Ԃ�
    */
    int AnimationController::AddAnimation(std::string animFileName, float animFps, bool isLoop)
    {
        AnimData Anim;
        Anim.AnimationPlayFps = animFps;
        Anim.LoopAnimation = isLoop;

        //�A�j���[�V�����f�[�^�ǂݍ���
        Anim.AnimationHandle = AssetManager::GetAnimation(animFileName.c_str());
        if (Anim.AnimationHandle == -1)
        {
            return -1;
        }
        Anim.AnimationIndex = MV1GetAnimNum(Anim.AnimationHandle) - 1;

        //���f���ɃA�j���[�V�������A�^�b�`
        AttachedIndex = MV1AttachAnim(ModelHandle, Anim.AnimationIndex, Anim.AnimationHandle, TRUE);
        Anim.AnimationTotalTime = MV1GetAnimTotalTime(Anim.AnimationHandle, Anim.AnimationIndex);

        //�A�j���[�V��������
        int Test;
        Test = MV1DetachAnim(ModelHandle, AttachedIndex);

        //�����ɃA�j���[�V�����f�[�^��ǉ�
        AnimDatas.push_back(Anim);
        //vector�ɓ���Y�����ԍ���Ԃ�
        return static_cast<int> (AnimDatas.size() - 1);
    }

    /**
    * �A�j���[�V�����̑���������ݒ�
    * @param[in] deltaTime 1�t���[���̑������� �b�P��
    * @detailes StartAnimation�Őݒ肳�ꂽ�A�j���[�V�����̍Đ���i�߂�B
    * ���t���[��AddAnimationTime���Ăяo���K�v������
    */
    void AnimationController::AddAnimaitonTime(float deltaTime)
     {
        NowAnimTime += deltaTime * AnimDatas[NowAnimTypeNum].AnimationPlayFps;
        if (AnimDatas[NowAnimTypeNum].LoopAnimation &&
            NowAnimTime > AnimDatas[NowAnimTypeNum].AnimationTotalTime)
        {
            NowAnimTime = 0;
        }
        int Test;
        Test = MV1SetAttachAnimTime(ModelHandle, AttachedIndex, NowAnimTime);
    }

    /**
    * �A�j���[�V�����̍Đ����J�n
    * @param[in] animID 
    * 
    * @detailes animID�Ŏw�肵���A�j���[�V�����̍Đ����J�n����
    * �������A�j���[�V�������w�肳�ꂽ�ꍇ�A�n�߂���Đ�����
    */
    void AnimationController::StartAnimaiton(int animID)
    {
        //�ȑO�̃A�j���[�V�����ƈႤ�A�j���[�V�������������x�f�^�b�`
        if (animID != NowAnimTypeNum)
        {
            if (NowAnimTypeNum != -1)
            {
                MV1DetachAnim(ModelHandle, AttachedIndex);
            }
            //�V�K�A�j���[�V�������Z�b�g
            NowAnimTypeNum = animID;
            AttachedIndex = MV1AttachAnim(ModelHandle, AnimDatas[animID].AnimationIndex, AnimDatas[NowAnimTypeNum].AnimationHandle, TRUE);
        }
        NowAnimTime = 0.0f;
        MV1SetAttachAnimTime(ModelHandle, AttachedIndex, NowAnimTime);
    }

    /**
    * ���ݎw�肳��Ă���A�j���[�V�����̍Đ����I��
    * @detailes ���ݎw�肳��Ă���A�j���[�V�������I�������ŃX�g�b�v����
    * �Đ��r���̃|�[�Y�Ŏ~�܂�Ȃ����Ƃɒ��ӁB���[�v�Đ��w��̃A�j���[�V�����͖��������
    */
    void AnimationController::StopAnimation()
    {
        NowAnimTime = AnimDatas[NowAnimTypeNum].AnimationTotalTime;
    }

    /**
    * ���ݎw�肳��Ă���A�j���[�V�����͍Đ������H
    * @return true:�Đ��� false:�Đ��I��
    * @detailes ���ݎw�肳��Ă���A�j���[�V�������Đ�������Ԃ�
    * ���[�v�w�肳�ꂽ���̂͏��true��Ԃ�
    */
    bool AnimationController::IsPlaying()
    {
        if (AnimDatas[NowAnimTypeNum].LoopAnimation &&
            NowAnimTime > AnimDatas[NowAnimTypeNum].AnimationTotalTime)
        {
            return false;
        }
        return true;
    }

    /**�A�j���[�V�����f�[�^�\���� �R���X�g���N�^*/
    AnimationController::AnimData::AnimData() :
        AnimationHandle(-1),
        AnimationIndex(-1),
        AnimationTotalTime(-1),
        AnimationPlayFps(0),
        LoopAnimation(false)
    {
    }
}