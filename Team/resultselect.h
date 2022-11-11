//=============================================================================
//リザルト選択管理[resultselect.h]
// Author : 三上航世
//=============================================================================
#ifndef _RESULTSELECT_H_
#define _RESULTSELECT_H_

#include "manager.h"
#include "scene.h"
//*****************************************************************************
//前方宣言
//*****************************************************************************
class CGamePad;
class CKeyboard;
class CUI;

class CResultSelect : public CScene
{
public:
	CResultSelect(PRIORITY Priority);
	~CResultSelect();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	void SetPos(D3DXVECTOR3) { ; }

	static CResultSelect *Create();

private:
	void SelectChange(int nAdd);
	void Select();
	void SelectFade();

	CKeyboard *m_pKeyboard;
	//CGamePad *m_pGamePad;

	CUI *m_pUI[6];
	int m_nSelect;
	float m_fClear;
	int m_nFadeTime;
};

#endif // _RESULT_H_
