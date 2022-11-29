//=============================================================================
// �v���C���[�G���g���[�Ǘ� [entry.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _ENTRY_H_
#define _ENTRY_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"
#include "scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CKeyboard;
class CGamePad;
class CUI;
class CStandbyUI;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEntry : public CScene
{
public:
	CEntry(PRIORITY Priority);			// �R���X�g���N�^
	~CEntry();							// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);		// ����������
	void Uninit();						// �I������
	void Update();						// �X�V����
	void Draw();						// �`�揈��
	void ZTexDraw();

	static CEntry *Create();			// �쐬����
	static bool GetStandby(int nNum);	// �ҋ@�擾����

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	void SetPos(D3DXVECTOR3) { ; }

private:
	void DisplayOkUI(int nNum, bool bEntry);	// UI�\������
	CKeyboard *m_pKeyboard;						// �L�[�{�[�h�̃|�C���^
	CGamePad *m_pGamePad;						// �Q�[���p�b�h�̃|�C���^
	CStandbyUI *m_pStandbyUI[4];				// �X�^���o�C��UI�̃|�C���^
	bool m_bCanStart;							// �X�^�[�g�ł��邩�ǂ���
	static bool m_bStandby[4];					// �ҋ@���Ă邩�ǂ���
};

#endif // _ENTRY_H_