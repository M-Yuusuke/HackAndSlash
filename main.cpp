#include "DxLib.h"
#include "Scene/SceneBase/SceneBase.h"
#include "Scene/SceneManager/SceneManager.h"
#include "GameObject/GameObjectBase/GameObjectBase.h"
#include "GameObject/GameObjectManager/GameObjectManager.h"
#include "GameObject/AssetManager/AssetManager.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ＤＸライブラリ初期化処理
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	if (DxLib_Init() == -1)
	{
		// エラーが起きたら直ちに終了
		return -1;
	}
	//フルスクリーンモード
	ChangeWindowMode(FALSE);
	//解像度・カラービット数の指定
	SetGraphMode(1920, 1080, 32);

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	SceneManager* sceneManager = SceneManager::Create();
	SceneBase* scene = nullptr;
	scene = sceneManager->NextScene(scene);

	//ゲームループ
	while (!ProcessMessage())
	{
		scene = scene->Update();
		scene->Draw();
	}

	SceneManager::Destroy();
	sceneManager = nullptr;
	scene = nullptr;
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}