#pragma once
class WaveManager
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    WaveManager();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~WaveManager();

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// ウェーブの状態を渡す
    /// </summary>
    /// <returns>ウェーブナンバー</returns>
    int GetWaveNum() { return WaveState; }

private:
    /// <summary>
    /// 必要数のエネミーを生成
    /// </summary>
    /// <param name="entryNum">必要数(デフォルトで1)</param>
    void EntryEnemy(int entryNum = 1);

    //出現可能上限
    const int aliveEnemyLimit = 15;
    //ウェーブの状態変数(Wave構造体の添字としても使用)
    int WaveState;
    struct Wave
    {
        //そのウェーブのエネミーの総数
        int totalEnemyNum;
        //現在生きているエネミーの数
        int aliveEnemyNum;
    };
    Wave wave[3];

};

