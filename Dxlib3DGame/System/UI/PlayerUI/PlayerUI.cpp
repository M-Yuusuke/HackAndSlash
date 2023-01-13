#include "PlayerUI.h"
#include "../GameObject/Objects/Camera/Camera.h"
#include "../GameObject/GameObjectManager/GameObjectManager.h"
#include "../GameObject/ObjectTag.h"
#include "../GameObject/Objects/Player/Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerUI::PlayerUI():
    hp(0),
    exp(0)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerUI::~PlayerUI()
{
}

/// <summary>
/// �X�V����
/// </summary>
void PlayerUI::Update()
{
    Calculation::GameObjectBase* player = Calculation::GameObjectManager::GetFirstGameObject(Calculation::ObjectTag::Player);
    hp = static_cast<Calculation::Player*>(player)->GetHP();
    exp = static_cast<Calculation::Player*>(player)->GetEXP();
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayerUI::Draw()
{

    SetFontSize(FontSize);
    //HP�Q�[�W
    DrawString(MeterPosX - 80, HpMeterPosY, "HP", GetColor(255, 255, 255));
    DrawBox(MeterPosX, HpMeterPosY, MeterPosX + (hp * 10), HpMeterPosY + MeterHeight, GetColor((int)HpColor.x, (int)HpColor.y, (int)HpColor.z), TRUE);

    //Exp�Q�[�W
    DrawString(MeterPosX - 90, ExpMeterPosY, "EXP", GetColor(255, 255, 255));
    DrawBox(MeterPosX, ExpMeterPosY, MeterPosX + (exp * 10), ExpMeterPosY + MeterHeight, GetColor((int)ExpColor.x, (int)ExpColor.y, (int)ExpColor.z), TRUE);
}