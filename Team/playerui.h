//*****************************************************************************
// プレイヤーUI処理(playerUI.h)
// Author : 三上航世
//*****************************************************************************

#ifndef _PLAYERUI_H_
#define _PLAYERUI_H_

#include "ui.h"

class CPlayerUI :public CUI
{
public:

	CPlayerUI(PRIORITY Priority);
	~CPlayerUI();

	HRESULT Init(int nTex);
	void Uninit();
	void Update();
	void Draw();
	void ZTexDraw() { ; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }

	void SetPos(D3DXVECTOR3 pos);

	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }

	static CPlayerUI *Create(int nTex);
private:
	float m_fHeight;
	CUI *m_pUI;
};
#endif