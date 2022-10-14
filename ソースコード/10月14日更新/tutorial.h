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
	static CTutorial *Create();		// �쐬����

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetMove() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	void SetPos(D3DXVECTOR3) { ; }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	float GetHeight() { return 0.0f; }
	COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	bool GetRotX() { return false; }
	D3DXMATRIX GetMatrix(int) { return D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f); }
	D3DXMATRIX GetMatrix() { return D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f); }

private:
	CKeyboard *m_pKeyboard;			// �L�[�{�[�h�̃|�C���^
	//CGamePad *m_pGamePad;			// �Q�[���p�b�h�̃|�C���^
};

#endif // _TUTORIAL_H_