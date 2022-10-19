//=============================================================================
//
// リザルトランキング処理 [result.h]
// Author : 三上航世
//
//=============================================================================
//*****************************************************************************
// インクルードファイル
//***************************************************************************** 
#if 1
#include "fade.h"
#include "resultrank.h"
#include "keyboard.h"
#include "gamepad.h"
#include "ui.h"

#include "sound.h"
#endif
//*****************************************************************************
// 静的メンバ変数
//***************************************************************************** 

//*****************************************************************************
//マクロ
//*****************************************************************************
#define MAX_FADE_TIME (60)
#define MAX_SELECT (3)

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CResultRank::CResultRank(PRIORITY Priority) :CScene(Priority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CResultRank::~CResultRank()
{

}
#endif
//*****************************************************************************
// 初期化
//***************************************************************************** 
HRESULT CResultRank::Init(D3DXVECTOR3 /*pos*/)
{
	m_pKeyboard = CManager::GetKeyboard();

	//背景、文字、枠
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 80.0f, 0.0f), D3DXVECTOR2(500.0f, 100.0f), 18, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 380.0f, 0.0f), D3DXVECTOR2(880.0f, 680.0f), 14, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	int nCntRank;

	//王冠
	for (nCntRank = 0; nCntRank < 4; nCntRank++)
	{
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 270.0f, 240.0f + 125.0f * nCntRank, 0.0f), D3DXVECTOR2(160.0f, 140.0f), 12, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//順位
	for (nCntRank = 0; nCntRank < 4; nCntRank++)
	{
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 100.0f, 240.0f + 125.0f * nCntRank, 0.0f), D3DXVECTOR2(160.0f, 108.0f), 4 + nCntRank, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	
	//nP
	for (nCntRank = 0; nCntRank < 4; nCntRank++)
	{
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 60.0f, 240.0f + 125.0f * nCntRank, 0.0f), D3DXVECTOR2(120.0f, 90.0f), 8 + nCntRank, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	int nCntUI;
	for (nCntRank = 0; nCntRank < 4; nCntRank++)
	{
		for (nCntUI = 0; nCntUI < 3; nCntUI++)
		{
			m_pUI[nCntRank * 3 + nCntUI] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 180.0f + 60.0f * nCntUI, 240.0f + 125.0f * nCntRank, 0.0f), D3DXVECTOR2(54.0f, 90.0f), 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pUI[nCntRank * 3 + nCntUI]->SetTex(0, 0.1f);
		}
	}

	
	CSound::Play(3);
	//bool RankOnly = CManager::GetRankOnly();

	//UIの配置
	//CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 190.0f, 0), 300.0f, 50.0f, 14, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//UI

	////ランキングの番号UI配置
	//CUI::Create(D3DXVECTOR3(520.0f, 270.0f, 0), 60.0f, 50.0f, 9, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//UI
	//CUI::Create(D3DXVECTOR3(520.0f, 350.0f, 0), 60.0f, 50.0f, 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//UI
	//CUI::Create(D3DXVECTOR3(520.0f, 430.0f, 0), 60.0f, 50.0f, 11, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//UI
	//CUI::Create(D3DXVECTOR3(520.0f, 510.0f, 0), 60.0f, 50.0f, 12, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//UI
	//CUI::Create(D3DXVECTOR3(520.0f, 590.0f, 0), 60.0f, 50.0f, 13, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//UI

	return S_OK;
}

//*****************************************************************************
// 終了
//***************************************************************************** 
void CResultRank::Uninit()
{
	int nCnt;
	for (nCnt = 0; nCnt < 6; nCnt++)
	{
		if (m_pUI[nCnt] != NULL)
		{
			m_pUI[nCnt] = NULL;
		}
	}
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	CScene::Release();
}

//*****************************************************************************
// kousinn
//***************************************************************************** 
void CResultRank::Update()
{
	if (m_pKeyboard != NULL)
	{
		if (m_pKeyboard->GetAnyKey() == true)
		{
			CFade::SetFade(CManager::MODE_RESULTSELECT);

		}
	}
}

//描画・作成
#if 1
//*****************************************************************************
//描画
//***************************************************************************** 
void CResultRank::Draw()
{

}

//*****************************************************************************
//作成
//***************************************************************************** 
CResultRank *CResultRank::Create()
{
	CResultRank *pResultRank = NULL;
	pResultRank = new CResultRank(PRIORITY_ORBIT);		//メモリ確保
	//NULLチェック
	if (pResultRank != NULL)
	{
		pResultRank->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pResultRank;
}
#endif