//=============================================================================
// ステージセレクト管理 [stageselect.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _STAGE_SELECT_H_
#define _STAGE_SELECT_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "scene.h"

//*****************************************************************************
//マクロ
//*****************************************************************************
#define MAX_STAGESELECT_UI (4)	// 選択肢のUIの数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CKeyboard;
class CGamePad;
class CUI;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CStageSelect : public CScene
{
public:
	CStageSelect(PRIORITY Priority);	// コンストラクタ
	~CStageSelect();					// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);		// 初期化処理
	void Uninit();						// 終了処理
	void Update();						// 更新処理
	void Draw();						// 描画処理
	static CStageSelect *Create();		// 作成処理
	void ZTexDraw() { ; }

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	void SetPos(D3DXVECTOR3) { ; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }

	static int GetStageNum(void) { return m_nSelect; }	// ステージ番号取得処理

private:
	void SelectChange(int nLine, int nRow);		// 選択肢の変更処理

	CKeyboard *m_pKeyboard;						// キーボードのポインタ
	CGamePad *m_pGamePad;						// ゲームパッドのポインタ
	CUI *m_pUI[MAX_STAGESELECT_UI];				// UIのポインタ
	static int m_nSelect;						// 選択肢
	static int m_nLine;							// 行
	static int m_nRow;							// 列
};

#endif // _STAGE_SELECT_H_