//=============================================================================
//�Q�[���Ǘ�[Game.h]
// Author : �O��q��
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "manager.h"
#include "scene.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CGamePad;
//*****************�������X�V����������*****************//
class CPlayer;
//*****************�������X�V����������*****************//
class CUI;
class CMeshWall;
class CMeshField;

class CGame : public CScene
{
public:
	CGame(PRIORITY Priority);
	~CGame();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	void SetPos(D3DXVECTOR3 pos) { pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetMove() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	float GetHeight() { return 0.0f; }
	COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	bool GetRotX() { return false; }
	D3DXMATRIX GetMatrix(int) { return D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f); }
	D3DXMATRIX GetMatrix() { return D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f); }

	static CGame *Create();

	//�I��ԍ������Ƃ��ł�����
	static int GetSelectNum() { return m_SelectNum; };

private:
	void TimerUI();
	//*****************�������X�V����������*****************//
	void Annihilation();
	//*****************�������X�V����������*****************//

	static bool m_bCountFlag;		//�J�E���g�_�E�������ǂ���
	static int m_SelectNum;			//�I��ԍ�

	int m_nTime;
	//*****************�������X�V����������*****************//
	int m_nDefeatNum;				// ���ꂽ�v���C���[�̐l��
	bool m_bAnnihilation;			// �S�ł������ǂ���
	CPlayer *m_pPlayer[4];			// �v���C���[�̃|�C���^
	//*****************�������X�V����������*****************//
	CUI *m_pTimeUI[3];
	CUI *m_pCountDown[4];
	CMeshField *m_pMeshField[2];	// ���b�V���t�B�[���h�̃|�C���^
	CMeshWall *m_pMeshWall[4];		// ���b�V���E�H�[���̃|�C���^
};

#endif // _GAME_H_
