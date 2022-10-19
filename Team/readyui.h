//*****************************************************************************
// �Q�[���X�^�[�gUI����(readyUI.h)
// Author : �O��q��
//*****************************************************************************

#ifndef _READYUI_H_
#define _READYUI_H_

#include "ui.h"

class CReadyUI :public CUI
{
public:

	CReadyUI(PRIORITY Priority);
	~CReadyUI();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }

	static CReadyUI *Create();
private:
	int m_nTime;			//UI�̕ς���Ă���̎���
	int m_nPattern;			//UI�̃p�^�[��
	D3DXVECTOR2 m_size;		//UI�̑傫��
	float m_fClear;			//�����x
	CUI *m_pUI;				//UI�̃|�C���^
};
#endif