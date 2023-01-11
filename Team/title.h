//=============================================================================
// タイトル管理[Title.h]
// Author : 三上航世
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "manager.h"
#include "scene.h"

//*****************************************************************************
//前方宣言
//*****************************************************************************
//class CGamePad;
class CKeyboard;
//class CMouse;
class CUI;

class CTitle : public CScene
{
public:
	CTitle(PRIORITY Priority);
	~CTitle();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	void ZTexDraw();

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	void SetPos(D3DXVECTOR3) { ; }

	static CTitle *Create();

private:
	void SelectChange(int nAdd);
	void Select();
	void SelectFade();

	CKeyboard *m_pKeyboard;
	CGamePad *m_pGamePad;
	CUI *m_pUI[4];
	float m_fClear;
	int m_nSelect;
	int m_nFadeTime;
};

#endif // _TITLE_H_
