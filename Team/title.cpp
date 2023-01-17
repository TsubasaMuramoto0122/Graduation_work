//=============================================================================
//
// タイトル処理 [title.h]
// Author : 三上航世
//
//=============================================================================
//*****************************************************************************
//インクルード
//*****************************************************************************
#if 1
#include "title.h"
#include "keyboard.h"
#include "ui.h"

#include "game.h"
#include "gamepad.h"
#include "fade.h"

#include "sound.h"
#endif

//*****************************************************************************
//静的
//*****************************************************************************

//*****************************************************************************
//マクロ
//*****************************************************************************
#define MAX_FADE_TIME (60)
#define MAX_SELECT (2)

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CTitle::CTitle(PRIORITY Priority) : CScene(Priority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CTitle::~CTitle()
{
}
#endif

//*****************************************************************************
// 初期化
//***************************************************************************** 
HRESULT CTitle::Init(D3DXVECTOR3 /*pos*/)
{
	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();

	//m_SerectNam = 1;
	//SetSerectNum(m_SerectNam);
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 28, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 300.0f, 300.0f), D3DXVECTOR2(360.0f, 260.0f), 29, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, 300.0f), D3DXVECTOR2(500.0f, 130.0f), 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pUI[0] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f - 270.0f, 540.0f), D3DXVECTOR2(500.0f, 100.0f), 25, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pUI[1] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f - 270.0f, 540.0f), D3DXVECTOR2(460.0f, 70.0f), 26, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pUI[2] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 270.0f, 540.0f), D3DXVECTOR2(500.0f, 100.0f), 25, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_pUI[3] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 270.0f, 540.0f), D3DXVECTOR2(460.0f, 70.0f), 27, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_fClear = 1.0f;
	CManager::SetPause(false);
	CSound::Play(0);
	return S_OK;
}

//*****************************************************************************
// 終了
//***************************************************************************** 
void CTitle::Uninit()
{
	int nCntUI;
	for (nCntUI = 0; nCntUI < 4; nCntUI++)
	{
		if (m_pUI[nCntUI] != NULL)
		{
			m_pUI[nCntUI] = NULL;
		}
	}
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	if (m_pGamePad != NULL)
	{
		m_pGamePad = NULL;
	}
	Release();
}

//*****************************************************************************
// kousinn
//***************************************************************************** 
void CTitle::Update()
{
#ifdef _DEBUG
	if (m_pKeyboard != NULL)
	{
		SelectFade();
		if (m_pKeyboard->GetKey(DIK_A) == true)
		{
			SelectChange(-1);
		}
		if (m_pKeyboard->GetKey(DIK_D) == true)
		{
			SelectChange(1);
		}
		if (m_pKeyboard->GetKey(DIK_RETURN) == true)
		{
			Select();
		}
	}
#endif
	if (m_pGamePad != NULL)
	{
		if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_LEFT, 0) == true)
		{
			SelectChange(-1);
		}
		if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_RIGHT, 0) == true)
		{
			SelectChange(1);
		}
		if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_B, 0) == true)
		{
			Select();
		}
	}
}

#if 1
//*****************************************************************************
//描画
//***************************************************************************** 
void CTitle::Draw()
{

}

void CTitle::ZTexDraw()
{

}

//*****************************************************************************
//描画
//***************************************************************************** 
CTitle *CTitle::Create()
{
	CTitle *pTitle = NULL;
	pTitle = new CTitle(PRIORITY_PLANE);		//メモリ確保
	//NULLチェック
	if (pTitle != NULL)
	{
		pTitle->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pTitle;
}
#endif

void CTitle::SelectChange(int nAdd)
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
	CSound::Play(13);
}

void CTitle::Select()
{
	switch (m_nSelect)
	{
	case 0:
		CFade::SetFade(CManager::MODE_ENTRY);
		break;
	case 1:
		CFade::SetFade(CManager::MODE_TUTORIAL);
		break;
	default:
		break;
	}
	CSound::Play(12);
}

void CTitle::SelectFade()
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