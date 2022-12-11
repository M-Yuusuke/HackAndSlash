#include "DxLib.h"
#include "Scene/SceneBase/SceneBase.h"
#include "Scene/SceneManager/SceneManager.h"
#include "GameObject/GameObjectBase/GameObjectBase.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/AssetManager/AssetManager.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �c�w���C�u��������������
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	if (DxLib_Init() == -1)
	{
		// �G���[���N�����璼���ɏI��
		return -1;
	}
	//�t���X�N���[�����[�h
	ChangeWindowMode(FALSE);
	//�𑜓x�E�J���[�r�b�g���̎w��
	SetGraphMode(1920, 1080, 32);

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	SceneManager* sceneManager = SceneManager::Create();
	SceneBase* scene = nullptr;
	scene = sceneManager->NextScene(scene);

	//�Q�[�����[�v
	while (!ProcessMessage())
	{
		scene = scene->Update();
		scene->Draw();
	}

	SceneManager::Destroy();
	sceneManager = nullptr;
	scene = nullptr;
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}