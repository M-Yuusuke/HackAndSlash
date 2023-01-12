#include "PlayerUI.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerUI::PlayerUI()
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerUI::~PlayerUI()
{
}

/// <summary>
/// 描画処理
/// </summary>
void PlayerUI::Draw(int hp, int exp)
{
    SetFontSize(FontSize);
    //HPゲージ
    DrawString(MeterPosX - 80, HpMeterPosY, "HP", GetColor(255, 255, 255));
    DrawBox(MeterPosX, HpMeterPosY, MeterPosX + (hp * 10), HpMeterPosY + MeterHeight, GetColor(HpColor.x, HpColor.y, HpColor.z), TRUE);
    //Expゲージ
    DrawString(MeterPosX - 90, ExpMeterPosY, "EXP", GetColor(255, 255, 255));
    DrawBox(MeterPosX, ExpMeterPosY, MeterPosX + (exp * 10), ExpMeterPosY + MeterHeight, GetColor(ExpColor.x, ExpColor.y, ExpColor.z), TRUE);
}
