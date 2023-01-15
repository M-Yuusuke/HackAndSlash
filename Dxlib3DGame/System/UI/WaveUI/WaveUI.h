#pragma once
#include "../UIBase/UIBase.h"
class WaveUI :public UIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    WaveUI();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~WaveUI();

    /// <summary>
    /// 描画処理
    /// </summary>
    /// <param name="waveState">現在のウェーブ数</param>
    void Draw(const int waveState);
};