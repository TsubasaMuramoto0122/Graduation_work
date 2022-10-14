//=============================================================================
//�|�[�Y�Ǘ�[pauseui.h]
// Author : �O��@�q��
//=============================================================================
#ifndef _PAUSEUI_H_
#define _PAUSEUI_H_

#include "ui.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CPauseUI : public CUI
{
public:
	CPauseUI(PRIORITY Priority);
	~CPauseUI();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nType, D3DXCOLOR col);
	void Uninit();
	void Update();
	void Draw();

	static CPauseUI *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nType, D3DXCOLOR col);

private:

};

#endif