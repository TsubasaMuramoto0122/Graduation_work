//=============================================================================
// プレイヤーエントリー管理 [entry.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// インクルードファイル
//***************************************************************************** 
#include "entry.h"
#include "fade.h"
#include "keyboard.h"
#include "gamepad.h"
#include "ui.h"
#include "okui.h"
#include "sound.h"

//*****************************************************************************
// 静的メンバ変数宣言
//***************************************************************************** 
bool CEntry::m_bStandby[4] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CEntry::CEntry(PRIORITY Priority) :CScene(Priority)
{
	m_pKeyboard = NULL;
	m_pGamePad = NULL;

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_bStandby[nCnt] = false;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CEntry::~CEntry()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEntry::Init(D3DXVECTOR3)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_bStandby[nCnt] = false;
	}

	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
	{
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 5.0f + (SCREEN_WIDTH / 5.0f * nCntPlayer), 300.0f, 0.0f), D3DXVECTOR2(130.0f, 80.0f), 8 + nCntPlayer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}
	
	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();

	//CSound::Play(2);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEntry::Uninit()
{
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	if (m_pGamePad != NULL)
	{
		m_pGamePad = NULL;
	}
	for (int nCntUI = 0; nCntUI < 4; nCntUI++)
	{
		if (m_pOkUI[nCntUI] != NULL)
		{
			m_pOkUI[nCntUI]->Uninit();
			m_pOkUI[nCntUI] = NULL;
		}
	}

	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEntry::Update()
{
	if (m_pKeyboard != NULL)
	{
		if (m_pKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			CFade::SetFade(CManager::MODE_GAME);
			CSound::Play(10);
		}

		if (m_pKeyboard->GetTrigger(DIK_SPACE) == true)
		{
			DisplayOkUI(0, m_bStandby[0]);
		}
		if (m_pKeyboard->GetTrigger(DIK_B) == true)
		{
			DisplayOkUI(1, m_bStandby[1]);
		}
		if (m_pKeyboard->GetTrigger(DIK_N) == true)
		{
			DisplayOkUI(2, m_bStandby[2]);
		}
		if (m_pKeyboard->GetTrigger(DIK_M) == true)
		{
			DisplayOkUI(3, m_bStandby[3]);
		}
	}
	if (m_pGamePad != NULL)
	{
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START, nCnt) == true)
			{
				CFade::SetFade(CManager::MODE_GAME);
				CSound::Play(10);
			}

			if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A, nCnt) == true)
			{
				DisplayOkUI(nCnt, m_bStandby[nCnt]);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEntry::Draw()
{

}

//=============================================================================
// 作成処理
//=============================================================================
CEntry *CEntry::Create()
{
	CEntry *pEntry = NULL;
	pEntry = new CEntry(PRIORITY_ORBIT);		//メモリ確保
	//NULLチェック
	if (pEntry != NULL)
	{
		pEntry->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	return pEntry;
}

//=============================================================================
// 作成処理
//=============================================================================
void CEntry::DisplayOkUI(int nNum, bool bEntry)
{
	if (bEntry == false)
	{
		// UIを生成
		if (m_pOkUI[nNum] == NULL)
		{
			m_pOkUI[nNum] = COkUI::Create(D3DXVECTOR2(SCREEN_WIDTH / 5.0f + (SCREEN_WIDTH / 5.0f * nNum), 300.0f), D3DXVECTOR2(160.0f, 90.0f));
		}
	}
	else
	{
		// UIを消去
		if (m_pOkUI[nNum] != NULL)
		{
			m_pOkUI[nNum]->Uninit();
			m_pOkUI[nNum] = NULL;
		}
	}

	// falseまたはtrueを現在とは逆の状態にする
	m_bStandby[nNum] = !m_bStandby[nNum];
}

//=============================================================================
// 待機取得処理
//=============================================================================
bool CEntry::GetStandby(int nNum)
{
	return m_bStandby[nNum];
}