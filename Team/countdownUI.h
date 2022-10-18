//*****************************************************************************
// カウントダウンUI処理(countdownUI.h)
// Author : 三上航世
//*****************************************************************************

#ifndef _COUNTDOWNUI_H_
#define _COUNTDOWNUI_H_

#include "ui.h"

class CCountdownUI :public CUI
{
public:

	CCountdownUI(PRIORITY Priority);
	~CCountdownUI();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }

	static CCountdownUI *Create();
private:
	int m_nTime;
	int m_nPattern;
	CUI *m_pUI;
};
#endif