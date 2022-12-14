//=============================================================================
//
// マネージャ [Manager.h]
// Author : 三上航世
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
//=============================================================================
//マクロ
//=============================================================================

//前方宣言
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
		MODE_TITLE,			// タイトル
		MODE_TUTORIAL,		// チュートリアル
		MODE_ENTRY,			// プレイヤーエントリー
		MODE_GAME,			// ゲーム
		MODE_RESULTRANK,	// リザルトランキング
		MODE_RESULTSELECT,	// リザルト後選択
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

	//モード格納・取得
	static void SetMode(MODE mode);
	static MODE GetMode() { return m_aMode; }

	//ゲーム終了のフラグ格納・取得
	static void SetGameEnd(bool GameEnd) { m_bGameEnd = GameEnd; }
	static bool GetGameEnd() { return m_bGameEnd; }


	//それぞれのモード渡すやつ
	static CTitle *GetTitle() { return m_pTitle; }
	static CGame *GetGame() { return m_pGame; }
	static CResultRank *GetResultRank() { return m_pResultRank; }
	static CResultSelect *GetResultSelect() { return m_pResultSelect; }
	static CTutorial *GetTutorial() { return m_pTutorial; }
	static CEntry *GetEntry() { return m_pEntry; }

	//ゲームクリア関係
	static bool GetGameClear() { return m_bGameClear; }
	static void SetGameClear(bool Set) { m_bGameClear = Set; }

	//Pause中かどうか何とかする
	static void SetPause(bool bFlag) { m_bPause = bFlag; }
	static bool GetPause() { return m_bPause; };

	//カウントダウン関連
	static void SetCountdown(bool bCountdown) { m_bCountdown = bCountdown; }
	static bool GetCountdown() { return m_bCountdown; }

	//クリア後のストップ
	static void SetEnd(bool bFlag) { m_bEnd = bFlag; }
	static bool GetEnd() { return m_bEnd; };

private:
	static CRenderer *m_pRenderer;
	static CKeyboard *m_pKeyboard;
	static CMouse *m_pMouse;
	static CGamePad *m_pGamepad;

	//static int m_nTime;		//ゲーム終了後のスコアを一時的に格納
	static bool m_bGameEnd;		//ゲーム終了したか

	static MODE m_aMode;		//現在のモード

								//渡すやつ
	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResultRank *m_pResultRank;
	static CResultSelect *m_pResultSelect;
	static CTutorial *m_pTutorial;
	static CEntry *m_pEntry;

	static bool m_bGameClear;	//ゲームクリアしたかどうか
	static bool m_bPause;		//Pause中かどうか
	static bool m_bEnd;			//ゲーム終了か
	static bool m_bCountdown;	//カウントダウン中か

};

#endif