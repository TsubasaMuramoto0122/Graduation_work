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
class CPauseUI;

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
	static bool GetStandby(int nNum) { return m_bStandby[nNum]; }	// �ҋ@�擾����
	static int SelectStage() { return m_nStage; }

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	void SetPos(D3DXVECTOR3) { ; }

private:
	void DisplayOkUI(int nNum, bool bEntry);	// UI�\������
	bool ReadyGo();								// �N��GO�T�C���o���Ă邩
	void Stage();
	void StageUIMove();
	void StageChange(int nLine, int nAdd);
	void GameStart();

	CKeyboard *m_pKeyboard;			// �L�[�{�[�h�̃|�C���^
	CGamePad *m_pGamePad;			// �Q�[���p�b�h�̃|�C���^
	CStandbyUI *m_pStandbyUI[4];	// �X�^���o�C��UI�̃|�C���^
	CUI *m_pBg;						// �w�i
	CUI *m_pStage[18];				// �X�e�[�W
	int m_nTime;
	bool m_bStageSelect;
	int m_nLine[2];

	static bool m_bStandby[4];					// �ҋ@���Ă邩�ǂ���
	static int m_nStage;
};
#endif // _ENTRY_H_