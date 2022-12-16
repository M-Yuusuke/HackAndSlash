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
        /// アニメーションの追加
        /// </summary>
        /// <param name="animFileName">アニメーションのファイルパス</param>
        /// <param name="animFps">アニメーション再生のフレームレート（デフォルトで30FPS）</param>
        /// <param name="isLoop">アニメーションのループ再生</param>
        /// <returns>アニメーション再生に必要なID</returns>
        int AddAnimation(std::string animFileName, float animFps = 30.0f, bool isLoop = true);

        /// <summary>
        /// アニメーションの時間のセット
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void AddAnimaitonTime(float deltaTime);
        
        /// <summary>
        /// アニメーションの再生開始
        /// </summary>
        /// <param name="animID">アニメーションID</param>
        void StartAnimaiton(int animID);

        /// <summary>
        /// アニメーションの再生をストップ
        /// </summary>
        void StopAnimation();

        /// <summary>
        /// 現在再生中か
        /// </summary>
        /// <returns>再生中ならtrue、停止していればfalse</returns>
        bool IsPlaying();

    private:
        struct AnimData
        {
        public:
            AnimData();
            int animationHandle;
            //アタッチするアニメーション番号
            int animationIndex;
            //アニメーションの総再生時間
            float animationTotalTime;
            //アニメーションの再生速度
            float animationPlayFps;
            //ループ再生を許可するか
            bool loopAnimation;
        };

        int modelHandle;
        //アニメーション複数登録用
        std::vector<AnimData> animDatas;
        //現在再生中のアニメーションID
        int nowAnimTypeNum;
        //取り付け後のインデックス
        int attachedIndex;
        //現在再生中のアニメーション時刻
        float nowAnimTime;
    };
}

