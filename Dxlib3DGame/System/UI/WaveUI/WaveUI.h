#pragma once
#include "../UIBase/UIBase.h"
class WaveUI :public UIBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    WaveUI();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~WaveUI();

    /// <summary>
    /// �`�揈��
    /// </summary>
    /// <param name="waveState">���݂̃E�F�[�u��</param>
    void Draw(const int waveState);
};