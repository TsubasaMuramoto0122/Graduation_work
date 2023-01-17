//*****************************************************************************
// フィニッシュUI処理(finish.h)
// Author : 三上航世
//*****************************************************************************

#ifndef _FINISH_H_
#define _FINISH_H_

#include "ui.h"

class CFinish :public CScene
{
public:

	CFinish(PRIORITY Priority);
	~CFinish();

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

	static CFinish *Create();
private:
	int m_nTime;
};
#endif