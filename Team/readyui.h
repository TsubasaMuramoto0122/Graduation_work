//*****************************************************************************
// �Q�[���X�^�[�gUI����(readyUI.h)
// Author : �O��q��
//*****************************************************************************

#ifndef _READYUI_H_
#define _READYUI_H_

#include "ui.h"

class CReadyUI :public CScene
{
public:

	CReadyUI(PRIORITY Priority);
	~CReadyUI();

	HRESULT Init(D3DXVECTOR3);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }
	void ZTexDraw() { ; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	void SetPos(D3DXVECTOR3) { ; }

	static CReadyUI *Create();
private:
	int m_nTime;			//UI�̕ς���Ă���̎���
	int m_nPattern;			//UI�̃p�^�[��
	D3DXVECTOR2 m_size;		//UI�̑傫��
	float m_fClear;			//�����x
	CUI *m_pUI;				//UI�̃|�C���^
};
#endif