//=============================================================================
//
// フィニッシュUI処理 [finishui.h]
// Author : 三上航世
//
//=============================================================================
//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "finish.h"
#include "fade.h"
#include "manager.h"
#include "sound.h"

//*****************************************************************************
//静的
//*****************************************************************************

//*****************************************************************************
//マクロ
//*****************************************************************************
#define COUNT_TIME (120)

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CFinish::CFinish(CScene::PRIORITY Priority) : CUI(Priority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CFinish::~CFinish()
{

}
#endif

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CFinish::Init()
{
	m_nTime = COUNT_TIME;
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 250.0f, 0.0f), D3DXVECTOR2(540.0f, 180.0f), 13, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CManager::SetGameEnd(true);
	CSound::Play(14);
	return S_OK;
}

//*****************************************************************************
//終了
//*****************************************************************************
void CFinish::Uninit()
{
	CScene::Release();
}

//*****************************************************************************
//更新
//*****************************************************************************
void CFinish::Update()
{
	m_nTime--;
	if (m_nTime <= 0)
	{
		CFade::SetFade(CManager::MODE_RESULTRANK);
	}
}

//描画・作成
#if 1
//*****************************************************************************
//描画
//*****************************************************************************
void CFinish::Draw()
{

}

//*****************************************************************************
//作成
//*****************************************************************************
CFinish *CFinish::Create()
{
	CFinish *pFinish = NULL;
	pFinish = new CFinish(PRIORITY_UI);
	if (pFinish != NULL)
	{
		pFinish->Init();
	}
	return pFinish;
}
#endif
