#include "DxLib.h"
#include "SceneBase.h"
#include "SceneManager.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		// エラーが起きたら直ちに終了
		return -1;
	}
	//フルスクリーンモード
	ChangeWindowMode(FALSE);
	//解像度・カラービット数の指定
	SetGraphMode(1920, 1080, 32);

	SceneManager* sceneManager = SceneManager::Create();
	SceneBase* scene = nullptr;
	scene = sceneManager->NextScene(scene);

	//ゲームループ
	while (!ProcessMessage())
	{
		scene = scene->Update(sceneManager);
		scene->Draw();
	}

	SceneManager::Destroy();
	sceneManager = nullptr;
	scene = nullptr;
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}