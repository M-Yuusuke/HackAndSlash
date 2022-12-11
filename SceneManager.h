#pragma once
class SceneBase;
class Initialize;
class Title;
class Play;
class Result;
class SceneManager
{
public:
    //�V���O���g���̐���
    static SceneManager* Create();
    //�V���O���g���̔j��
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

