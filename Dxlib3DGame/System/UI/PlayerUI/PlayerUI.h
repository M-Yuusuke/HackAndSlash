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
    /// �X�V����
    /// </summary>
    void Update();

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw();

private:
    //PlayerUI�̃t�H���g�T�C�Y
    const int FontSize = 48;

    //HP�Q�[�W�̐F
    const VECTOR HpColor = { 0,255,0 };
    //Exp�Q�[�W�̐F
    const VECTOR ExpColor = { 0,0,255 };

    //�Q�[�W�̊g�嗦
    const int Magnifincation = 10;
    //�Q�[�W�̍��[�̈ʒu
    const int MeterPosX = 475;
    //�Q�[�W�̏c��
    const int MeterHeight = 50;
    //�Q�[�W�̕��̍ő�l
    const int MeterWidth = 1000;
    //HP�Q�[�W��Y���W
    const int HpMeterPosY = 900;
    //Exp�Q�[�W��Y���W
    const int ExpMeterPosY = HpMeterPosY + MeterHeight + 50;
    //�Q�[�W�ƃt���[���̍�
    const int FrameSub = 5;
    //HP�̕�����x���W
    const int HpStringPosX = MeterPosX - 80;
    //Exp�̕�����x���W
    const int ExpStringPosX = MeterPosX - 90;
    //���F
    const INT4 White = { 255,255,255,0 };

    int hp;
    int exp;
};

