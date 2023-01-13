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
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw();

private:
    //PlayerUIのフォントサイズ
    const int FontSize = 48;

    //HPゲージの色
    const VECTOR HpColor = { 0,255,0 };
    //Expゲージの色
    const VECTOR ExpColor = { 0,0,255 };

    //ゲージの拡大率
    const int Magnifincation = 10;
    //ゲージの左端の位置
    const int MeterPosX = 475;
    //ゲージの縦幅
    const int MeterHeight = 50;
    //ゲージの幅の最大値
    const int MeterWidth = 1000;
    //HPゲージのY座標
    const int HpMeterPosY = 900;
    //ExpゲージのY座標
    const int ExpMeterPosY = HpMeterPosY + MeterHeight + 50;
    //ゲージとフレームの差
    const int FrameSub = 5;
    //HPの文字のx座標
    const int HpStringPosX = MeterPosX - 80;
    //Expの文字のx座標
    const int ExpStringPosX = MeterPosX - 90;
    //白色
    const INT4 White = { 255,255,255,0 };

    int hp;
    int exp;
};

