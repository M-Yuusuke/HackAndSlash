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

    /// <summary>
    /// アニメーションの追加
    /// </summary>
    /// <param name="animFileName">アニメーションのファイルパス</param>
    /// <param name="animFps">アニメーション再生のフレームレート（省略可。デフォルトで30fps）</param>
    /// <param name="isLoop">アニメーションのループ再生させるか（省略可。デフォルトでループさせる）</param>
    /// <returns>アニメーション再生に必要なID</returns>
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

    /// <summary>
     /// アニメーションの増分時刻を設定
     /// 毎フレームAddAnimationを呼び出す必要がある
     /// </summary>
     /// <param name="deltaTime">1フレームの経過時間</param>
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

    /// <summary>
    /// アニメーションの再生開始
    /// 同じアニメーションが指定された場合、始めから再生する
    /// </summary>
    /// <param name="animID">アニメーションID</param>
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

    /// <summary>
    /// アニメーションの再生をストップ
    /// </summary>
    void AnimationController::StopAnimation()
    {
        nowAnimTime = animDatas[nowAnimTypeNum].animationTotalTime;
    }

    /// <summary>
    /// 現在再生中か
    /// </summary>
    /// <returns>再生中ならtrue、停止していればfalse</returns>
    bool AnimationController::IsPlaying()
    {
        if (animDatas[nowAnimTypeNum].loopAnimation &&
            nowAnimTime > animDatas[nowAnimTypeNum].animationTotalTime)
        {
            return false;
        }
        return true;
    }

    /// <summary>
    /// アニメーションデータ構造体 コンストラクタ
    /// </summary>
    AnimationController::AnimData::AnimData() :
        animationHandle(-1),
        animationIndex(-1),
        animationTotalTime(-1),
        animationPlayFps(0),
        loopAnimation(false)
    {
    }
}