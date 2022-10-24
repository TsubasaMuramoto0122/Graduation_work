//=============================================================================
// スタンバイUI処理 [standbyUI.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _STANDBYUI_H_
#define _STANDBYUI_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "ui.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************
class CStandbyUI :public CUI
{
public:
	CStandbyUI(PRIORITY Priority);									// コンストラクタ
	~CStandbyUI();													// デストラクタ
	HRESULT Init(D3DXVECTOR2 pos, D3DXVECTOR2 size);				// 初期化処理
	void Uninit();													// 終了処理
	void Update();													// 更新処理
	void Draw();													// 描画処理
	static CStandbyUI *Create(D3DXVECTOR2 pos, D3DXVECTOR2 size);	// 生成処理
	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }

private:
	D3DXVECTOR2 m_size;		// UIのサイズ
	int m_nTime;			// カウント
	bool m_bShrink;			// 縮小するかどうか
	CUI *m_pUI;				// UIのポインタ
};
#endif //_STANDBYUI_H_