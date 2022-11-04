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
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }

	static CGame *Create();

	//選択番号を何とかできるやつ
	static int GetSelectNum() { return m_SelectNum; };

private:
	void TimerUI();
	void Annihilation();
	void SetPlayerSurviveTime();	// プレイヤーの生存時間のセーブ

	int GetSurviveTime(void);

	static bool m_bCountFlag;		// カウントダウン中かどうか
	static int m_SelectNum;			// 選択番号
	int m_nDefeatNum;				// やられたプレイヤーの人数
	bool m_bAnnihilation;			// 全滅したかどうか
	CPlayer *m_pPlayer[4];			// プレイヤーのポインタ

	int m_nTime;
	CUI *m_pTimeUI[3];
	bool m_bDeath[4];
};

#endif // _GAME_H_