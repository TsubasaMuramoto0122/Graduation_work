//=============================================================================
// �`���[�g���A���Ǘ� [tutorial.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"
#include "scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CUI;
class CKeyboard;
class CMeshWall;
class CMeshField;
//class CGamePad;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTutorial : public CScene
{
public:
	CTutorial(PRIORITY Priority);	// �R���X�g���N�^
	~CTutorial();					// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);	// ����������
	void Uninit();					// �I������
	void Update();					// �X�V����
	void Draw();					// �`�揈��
	void ZTexDraw();
	static CTutorial *Create();		// �쐬����

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	void SetPos(D3DXVECTOR3) { ; }

private:
	CKeyboard *m_pKeyboard;			// �L�[�{�[�h�̃|�C���^
	CMeshField *m_pMeshField[2];	// ���b�V���t�B�[���h�̃|�C���^
	CMeshWall *m_pMeshWall[4];		// ���b�V���E�H�[���̃|�C���^
};

#endif // _TUTORIAL_H_