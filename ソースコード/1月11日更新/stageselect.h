//=============================================================================
// �X�e�[�W�Z���N�g�Ǘ� [stageselect.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _STAGE_SELECT_H_
#define _STAGE_SELECT_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"
#include "scene.h"

//*****************************************************************************
//�}�N��
//*****************************************************************************
#define MAX_STAGESELECT_UI (4)	// �I������UI�̐�

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CKeyboard;
class CGamePad;
class CUI;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CStageSelect : public CScene
{
public:
	CStageSelect(PRIORITY Priority);	// �R���X�g���N�^
	~CStageSelect();					// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);		// ����������
	void Uninit();						// �I������
	void Update();						// �X�V����
	void Draw();						// �`�揈��
	static CStageSelect *Create();		// �쐬����
	void ZTexDraw() { ; }

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	void SetPos(D3DXVECTOR3) { ; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }

	static int GetStageNum(void) { return m_nSelect; }	// �X�e�[�W�ԍ��擾����

private:
	void SelectChange(int nLine, int nRow);		// �I�����̕ύX����

	CKeyboard *m_pKeyboard;						// �L�[�{�[�h�̃|�C���^
	CGamePad *m_pGamePad;						// �Q�[���p�b�h�̃|�C���^
	CUI *m_pUI[MAX_STAGESELECT_UI];				// UI�̃|�C���^
	static int m_nSelect;						// �I����
	static int m_nLine;							// �s
	static int m_nRow;							// ��
};

#endif // _STAGE_SELECT_H_