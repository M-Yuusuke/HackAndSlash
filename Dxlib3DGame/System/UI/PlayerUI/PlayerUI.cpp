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
    //HPゲージ
    DrawString(MeterPosX - 80, HpMeterPosY, "HP", GetColor(255, 255, 255));
    DrawBox(MeterPosX, HpMeterPosY, MeterPosX + (hp * 10), HpMeterPosY + MeterHeight, GetColor((int)HpColor.x, (int)HpColor.y, (int)HpColor.z), TRUE);

    //Expゲージ
    DrawString(MeterPosX - 90, ExpMeterPosY, "EXP", GetColor(255, 255, 255));
    DrawBox(MeterPosX, ExpMeterPosY, MeterPosX + (exp * 10), ExpMeterPosY + MeterHeight, GetColor((int)ExpColor.x, (int)ExpColor.y, (int)ExpColor.z), TRUE);
}