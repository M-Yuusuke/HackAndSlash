#include "DxLib.h"
#include "SceneBase.h"
#include "SceneManager.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		// �G���[���N�����璼���ɏI��
		return -1;
	}
	//�t���X�N���[�����[�h
	ChangeWindowMode(FALSE);
	//�𑜓x�E�J���[�r�b�g���̎w��
	SetGraphMode(1920, 1080, 32);

	SceneManager* sceneManager = SceneManager::Create();
	SceneBase* scene = nullptr;
	scene = sceneManager->NextScene(scene);

	//�Q�[�����[�v
	while (!ProcessMessage())
	{
		scene = scene->Update(sceneManager);
		scene->Draw();
	}

	SceneManager::Destroy();
	sceneManager = nullptr;
	scene = nullptr;
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}