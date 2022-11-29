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
	static bool GetStandby(int nNum);	// 待機取得処理

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	void SetPos(D3DXVECTOR3) { ; }

private:
	void DisplayOkUI(int nNum, bool bEntry);	// UI表示処理
	CKeyboard *m_pKeyboard;						// キーボードのポインタ
	CGamePad *m_pGamePad;						// ゲームパッドのポインタ
	CStandbyUI *m_pStandbyUI[4];				// スタンバイのUIのポインタ
	bool m_bCanStart;							// スタートできるかどうか
	static bool m_bStandby[4];					// 待機してるかどうか
};

#endif // _ENTRY_H_