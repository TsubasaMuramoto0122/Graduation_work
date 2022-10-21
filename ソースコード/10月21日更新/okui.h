//=============================================================================
// �G���g���[OK����(okUI.h)
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _OKUI_H_
#define _OKUI_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "ui.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class COkUI :public CUI
{
public:
	COkUI(PRIORITY Priority);									// �R���X�g���N�^
	~COkUI();													// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR2 pos, D3DXVECTOR2 size);			// ����������
	void Uninit();												// �I������
	void Update();												// �X�V����
	void Draw();												// �`�揈��
	static COkUI *Create(D3DXVECTOR2 pos, D3DXVECTOR2 size);	// ��������
	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }

private:
	D3DXVECTOR2 m_size;		// UI�̃T�C�Y
	int m_nTime;			// �J�E���g
	bool m_bShrink;			// �k�����邩�ǂ���
	CUI *m_pUI;				// UI�̃|�C���^
};
#endif //_OKUI_H_