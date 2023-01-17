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
class CUI;
class CMeshWall;
class CPlayer;
class CMeshField;
class CPauseUI;

class CGame : public CScene
{
public:
	CGame(PRIORITY Priority);
	~CGame();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit();
	void Update();
	void Draw();
	void ZTexDraw();

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	void SetPos(D3DXVECTOR3 pos) { pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }

	static CGame *Create();

	//�I��ԍ������Ƃ��ł�����
	static int GetSelectNum() { return m_SelectNum; };

private:
	void TimerUI();
	void Annihilation();
	void SetPlayerSurviveTime();	// �v���C���[�̐������Ԃ̃Z�[�u
	void Pause();
	void PauseSelect();
	void PauseChange(int nAdd);
	void Snow();
	void StartSnow();

	int GetSurviveTime(void);

	static bool m_bCountFlag;		// �J�E���g�_�E�������ǂ���
	static int m_SelectNum;			// �I��ԍ�
	int m_nDefeatNum;				// ���ꂽ�v���C���[�̐l��
	bool m_bAnnihilation;			// �S�ł������ǂ���
	CPlayer *m_pPlayer[4];			// �v���C���[�̃|�C���^
	CGamePad *m_pGamePad;			// �Q�[���p�b�h�̃|�C���^

	int m_nSelect;					// �I��ł�|�[�Y�̑I����
	int m_nGamePad;					// ���̃Q�[���p�b�h���I�΂�Ă邩
	CPauseUI *m_pUI[3];				// �|�[�YUI

	int m_nTime;					// �c�莞��
	int m_nMaxTime;
	CUI *m_pTimeUI[3];				// �^�C�}�[UI
	bool m_bDeath[4];				// ���񂾂�
	int m_nSnowMaxTime;
	int m_nSnowTime;
};

#endif // _GAME_H_