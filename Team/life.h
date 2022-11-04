//=============================================================================
// ライフ管理 [life.h]
// Author : Kusakari Kakeru
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_LIFE_IMAGE	(4)		// ライフの画像の最大数

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "ui.h"
//#include "DxLib.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CLifeUI : public CUI
{
public:
	CLifeUI(PRIORITY Priority);									// コンストラクタ
	~CLifeUI();													// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);			// 初期化処理
	void Uninit();												// 終了処理
	void Update();												// 更新処理
	void Draw();												// 描画処理
	static CLifeUI *Create(D3DXVECTOR2 pos, D3DXVECTOR2 size);	// 生成処理
	void SetLifeBar(int nNowLife, int nMaxLife);				// ライフバーの設定処理
	void SetOut();												// アウト設置

private:
	int m_nLife;												// ライフ
	float m_fObjectiveSize;										// 目的のサイズ
	float m_fMaxSize;											// 最大のサイズ
	D3DXVECTOR3 m_pos;											// 位置
	D3DXVECTOR2 m_size;											// サイズ
	D3DXVECTOR2 m_barPos;										// ゲージ部分の位置
	CUI *m_apUI[MAX_LIFE_IMAGE];								// UIのポインタ
};
#endif //_LIFE_H_