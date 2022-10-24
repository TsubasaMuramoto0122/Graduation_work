//=============================================================================
// �X�^���o�CUI���� [standbyUI.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _STANDBYUI_H_
#define _STANDBYUI_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "ui.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class CStandbyUI :public CUI
{
public:
	CStandbyUI(PRIORITY Priority);									// �R���X�g���N�^
	~CStandbyUI();													// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR2 pos, D3DXVECTOR2 size);				// ����������
	void Uninit();													// �I������
	void Update();													// �X�V����
	void Draw();													// �`�揈��
	static CStandbyUI *Create(D3DXVECTOR2 pos, D3DXVECTOR2 size);	// ��������
	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }

private:
	D3DXVECTOR2 m_size;		// UI�̃T�C�Y
	int m_nTime;			// �J�E���g
	bool m_bShrink;			// �k�����邩�ǂ���
	CUI *m_pUI;				// UI�̃|�C���^
};
#endif //_STANDBYUI_H_