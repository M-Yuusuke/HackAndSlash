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

    static SceneBase* NextScene(SceneBase* NowScene);

private:
    SceneManager();
    ~SceneManager();
    static SceneManager* Instance;

    static Initialize* initialize;
    static Title* title;
    static Play* play;
    static Result* result;
};

