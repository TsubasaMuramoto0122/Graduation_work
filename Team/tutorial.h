//=============================================================================
// チュートリアル管理 [tutorial.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUI;
class CKeyboard;
class CMeshWall;
class CMeshField;
//class CGamePad;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTutorial : public CScene
{
public:
	CTutorial(PRIORITY Priority);	// コンストラクタ
	~CTutorial();					// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);	// 初期化処理
	void Uninit();					// 終了処理
	void Update();					// 更新処理
	void Draw();					// 描画処理
	void ZTexDraw();
	static CTutorial *Create();		// 作成処理

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	void SetPos(D3DXVECTOR3) { ; }

private:
	CKeyboard *m_pKeyboard;			// キーボードのポインタ
	CMeshField *m_pMeshField[2];	// メッシュフィールドのポインタ
	CMeshWall *m_pMeshWall[4];		// メッシュウォールのポインタ
};

#endif // _TUTORIAL_H_