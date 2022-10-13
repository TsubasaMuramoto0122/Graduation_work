//=============================================================================
//
// リザルト処理 [result.h]
// Author : 三上航世
//
//=============================================================================
//*****************************************************************************
// インクルードファイル
//***************************************************************************** 
#if 1
#include "fade.h"
#include "result.h"
#include "keyboard.h"
#include "gamepad.h"
#include "ui.h"

#include "sound.h"
#endif
//*****************************************************************************
// 静的メンバ変数
//***************************************************************************** 


#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CResult::CResult(PRIORITY Priority) :CScene(Priority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CResult::~CResult()
{

}
#endif
//*****************************************************************************
// 初期化
//***************************************************************************** 
HRESULT CResult::Init(D3DXVECTOR3 /*pos*/)
{
	m_pKeyboard = CManager::GetKeyboard();
	//m_pGamePad = CManager::GetGamepad();

	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 560.0f, 0.0f), D3DXVECTOR2(660.0f, 70.0f), 5, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 200.0f, 0.0f), D3DXVECTOR2(400.0f, 140.0f), 8, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	//CSound::Play(2);
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
void CResult::Uninit()
{
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	/*if (m_pMouse != NULL)
	{
	m_pMouse = NULL;
	}*/
	CScene::Release();
}

//*****************************************************************************
// kousinn
//***************************************************************************** 
void CResult::Update()
{
	if (m_pKeyboard != NULL)
	{
		if (m_pKeyboard->GetAnyKey() == true)
		{
			CFade::SetFade(CManager::MODE_TITLE);
			//CSound::Play(7);
		}
	}
}

//描画・作成
#if 1
//*****************************************************************************
//描画
//***************************************************************************** 
void CResult::Draw()
{

}

//*****************************************************************************
//作成
//***************************************************************************** 
CResult *CResult::Create()
{
	CResult *pResult = NULL;
	pResult = new CResult(PRIORITY_ORBIT);		//メモリ確保
												//NULLチェック
	if (pResult != NULL)
	{
		pResult->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pResult;
}
#endif
