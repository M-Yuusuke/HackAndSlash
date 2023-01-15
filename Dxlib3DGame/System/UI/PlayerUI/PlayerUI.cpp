#include "PlayerUI.h"
#include "../GameObject/Objects/Camera/Camera.h"
#include "../GameObject/GameObjectManager/GameObjectManager.h"
#include "../GameObject/ObjectTag.h"
#include "../GameObject/Objects/Player/Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerUI::PlayerUI():
    hp(0),
    exp(0)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerUI::~PlayerUI()
{
}

/// <summary>
/// 更新処理
/// </summary>
void PlayerUI::Update()
{
    Calculation::GameObjectBase* player = Calculation::GameObjectManager::GetFirstGameObject(Calculation::ObjectTag::Player);
    hp = static_cast<Calculation::Player*>(player)->GetHP();
    exp = static_cast<Calculation::Player*>(player)->GetEXP();
}

/// <summary>
/// 描画処理
/// </summary>
void PlayerUI::Draw()
{ 
    SetFontSize(FontSize);
    DrawString(HpStringPosX, HpMeterPosY, "HP", GetColor(White.x, White.y, White.z));
    //HPゲージフレーム
    DrawBox(MeterPosX - FrameSub, HpMeterPosY - FrameSub, MeterPosX + MeterWidth + FrameSub, HpMeterPosY + MeterHeight + FrameSub, GetColor(0, 0, 0), TRUE);
    //HPゲージ
    DrawBox(MeterPosX, HpMeterPosY, MeterPosX + (hp * Magnifincation), HpMeterPosY + MeterHeight, GetColor((int)HpColor.x, (int)HpColor.y, (int)HpColor.z), TRUE);

    DrawString(ExpStringPosX, ExpMeterPosY, "EXP", GetColor(White.x, White.y, White.z));
    //Expフレーム
    DrawBox(MeterPosX - FrameSub, ExpMeterPosY - FrameSub, MeterPosX + MeterWidth + FrameSub, ExpMeterPosY + MeterHeight + FrameSub, GetColor(0, 0, 0), TRUE);
    //Expゲージ
    DrawBox(MeterPosX, ExpMeterPosY, MeterPosX + (exp * Magnifincation), ExpMeterPosY + MeterHeight, GetColor((int)ExpColor.x, (int)ExpColor.y, (int)ExpColor.z), TRUE);
}