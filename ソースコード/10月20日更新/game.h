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
//*****************↓↓↓更新部分↓↓↓*****************//
class CPlayer;
//*****************↑↑↑更新部分↑↑↑*****************//
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

	//選択番号を何とかできるやつ
	static int GetSelectNum() { return m_SelectNum; };

private:
	void TimerUI();
	//*****************↓↓↓更新部分↓↓↓*****************//
	void Annihilation();
	//*****************↑↑↑更新部分↑↑↑*****************//

	static bool m_bCountFlag;		//カウントダウン中かどうか
	static int m_SelectNum;			//選択番号

	int m_nTime;
	//*****************↓↓↓更新部分↓↓↓*****************//
	int m_nDefeatNum;				// やられたプレイヤーの人数
	bool m_bAnnihilation;			// 全滅したかどうか
	CPlayer *m_pPlayer[4];			// プレイヤーのポインタ
	//*****************↑↑↑更新部分↑↑↑*****************//
	CUI *m_pTimeUI[3];
	CUI *m_pCountDown[4];
	CMeshField *m_pMeshField[2];	// メッシュフィールドのポインタ
	CMeshWall *m_pMeshWall[4];		// メッシュウォールのポインタ
};

#endif // _GAME_H_
