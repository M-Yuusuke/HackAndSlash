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
        //アニメーションの追加
        int AddAnimation(std::string animFileName, float animFps = 30.0f, bool isLoop = true);

        //アニメーションの時間のセット
        void AddAnimaitonTime(float deltaTime);
        //アニメーションの再生開始
        void StartAnimaiton(int animID);
        //アニメーションの再生をストップ
        void StopAnimation();
        //現在再生中か
        bool IsPlaying();

    private:
        struct AnimData
        {
        public:
            AnimData();
            int AnimationHandle;
            //アタッチするアニメーション番号
            int AnimationIndex;
            //アニメーションの総再生時間
            float AnimationTotalTime;
            //アニメーションの再生速度
            float AnimationPlayFps;
            //ループ再生を許可するか
            bool LoopAnimation;
        };

        int ModelHandle;
        //アニメーション複数登録用
        std::vector<AnimData> AnimDatas;
        //現在再生中のアニメーションID
        int NowAnimTypeNum;
        //取り付け後のインデックス
        int AttachedIndex;
        //現在再生中のアニメーション時刻
        float NowAnimTime;
    };
}

