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

