#include "DxLib.h"
#include "WaveUI.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
WaveUI::WaveUI()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WaveUI::~WaveUI()
{
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="waveState">���݂̃E�F�[�u��</param>
void WaveUI::Draw(const int waveState)
{
    DrawFormatString(800, 20, GetColor(255, 255, 255), "Wave %d / 3", waveState + 1);
}
