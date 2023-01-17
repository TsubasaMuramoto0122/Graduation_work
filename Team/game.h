//=============================================================================
//ゲーム管理[Game.h]
// Author : 三上航世
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "manager.h"
#include "scene.h"

//*****************************************************************************
//前方宣言
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

	//選択番号を何とかできるやつ
	static int GetSelectNum() { return m_SelectNum; };

private:
	void TimerUI();
	void Annihilation();
	void SetPlayerSurviveTime();	// プレイヤーの生存時間のセーブ
	void Pause();
	void PauseSelect();
	void PauseChange(int nAdd);
	void Snow();
	void StartSnow();

	int GetSurviveTime(void);

	static bool m_bCountFlag;		// カウントダウン中かどうか
	static int m_SelectNum;			// 選択番号
	int m_nDefeatNum;				// やられたプレイヤーの人数
	bool m_bAnnihilation;			// 全滅したかどうか
	CPlayer *m_pPlayer[4];			// プレイヤーのポインタ
	CGamePad *m_pGamePad;			// ゲームパッドのポインタ

	int m_nSelect;					// 選んでるポーズの選択肢
	int m_nGamePad;					// 何のゲームパッドが選ばれてるか
	CPauseUI *m_pUI[3];				// ポーズUI

	int m_nTime;					// 残り時間
	int m_nMaxTime;
	CUI *m_pTimeUI[3];				// タイマーUI
	bool m_bDeath[4];				// 死んだか
	int m_nSnowMaxTime;
	int m_nSnowTime;
};

#endif // _GAME_H_