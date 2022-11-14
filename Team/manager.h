//=============================================================================
//
// �}�l�[�W�� [Manager.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
//=============================================================================
//�}�N��
//=============================================================================

//�O���錾
class CRenderer;
class CKeyboard;
class CMouse;
class CGamePad;

class CTitle;
class CGame;
class CResultRank;
class CResultSelect;
class CTutorial;
class CEntry;
//class CGameOver;

class CManager
{
public:

	typedef enum
	{
		MODE_TITLE,			// �^�C�g��
		MODE_TUTORIAL,		// �`���[�g���A��
		MODE_ENTRY,			// �v���C���[�G���g���[
		MODE_GAME,			// �Q�[��
		MODE_RESULTRANK,	// ���U���g�����L���O
		MODE_RESULTSELECT,	// ���U���g��I��
		MODE_MAX,
	}MODE;

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();
	static CRenderer *GetRenderer() { return m_pRenderer; }
	static CKeyboard *GetKeyboard() { return m_pKeyboard; }
	static CMouse *GetMouse() { return m_pMouse; }
	static CGamePad *GetGamepad() { return m_pGamepad; }

	//���[�h�i�[�E�擾
	static void SetMode(MODE mode);
	static MODE GetMode() { return m_aMode; }

	//�Q�[���I���̃t���O�i�[�E�擾
	static void SetGameEnd(bool GameEnd) { m_bGameEnd = GameEnd; }
	static bool GetGameEnd() { return m_bGameEnd; }


	//���ꂼ��̃��[�h�n�����
	static CTitle *GetTitle() { return m_pTitle; }
	static CGame *GetGame() { return m_pGame; }
	static CResultRank *GetResultRank() { return m_pResultRank; }
	static CResultSelect *GetResultSelect() { return m_pResultSelect; }
	static CTutorial *GetTutorial() { return m_pTutorial; }
	static CEntry *GetEntry() { return m_pEntry; }

	//�Q�[���N���A�֌W
	static bool GetGameClear() { return m_bGameClear; }
	static void SetGameClear(bool Set) { m_bGameClear = Set; }

	//Pause�����ǂ������Ƃ�����
	static void SetPause(bool bFlag) { m_bPause = bFlag; }
	static bool GetPause() { return m_bPause; };

	//�J�E���g�_�E���֘A
	static void SetCountdown(bool bCountdown) { m_bCountdown = bCountdown; }
	static bool GetCountdown() { return m_bCountdown; }

	//�N���A��̃X�g�b�v
	static void SetEnd(bool bFlag) { m_bEnd = bFlag; }
	static bool GetEnd() { return m_bEnd; };

private:
	static CRenderer *m_pRenderer;
	static CKeyboard *m_pKeyboard;
	static CMouse *m_pMouse;
	static CGamePad *m_pGamepad;

	static int m_nTime;			//�Q�[���I����̃X�R�A���ꎞ�I�Ɋi�[

	static bool m_bGameEnd;		//�Q�[���I��������

	static MODE m_aMode;		//���݂̃��[�h

								//�n�����
	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResultRank *m_pResultRank;
	static CResultSelect *m_pResultSelect;
	static CTutorial *m_pTutorial;
	static CEntry *m_pEntry;

	static bool m_bGameClear;	//�Q�[���N���A�������ǂ���
	static bool m_bPause;		//Pause�����ǂ���
	static bool m_bEnd;			//�Q�[���I����
	static bool m_bCountdown;	//�J�E���g�_�E������

};

#endif