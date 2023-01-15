#include "DxLib.h"
#include "WaveUI.h"
/// <summary>
/// コンストラクタ
/// </summary>
WaveUI::WaveUI()
{
}

/// <summary>
/// デストラクタ
/// </summary>
WaveUI::~WaveUI()
{
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="waveState">現在のウェーブ数</param>
void WaveUI::Draw(const int waveState)
{
    DrawFormatString(800, 20, GetColor(255, 255, 255), "Wave %d / 3", waveState + 1);
}
