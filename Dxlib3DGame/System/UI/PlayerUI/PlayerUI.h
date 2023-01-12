#pragma once
#include "DxLib.h"
#include "../UIBase/UIBase.h"
class PlayerUI : public UIBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerUI();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PlayerUI();

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw(int hp, int exp);

private:
    //PlayerUIのフォントサイズ
    const int FontSize = 48;

    //HPゲージの色
    const VECTOR HpColor = { 0,255,0 };
    //Expゲージの色
    const VECTOR ExpColor = { 0,0,255 };

    //ゲージの左端の位置
    const int MeterPosX = 600;
    //ゲージの縦幅
    const int MeterHeight = 50;
    //HPゲージのY座標
    const int HpMeterPosY = 900;
    //ExpゲージのY座標
    const int ExpMeterPosY = HpMeterPosY + MeterHeight + 50;
};

