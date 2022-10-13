//*****************************************************************************
// UI�֘A����(UI.h)
// Author : �O��q��
//*****************************************************************************

#ifndef _UI_H_
#define _UI_H_

#include "Scene2d.h"

class CUI :public CScene2D
{
public:

	CUI(PRIORITY Priority);
	~CUI();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nType, D3DXCOLOR col);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }

	static CUI *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nType, D3DXCOLOR col);
private:

	D3DXVECTOR3 m_pos;			//���݈ʒu

	D3DCOLORVALUE m_Color;		//�J���[
	bool m_bUninit;				//������

};
#endif