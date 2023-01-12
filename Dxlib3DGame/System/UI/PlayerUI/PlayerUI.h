#pragma once
#include "DxLib.h"
#include "../UIBase/UIBase.h"
class PlayerUI : public UIBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerUI();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PlayerUI();

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw(int hp, int exp);

private:
    //PlayerUI�̃t�H���g�T�C�Y
    const int FontSize = 48;

    //HP�Q�[�W�̐F
    const VECTOR HpColor = { 0,255,0 };
    //Exp�Q�[�W�̐F
    const VECTOR ExpColor = { 0,0,255 };

    //�Q�[�W�̍��[�̈ʒu
    const int MeterPosX = 600;
    //�Q�[�W�̏c��
    const int MeterHeight = 50;
    //HP�Q�[�W��Y���W
    const int HpMeterPosY = 900;
    //Exp�Q�[�W��Y���W
    const int ExpMeterPosY = HpMeterPosY + MeterHeight + 50;
};

