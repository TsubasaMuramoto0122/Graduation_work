//*****************************************************************************
// ゲームスタートUI処理(readyUI.h)
// Author : 三上航世
//*****************************************************************************

#ifndef _READYUI_H_
#define _READYUI_H_

#include "ui.h"

class CReadyUI :public CUI
{
public:

	CReadyUI(PRIORITY Priority);
	~CReadyUI();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }

	static CReadyUI *Create();
private:
	int m_nTime;			//UIの変わってからの時間
	int m_nPattern;			//UIのパターン
	D3DXVECTOR2 m_size;		//UIの大きさ
	float m_fClear;			//透明度
	CUI *m_pUI;				//UIのポインタ
};
#endif