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
	static CTutorial *Create();		// 作成処理

	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetMove() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	void SetPos(D3DXVECTOR3) { ; }
	D3DXVECTOR3 GetPosOld() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	float GetHeight() { return 0.0f; }
	COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	bool GetRotX() { return false; }
	D3DXMATRIX GetMatrix(int) { return D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f); }
	D3DXMATRIX GetMatrix() { return D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f); }

private:
	CKeyboard *m_pKeyboard;			// キーボードのポインタ
	//CGamePad *m_pGamePad;			// ゲームパッドのポインタ
};

#endif // _TUTORIAL_H_