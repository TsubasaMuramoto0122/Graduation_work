//=============================================================================
//リザルトランキング管理[resultrank.h]
// Author : 三上航世
//=============================================================================
#ifndef _RESULTRANK_H_
#define _RESULTRANK_H_

#include "manager.h"
#include "scene.h"
//*****************************************************************************
//前方宣言
//*****************************************************************************
class CGamePad;
class CKeyboard;
class CUI;

class CResultRank : public CScene
{
public:
	CResultRank(PRIORITY Priority);
	~CResultRank();

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

	static CResultRank *Create();

private:
	void SelectFade();
	void Select();
	void SelectChange(int nAdd);
	void ChooseFade();

	CKeyboard *m_pKeyboard;
	CGamePad *m_pGamePad;

	bool m_bSelect;
	int m_nSelect;
	int m_nFadeTime;
	float m_fClear;
	int m_nTime;
	CUI *m_pUI[12];
	CUI *m_pSelectUI[20];
	float m_fFade[7];
};

#endif // _RESULT_H_
