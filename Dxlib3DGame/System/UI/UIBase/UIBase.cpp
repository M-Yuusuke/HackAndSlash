#include "UIBase.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ(フォントデータの読み込み)
/// </summary>
UIBase::UIBase()
{
    //if (AddFontResourceEx("フォントのパス", FR_PRIVATE, NULL) > 0)
    //{
    //    ;
    //}
    //else
    //{
    //    //フォント読み込みエラー処理
    //    MessageBox(NULL, "フォント読込失敗", "", MB_OK);
    //}
    //SetFontSize(FontSize);
    //ChangeFont("美咲ゴシック第2", DX_CHARSET_DEFAULT);
}

/// <summary>
/// デストラクタ(フォントデータの破棄)
/// </summary>
UIBase::~UIBase()
{
    //if (RemoveFontResourceEx("フォントのパス", FR_PRIVATE, NULL))
    //{
    //    ;
    //}
    //else
    //{
    //    MessageBox(NULL, "remove failure", "", MB_OK);
    //}
}
