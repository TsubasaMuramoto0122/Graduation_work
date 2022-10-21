//=============================================================================
// エントリーOK処理(okUI.h)
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _OKUI_H_
#define _OKUI_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "ui.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class COkUI :public CUI
{
public:
	COkUI(PRIORITY Priority);									// コンストラクタ
	~COkUI();													// デストラクタ
	HRESULT Init(D3DXVECTOR2 pos, D3DXVECTOR2 size);			// 初期化処理
	void Uninit();												// 終了処理
	void Update();												// 更新処理
	void Draw();												// 描画処理
	static COkUI *Create(D3DXVECTOR2 pos, D3DXVECTOR2 size);	// 生成処理
	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }

private:
	D3DXVECTOR2 m_size;		// UIのサイズ
	int m_nTime;			// カウント
	bool m_bShrink;			// 縮小するかどうか
	CUI *m_pUI;				// UIのポインタ
};
#endif //_OKUI_H_