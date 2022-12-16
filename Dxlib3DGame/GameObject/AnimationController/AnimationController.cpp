#include "DxLib.h"
#include "AnimationController.h"
#include "../AssetManager/AssetManager.h"

namespace Calculation
{
    /**
    * コンストラクタ
    * @param[in] modelHandle アニメーションを適用するモデルハンドル
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
    * アニメーションの追加
    * @param[in] animFileName 追加したいアニメーションファイル名
    * @param[in] animFps アニメーションの再生速度(省略可。デフォルトで30fps)
    * @param[in] isLoop アニメーションをループさせるか(省略可。デフォルトでループさせる)
    * @return int アニメーション再生用ID
    * @details コンストラクタで指定したモデルハンドルに対し、アニメーションを追加する
    * アニメーションが追加できた時はアニメーション再生IDを返す。失敗時は-1を返す
    */
    int AnimationController::AddAnimation(std::string animFileName, float animFps, bool isLoop)
    {
        AnimData Anim;
        Anim.animationPlayFps = animFps;
        Anim.loopAnimation = isLoop;

        //アニメーションデータ読み込み
        Anim.animationHandle = AssetManager::GetAnimation(animFileName.c_str());
        if (Anim.animationHandle == -1)
        {
            return -1;
        }
        Anim.animationIndex = MV1GetAnimNum(Anim.animationHandle) - 1;

        //モデルにアニメーションをアタッチ
        attachedIndex = MV1AttachAnim(modelHandle, Anim.animationIndex, Anim.animationHandle, TRUE);
        Anim.animationTotalTime = MV1GetAnimTotalTime(Anim.animationHandle, Anim.animationIndex);

        //アニメーション解除
        int Test;
        Test = MV1DetachAnim(modelHandle, attachedIndex);

        //末尾にアニメーションデータを追加
        animDatas.push_back(Anim);
        //vectorに入る添え字番号を返す
        return static_cast<int> (animDatas.size() - 1);
    }

    /**
    * アニメーションの増分時刻を設定
    * @param[in] deltaTime 1フレームの増分時刻 秒単位
    * @detailes StartAnimationで設定されたアニメーションの再生を進める。
    * 毎フレームAddAnimationTimeを呼び出す必要がある
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
    * アニメーションの再生を開始
    * @param[in] animID 
    * 
    * @detailes animIDで指定したアニメーションの再生を開始する
    * お同じアニメーションが指定された場合、始めから再生する
    */
    void AnimationController::StartAnimaiton(int animID)
    {
        //以前のアニメーションと違うアニメーションが来たら一度デタッチ
        if (animID != nowAnimTypeNum)
        {
            if (nowAnimTypeNum != -1)
            {
                MV1DetachAnim(modelHandle, attachedIndex);
            }
            //新規アニメーションをセット
            nowAnimTypeNum = animID;
            attachedIndex = MV1AttachAnim(modelHandle, animDatas[animID].animationIndex, animDatas[nowAnimTypeNum].animationHandle, TRUE);
        }
        nowAnimTime = 0.0f;
        MV1SetAttachAnimTime(modelHandle, attachedIndex, nowAnimTime);
    }

    /**
    * 現在指定されているアニメーションの再生を終了
    * @detailes 現在指定されているアニメーションが終了時刻でストップする
    * 再生途中のポーズで止まらないことに注意。ループ再生指定のアニメーションは無視される
    */
    void AnimationController::StopAnimation()
    {
        nowAnimTime = animDatas[nowAnimTypeNum].animationTotalTime;
    }

    /**
    * 現在指定されているアニメーションは再生中か？
    * @return true:再生中 false:再生終了
    * @detailes 現在指定されているアニメーションが再生中かを返す
    * ループ指定されたものは常にtrueを返す
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

    /**アニメーションデータ構造体 コンストラクタ*/
    AnimationController::AnimData::AnimData() :
        animationHandle(-1),
        animationIndex(-1),
        animationTotalTime(-1),
        animationPlayFps(0),
        loopAnimation(false)
    {
    }
}