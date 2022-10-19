//=============================================================================
//
// リザルト選択処理 [result.h]
// Author : 三上航世
//
//=============================================================================
//*****************************************************************************
// インクルードファイル
//***************************************************************************** 
#if 1
#include "fade.h"
#include "resultselect.h"
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
CResultSelect::CResultSelect(PRIORITY Priority) :CScene(Priority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CResultSelect::~CResultSelect()
{

}
#endif
//*****************************************************************************
// 初期化
//***************************************************************************** 
HRESULT CResultSelect::Init(D3DXVECTOR3 /*pos*/)
{
	m_pKeyboard = CManager::GetKeyboard();
	//m_pGamePad = CManager::GetGamepad();

	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 560.0f, 0.0f), D3DXVECTOR2(660.0f, 70.0f), 5, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	//CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 200.0f, 0.0f), D3DXVECTOR2(400.0f, 140.0f), 8, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	m_pUI[0] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 180.0f, 0.0f), D3DXVECTOR2(700.0f, 120.0f), 24, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pUI[1] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 180.0f, 0.0f), D3DXVECTOR2(650.0f, 100.0f), 20, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pUI[2] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f		, 0.0f), D3DXVECTOR2(700.0f, 120.0f), 24, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_pUI[3] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f		, 0.0f), D3DXVECTOR2(650.0f, 100.0f), 21, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_pUI[4] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 180.0f, 0.0f), D3DXVECTOR2(700.0f, 120.0f), 24, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_pUI[5] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 180.0f, 0.0f), D3DXVECTOR2(650.0f, 100.0f), 22, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	
	m_nSelect = 0;

	m_fClear = 1.0f;

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
void CResultSelect::Uninit()
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
void CResultSelect::Update()
{
	if (m_pKeyboard != NULL)
	{
		if (m_pKeyboard->GetKey(DIK_W) == true)
		{
			SelectChange(-1);
		}
		if (m_pKeyboard->GetKey(DIK_S) == true)
		{
			SelectChange(1);
		}
		if (m_pKeyboard->GetKey(DIK_RETURN) == true)
		{
			Select();
		}
	}
	SelectFade();
}

//描画・作成
#if 1
//*****************************************************************************
//描画
//***************************************************************************** 
void CResultSelect::Draw()
{

}

//*****************************************************************************
//作成
//***************************************************************************** 
CResultSelect *CResultSelect::Create()
{
	CResultSelect *pResultSelect = NULL;
	pResultSelect = new CResultSelect(PRIORITY_ORBIT);		//メモリ確保
												//NULLチェック
	if (pResultSelect != NULL)
	{
		pResultSelect->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pResultSelect;
}
#endif

void CResultSelect::SelectChange(int nAdd)
{
	m_pUI[m_nSelect * 2]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_pUI[m_nSelect * 2 + 1]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_nSelect += nAdd;
	if (m_nSelect < 0)
	{
		m_nSelect = MAX_SELECT;
	}
	else if (m_nSelect > MAX_SELECT)
	{
		m_nSelect = 0;
	}
	m_pUI[m_nSelect * 2]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pUI[m_nSelect * 2 + 1]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_nFadeTime = 0;
	m_fClear = 1.0f;
	CSound::Play(15);
}

void CResultSelect::Select()
{
	switch (m_nSelect)
	{
	case 0:
		CFade::SetFade(CManager::MODE_GAME);
		break;
	case 1:
		CFade::SetFade(CManager::MODE_TITLE);
		break;
	case 2:
		CFade::SetFade(CManager::MODE_TITLE);
		break;
	default:
		break;
	}
	CSound::Play(10);
}

void CResultSelect::SelectFade()
{
	m_nFadeTime++;
	if (m_nFadeTime > MAX_FADE_TIME / 2)
	{
		m_fClear += 1.0f / ((float)MAX_FADE_TIME / 2.0f);
		if (m_nFadeTime >= MAX_FADE_TIME)
		{
			m_nFadeTime = 0;
		}
	}
	else
	{
		m_fClear -= 1.0f / ((float)MAX_FADE_TIME / 2.0f);
	}
	m_pUI[m_nSelect * 2]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fClear));
	m_pUI[m_nSelect * 2 + 1]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fClear));
}