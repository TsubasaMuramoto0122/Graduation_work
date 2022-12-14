//=============================================================================
// スタンバイUI処理 [standbyUI.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "standbyui.h"
#include "fade.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define COUNT_TIME		(35)
#define SHRINK_SIZE_X	(2.2f)
#define SHRINK_SIZE_Y	(1.0f)

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CStandbyUI::CStandbyUI(CScene::PRIORITY Priority) : CUI(Priority)
{
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_nTime = 0;
	m_bShrink = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CStandbyUI::~CStandbyUI()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStandbyUI::Init(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	m_size = size;
	m_nTime = 0;
	m_bShrink = false;
	CUI::Init(pos, m_size, 19, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStandbyUI::Uninit()
{
	CUI::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CStandbyUI::Update()
{
	m_nTime++;

	if (m_bShrink == false)
	{
		m_size.x += SHRINK_SIZE_X;
		m_size.y += SHRINK_SIZE_Y;
	}
	else
	{
		m_size.x -= SHRINK_SIZE_X;
		m_size.y -= SHRINK_SIZE_Y;
	}

	SetSize(m_size);

	if (m_nTime > COUNT_TIME)
	{
		m_bShrink = !m_bShrink;
		m_nTime = 0;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CStandbyUI::Draw()
{
	CUI::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CStandbyUI *CStandbyUI::Create(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	CStandbyUI *pStandbyUI = NULL;
	pStandbyUI = new CStandbyUI(PRIORITY_UI);

	if (pStandbyUI != NULL)
	{
		pStandbyUI->Init(pos, size);
	}

	return pStandbyUI;
}