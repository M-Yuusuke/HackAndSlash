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
        modelHandle(modelHandle),
        nowAnimTypeNum(-1),
        nowAnimTime(0),
        attachedIndex(0)
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
        Anim.animationPlayFps = animFps;
        Anim.loopAnimation = isLoop;

        //�A�j���[�V�����f�[�^�ǂݍ���
        Anim.animationHandle = AssetManager::GetAnimation(animFileName.c_str());
        if (Anim.animationHandle == -1)
        {
            return -1;
        }
        Anim.animationIndex = MV1GetAnimNum(Anim.animationHandle) - 1;

        //���f���ɃA�j���[�V�������A�^�b�`
        attachedIndex = MV1AttachAnim(modelHandle, Anim.animationIndex, Anim.animationHandle, TRUE);
        Anim.animationTotalTime = MV1GetAnimTotalTime(Anim.animationHandle, Anim.animationIndex);

        //�A�j���[�V��������
        int Test;
        Test = MV1DetachAnim(modelHandle, attachedIndex);

        //�����ɃA�j���[�V�����f�[�^��ǉ�
        animDatas.push_back(Anim);
        //vector�ɓ���Y�����ԍ���Ԃ�
        return static_cast<int> (animDatas.size() - 1);
    }

    /**
    * �A�j���[�V�����̑���������ݒ�
    * @param[in] deltaTime 1�t���[���̑������� �b�P��
    * @detailes StartAnimation�Őݒ肳�ꂽ�A�j���[�V�����̍Đ���i�߂�B
    * ���t���[��AddAnimationTime���Ăяo���K�v������
    */
    void AnimationController::AddAnimaitonTime(float deltaTime)
     {
        nowAnimTime += deltaTime * animDatas[nowAnimTypeNum].animationPlayFps;
        if (animDatas[nowAnimTypeNum].loopAnimation &&
            nowAnimTime > animDatas[nowAnimTypeNum].animationTotalTime)
        {
            nowAnimTime = 0;
        }
        int Test;
        Test = MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
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
        if (animID != nowAnimTypeNum)
        {
            if (nowAnimTypeNum != -1)
            {
                MV1DetachAnim(modelHandle, attachedIndex);
            }
            //�V�K�A�j���[�V�������Z�b�g
            nowAnimTypeNum = animID;
            attachedIndex = MV1AttachAnim(modelHandle, animDatas[animID].animationIndex, animDatas[nowAnimTypeNum].animationHandle, TRUE);
        }
        nowAnimTime = 0.0f;
        MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
    }

    /**
    * ���ݎw�肳��Ă���A�j���[�V�����̍Đ����I��
    * @detailes ���ݎw�肳��Ă���A�j���[�V�������I�������ŃX�g�b�v����
    * �Đ��r���̃|�[�Y�Ŏ~�܂�Ȃ����Ƃɒ��ӁB���[�v�Đ��w��̃A�j���[�V�����͖��������
    */
    void AnimationController::StopAnimation()
    {
        nowAnimTime = animDatas[nowAnimTypeNum].animationTotalTime;
    }

    /**
    * ���ݎw�肳��Ă���A�j���[�V�����͍Đ������H
    * @return true:�Đ��� false:�Đ��I��
    * @detailes ���ݎw�肳��Ă���A�j���[�V�������Đ�������Ԃ�
    * ���[�v�w�肳�ꂽ���̂͏��true��Ԃ�
    */
    bool AnimationController::IsPlaying()
    {
        if (animDatas[nowAnimTypeNum].loopAnimation &&
            nowAnimTime > animDatas[nowAnimTypeNum].animationTotalTime)
        {
            return false;
        }
        return true;
    }

    /**�A�j���[�V�����f�[�^�\���� �R���X�g���N�^*/
    AnimationController::AnimData::AnimData() :
        animationHandle(-1),
        animationIndex(-1),
        animationTotalTime(-1),
        animationPlayFps(0),
        loopAnimation(false)
    {
    }
}