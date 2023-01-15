#pragma warning(disable:4244)   //int��float�ϊ��̃��[�j���O�}��
#include "WaveManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Objects/Enemy/Mutant/Mutant.h"
#include "../ObjectTag.h"

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
WaveManager::~WaveManager()
{
}

/// <summary>
/// ����������
/// </summary>
void WaveManager::Initialize()
{
    //�G�l�~�[���O�̐���
    EntryEnemy(3);
    WaveState = 0;
    
}

/// <summary>
/// �X�V����
/// </summary>
void WaveManager::Update()
{
    //���ݐ����Ă���G�l�~�[�̐����擾
    wave[WaveState].aliveEnemyNum = Calculation::GameObjectManager::GetObjectSize(Calculation::ObjectTag::Enemy);
    //���݂̃E�F�[�u�ŏo��������G�l�~�[�̑������K�萔�܂ŗ����玟�̃E�F�[�u�ɐ؂�ւ���
    if (wave[WaveState].totalEnemyNum == 0)
    {
        WaveState++;
    }
    int Sub;
    switch (WaveState)
    {
    case 0:
        //�펞3�̏o��������
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
/// �K�v���̃G�l�~�[�𐶐�
/// </summary>
/// <param name="entryNum">�K�v��(�f�t�H���g��1)</param>
void WaveManager::EntryEnemy(int entryNum)
{
    for (int i = 0; i < entryNum; i++)
    {
        //���ݏo�����Ă���G�l�~�[���o������������Ȃ������ꍇ�̂ݐ���
        if (wave[WaveState].aliveEnemyNum <= aliveEnemyLimit)
        {
            Calculation::GameObjectManager::Entry(new Calculation::Mutant(VGet((-GetRand(1000) + GetRand(1000)), 0, (-GetRand(1000) + GetRand(1000)))));
        }
    }
}
