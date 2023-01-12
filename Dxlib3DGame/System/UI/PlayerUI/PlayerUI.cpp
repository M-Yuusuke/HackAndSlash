#include "PlayerUI.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerUI::PlayerUI()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerUI::~PlayerUI()
{
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayerUI::Draw(int hp, int exp)
{
    SetFontSize(FontSize);
    //HP�Q�[�W
    DrawString(MeterPosX - 80, HpMeterPosY, "HP", GetColor(255, 255, 255));
    DrawBox(MeterPosX, HpMeterPosY, MeterPosX + (hp * 10), HpMeterPosY + MeterHeight, GetColor(HpColor.x, HpColor.y, HpColor.z), TRUE);
    //Exp�Q�[�W
    DrawString(MeterPosX - 90, ExpMeterPosY, "EXP", GetColor(255, 255, 255));
    DrawBox(MeterPosX, ExpMeterPosY, MeterPosX + (exp * 10), ExpMeterPosY + MeterHeight, GetColor(ExpColor.x, ExpColor.y, ExpColor.z), TRUE);
}
