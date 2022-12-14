//*****************************************************************************
// UI関連処理(UI.h)
// Author : 三上航世
//*****************************************************************************

#ifndef _UI_H_
#define _UI_H_

#include "Scene2d.h"

class CUI :public CScene2D
{
public:

	CUI(PRIORITY Priority);
	~CUI();

	HRESULT Init(D3DXVECTOR2 pos, D3DXVECTOR2 size, int nType, D3DXCOLOR col);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }

	static CUI *Create(D3DXVECTOR2 pos, D3DXVECTOR2 size, int nType, D3DXCOLOR col);
private:
	D3DXVECTOR2 m_pos;			//現在位置

	D3DCOLORVALUE m_Color;		//カラー
	bool m_bUninit;				//消すか
};
#endif