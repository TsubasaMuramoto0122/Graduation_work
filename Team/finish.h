//*****************************************************************************
// フィニッシュUI処理(finish.h)
// Author : 三上航世
//*****************************************************************************

#ifndef _FINISH_H_
#define _FINISH_H_

#include "ui.h"

class CFinish :public CUI
{
public:

	CFinish(PRIORITY Priority);
	~CFinish();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }

	static CFinish *Create();
private:
	int m_nTime;
};
#endif