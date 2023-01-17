//=============================================================================
//
// カウントダウンUI処理 [playerui.h]
// Author : 三上航世
//
//=============================================================================
//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "playerui.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
//静的
//*****************************************************************************

//*****************************************************************************
//マクロ
//*****************************************************************************

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CPlayerUI::CPlayerUI(CScene::PRIORITY Priority) : CUI(Priority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CPlayerUI::~CPlayerUI()
{

}
#endif

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CPlayerUI::Init(int nTex)
{
	CUI::Init(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(50.0f, 35.0f), nTex, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_fHeight = 90.0f;
	m_bDraw = false;
	return S_OK;
}

//*****************************************************************************
//終了
//*****************************************************************************
void CPlayerUI::Uninit()
{
	CUI::Uninit();
}

//*****************************************************************************
//更新
//*****************************************************************************
void CPlayerUI::Update()
{
	
}

//*****************************************************************************
//描画
//*****************************************************************************
void CPlayerUI::Draw()
{
	if (m_bDraw == true)
	{
		CUI::Draw();
	}
}

//*****************************************************************************
//作成
//*****************************************************************************
CPlayerUI *CPlayerUI::Create(int nTex)
{
	CPlayerUI *pPlayerUI = NULL;
	pPlayerUI = new CPlayerUI(PRIORITY_UI);
	if (pPlayerUI != NULL)
	{
		pPlayerUI->Init(nTex);
	}
	return pPlayerUI;
}

void CPlayerUI::SetPos(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice;   //デバイスのポインタ
	D3DXMATRIX mtxView, mtxProjection, mtxPlayer, mtxTrans, mtxParent;
	D3DXMATRIX mtxViewport =
	{ SCREEN_WIDTH / 2, 0, 0, 0, 0, -SCREEN_HEIGHT / 2, 0, 0, 0, 0, 1, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 1 }; //ビューポート配列
	pDevice = CManager::GetRenderer()->GetDevice();		 //デバイスを取得する
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxPlayer);
	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, 0.0f, m_fHeight, 0.0f);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxTrans);
	//パーツマトリックスの取得、反映
	D3DXMatrixTranslation(&mtxParent, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxParent);
	//ビュー変換
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxView);
	//射影変換
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxProjection);
	//ビューポート変換
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxViewport);
	mtxPlayer._41 /= mtxPlayer._44;
	mtxPlayer._42 /= mtxPlayer._44;

	if (mtxPlayer._41 <= 0.0f || SCREEN_WIDTH <= mtxPlayer._41 ||
		mtxPlayer._42 <= 0.0f || SCREEN_HEIGHT <= mtxPlayer._42 || mtxPlayer._43 < 0.0f)
	{
		m_bDraw = false;
	}
	else
	{
		m_bDraw = true;
		CScene2D::SetPos(D3DXVECTOR3(mtxPlayer._41, mtxPlayer._42, 0.0f));
	}
}