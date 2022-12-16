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
        Anim.AnimationPlayFps = animFps;
        Anim.LoopAnimation = isLoop;

        //アニメーションデータ読み込み
        Anim.AnimationHandle = AssetManager::GetAnimation(animFileName.c_str());
        if (Anim.AnimationHandle == -1)
        {
            return -1;
        }
        Anim.AnimationIndex = MV1GetAnimNum(Anim.AnimationHandle) - 1;

        //モデルにアニメーションをアタッチ
        AttachedIndex = MV1AttachAnim(ModelHandle, Anim.AnimationIndex, Anim.AnimationHandle, TRUE);
        Anim.AnimationTotalTime = MV1GetAnimTotalTime(Anim.AnimationHandle, Anim.AnimationIndex);

        //アニメーション解除
        int Test;
        Test = MV1DetachAnim(ModelHandle, AttachedIndex);

        //末尾にアニメーションデータを追加
        AnimDatas.push_back(Anim);
        //vectorに入る添え字番号を返す
        return static_cast<int> (AnimDatas.size() - 1);
    }

    /**
    * アニメーションの増分時刻を設定
    * @param[in] deltaTime 1フレームの増分時刻 秒単位
    * @detailes StartAnimationで設定されたアニメーションの再生を進める。
    * 毎フレームAddAnimationTimeを呼び出す必要がある
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
    * アニメーションの再生を開始
    * @param[in] animID 
    * 
    * @detailes animIDで指定したアニメーションの再生を開始する
    * お同じアニメーションが指定された場合、始めから再生する
    */
    void AnimationController::StartAnimaiton(int animID)
    {
        //以前のアニメーションと違うアニメーションが来たら一度デタッチ
        if (animID != NowAnimTypeNum)
        {
            if (NowAnimTypeNum != -1)
            {
                MV1DetachAnim(ModelHandle, AttachedIndex);
            }
            //新規アニメーションをセット
            NowAnimTypeNum = animID;
            AttachedIndex = MV1AttachAnim(ModelHandle, AnimDatas[animID].AnimationIndex, AnimDatas[NowAnimTypeNum].AnimationHandle, TRUE);
        }
        NowAnimTime = 0.0f;
        MV1SetAttachAnimTime(ModelHandle, AttachedIndex, NowAnimTime);
    }

    /**
    * 現在指定されているアニメーションの再生を終了
    * @detailes 現在指定されているアニメーションが終了時刻でストップする
    * 再生途中のポーズで止まらないことに注意。ループ再生指定のアニメーションは無視される
    */
    void AnimationController::StopAnimation()
    {
        NowAnimTime = AnimDatas[NowAnimTypeNum].AnimationTotalTime;
    }

    /**
    * 現在指定されているアニメーションは再生中か？
    * @return true:再生中 false:再生終了
    * @detailes 現在指定されているアニメーションが再生中かを返す
    * ループ指定されたものは常にtrueを返す
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

    /**アニメーションデータ構造体 コンストラクタ*/
    AnimationController::AnimData::AnimData() :
        AnimationHandle(-1),
        AnimationIndex(-1),
        AnimationTotalTime(-1),
        AnimationPlayFps(0),
        LoopAnimation(false)
    {
    }
}