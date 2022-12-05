#pragma once
class SceneBase;
class Initialize;
class Title;
class Play;
class Result;
class SceneManager
{
public:
    //シングルトンの生成
    static SceneManager* Create();
    //シングルトンの破棄
    static void Destroy();

    SceneBase* NextScene(SceneBase* NowScene)const;

private:
    SceneManager();
    ~SceneManager();
    static SceneManager* Instance;

    Initialize* initialize;
    Title* title;
    Play* play;
    Result* result;
};

