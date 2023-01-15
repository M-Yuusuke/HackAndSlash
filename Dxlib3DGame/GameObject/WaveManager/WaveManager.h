#pragma once
class WaveManager
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    WaveManager();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~WaveManager();

    /// <summary>
    /// ����������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �X�V����
    /// </summary>
    void Update();

    /// <summary>
    /// �E�F�[�u�̏�Ԃ�n��
    /// </summary>
    /// <returns>�E�F�[�u�i���o�[</returns>
    int GetWaveNum() { return WaveState; }

private:
    /// <summary>
    /// �K�v���̃G�l�~�[�𐶐�
    /// </summary>
    /// <param name="entryNum">�K�v��(�f�t�H���g��1)</param>
    void EntryEnemy(int entryNum = 1);

    //�o���\���
    const int aliveEnemyLimit = 15;
    //�E�F�[�u�̏�ԕϐ�(Wave�\���̂̓Y���Ƃ��Ă��g�p)
    int WaveState;
    struct Wave
    {
        //���̃E�F�[�u�̃G�l�~�[�̑���
        int totalEnemyNum;
        //���ݐ����Ă���G�l�~�[�̐�
        int aliveEnemyNum;
    };
    Wave wave[3];

};

