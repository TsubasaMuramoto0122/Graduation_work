//=============================================================================
//
// ゲームスタートUI処理 [readyui.h]
// Author : 三上航世
//
//=============================================================================
//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "readyui.h"
#include "fade.h"
#include "manager.h"


//*****************************************************************************
//静的
//*****************************************************************************

//*****************************************************************************
//マクロ
//*****************************************************************************
#define COUNT_TIME (100)

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CReadyUI::CReadyUI(CScene::PRIORITY Priority) : CUI(Priority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CReadyUI::~CReadyUI()
{

}
#endif

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CReadyUI::Init()
{
	CManager::SetCountdown(true);
	m_nTime = 40;
	m_nPattern = 0;
	m_fClear = 1.0f;
	m_size = D3DXVECTOR2(540.0f, 180.0f);
	return S_OK;
}

//*****************************************************************************
//終了
//*****************************************************************************
void CReadyUI::Uninit()
{
	if (m_pUI != NULL)
	{
		m_pUI->SetDeath(true);
		m_pUI = NULL;
	}
	CScene::Release();
}

//*****************************************************************************
//更新
//*****************************************************************************
void CReadyUI::Update()
{
	m_nTime--;
	if (m_nPattern == 1)
	{
		if (m_nTime >= 40)
		{
			m_size.x -= 3.0f;
			m_size.y -= 1.0f;
			m_pUI->SetSize(m_size);
		}
	}
	else if (m_nPattern == 2)
	{
		m_size.x += 2.0f;
		m_size.y += 1.4f;
		m_fClear -= 1.0f / (float)COUNT_TIME;
		m_pUI->SetSize(m_size);
		m_pUI->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fClear));
	}

	if (m_nTime <= 0)
	{
		m_nPattern++;
		m_nTime = COUNT_TIME;
		switch (m_nPattern)
		{
		case 1:
			m_pUI = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(420.0f, 140.0f), 19, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_size = D3DXVECTOR2(420.0f, 140.0f);
			break;
		case 2:
			m_pUI->SetTexture(15);
			m_size = D3DXVECTOR2(120.0f, 80.0f);
			m_pUI->SetSize(D3DXVECTOR2(120.0f, 80.0f));
			CManager::SetCountdown(false);
			break;
		case 3:
			SetDeath(true);
			break;
		default:
			break;
		}
	}
}

//描画・作成
#if 1
//*****************************************************************************
//描画
//*****************************************************************************
void CReadyUI::Draw()
{

}

//*****************************************************************************
//作成
//*****************************************************************************
CReadyUI *CReadyUI::Create()
{
	CReadyUI *pReadyUI = NULL;
	pReadyUI = new CReadyUI(PRIORITY_UI);
	if (pReadyUI != NULL)
	{
		pReadyUI->Init();
	}
	return pReadyUI;
}
#endif
