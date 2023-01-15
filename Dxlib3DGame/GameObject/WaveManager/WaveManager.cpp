#pragma warning(disable:4244)   //int→float変換のワーニング抑制
#include "WaveManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Objects/Enemy/Mutant/Mutant.h"
#include "../ObjectTag.h"

/// <summary>
/// コンストラクタ
/// </summary>
WaveManager::WaveManager():
    WaveState(0)
{
    for (int i = 0; i < 3; i++)
    {
        wave[i].totalEnemyNum = 10 * (i + 1);
    }
}

/// <summary>
/// デストラクタ
/// </summary>
WaveManager::~WaveManager()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void WaveManager::Initialize()
{
    //エネミーを三体生成
    EntryEnemy(3);
    WaveState = 0;
    
}

/// <summary>
/// 更新処理
/// </summary>
void WaveManager::Update()
{
    //現在生きているエネミーの数を取得
    wave[WaveState].aliveEnemyNum = Calculation::GameObjectManager::GetObjectSize(Calculation::ObjectTag::Enemy);
    //現在のウェーブで出現させるエネミーの総数が規定数まで来たら次のウェーブに切り替える
    if (wave[WaveState].totalEnemyNum == 0)
    {
        WaveState++;
    }
    int Sub;
    switch (WaveState)
    {
    case 0:
        //常時3体出現させる
        if (wave[WaveState].totalEnemyNum > 0 && wave[WaveState].aliveEnemyNum <= 3)
        {
            Sub = 3 - wave[WaveState].aliveEnemyNum;
            EntryEnemy(Sub);
            wave[WaveState].totalEnemyNum -= Sub;
        }
        break;
    case 1:

        break;
    case 2:

        break;
    default:
        break;
    }
}

/// <summary>
/// 必要数のエネミーを生成
/// </summary>
/// <param name="entryNum">必要数(デフォルトで1)</param>
void WaveManager::EntryEnemy(int entryNum)
{
    for (int i = 0; i < entryNum; i++)
    {
        //現在出現しているエネミーが出現上限よりも少なかった場合のみ生成
        if (wave[WaveState].aliveEnemyNum <= aliveEnemyLimit)
        {
            Calculation::GameObjectManager::Entry(new Calculation::Mutant(VGet((-GetRand(1000) + GetRand(1000)), 0, (-GetRand(1000) + GetRand(1000)))));
        }
    }
}
