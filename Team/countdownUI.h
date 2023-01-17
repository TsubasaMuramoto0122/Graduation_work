//*****************************************************************************
// カウントダウンUI処理(countdownUI.h)
// Author : 三上航世
//*****************************************************************************

#ifndef _COUNTDOWNUI_H_
#define _COUNTDOWNUI_H_

#include "ui.h"

class CCountdownUI :public CScene
{
public:

	CCountdownUI(PRIORITY Priority);
	~CCountdownUI();

	HRESULT Init(D3DXVECTOR3);
	void Uninit();
	void Update();
	void Draw();
	void ZTexDraw() { ; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	void SetPos(D3DXVECTOR3) { ; }

	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }

	static CCountdownUI *Create();
private:
	int m_nTime;
	int m_nPattern;
	CUI *m_pUI;
};
#endif