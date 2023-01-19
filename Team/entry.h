//=============================================================================
// プレイヤーエントリー管理 [entry.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _ENTRY_H_
#define _ENTRY_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CKeyboard;
class CGamePad;
class CUI;
class CStandbyUI;
class CPauseUI;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEntry : public CScene
{
public:
	CEntry(PRIORITY Priority);			// コンストラクタ
	~CEntry();							// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);		// 初期化処理
	void Uninit();						// 終了処理
	void Update();						// 更新処理
	void Draw();						// 描画処理
	void ZTexDraw();

	static CEntry *Create();			// 作成処理
	static bool GetStandby(int nNum) { return m_bStandby[nNum]; }	// 待機取得処理
	static int SelectStage() { return m_nStage; }

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	void SetPos(D3DXVECTOR3) { ; }

private:
	void DisplayOkUI(int nNum, bool bEntry);	// UI表示処理
	bool ReadyGo();								// 誰かGOサイン出してるか
	void Stage();
	void StageUIMove();
	void StageChange(int nLine, int nAdd);
	void GameStart();

	CKeyboard *m_pKeyboard;			// キーボードのポインタ
	CGamePad *m_pGamePad;			// ゲームパッドのポインタ
	CStandbyUI *m_pStandbyUI[4];	// スタンバイのUIのポインタ
	CUI *m_pBg;						// 背景
	CUI *m_pStage[18];				// ステージ
	int m_nTime;
	bool m_bStageSelect;
	int m_nLine[2];

	static bool m_bStandby[4];					// 待機してるかどうか
	static int m_nStage;
};
#endif // _ENTRY_H_