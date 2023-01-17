//=============================================================================
// プレイヤーエントリー管理 [entry.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// インクルードファイル
//***************************************************************************** 
#include "stageselect.h"
#include "fade.h"
#include "keyboard.h"
#include "gamepad.h"
#include "ui.h"
#include "sound.h"

//*****************************************************************************
// マクロ
//*****************************************************************************
#define TOP_POS_Y	(60)
#define TOP_SIZE_X	(500)
#define TOP_SIZE_Y	(90)
#define SELECT_POS_Y	(250)
#define SELECT_SIZE_X	(300)
#define SELECT_SIZE_Y	(200)

//*****************************************************************************
//静的
//*****************************************************************************
int CStageSelect::m_nSelect = 0;
int CStageSelect::m_nLine = 0;
int CStageSelect::m_nRow = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CStageSelect::CStageSelect(PRIORITY Priority) :CScene(Priority)
{
	// 変数のクリア
	m_pKeyboard = NULL;
	m_pGamePad = NULL;
	for (int nCntUI = 0; nCntUI < MAX_STAGESELECT_UI; nCntUI++)
	{
		m_pUI[nCntUI] = NULL;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CStageSelect::~CStageSelect()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CStageSelect::Init(D3DXVECTOR3)
{
	// 変数の初期化
	m_nSelect = 0;
	m_nLine = 0;
	m_nRow = 0;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI：背景
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, TOP_POS_Y), D3DXVECTOR2(TOP_SIZE_X, TOP_SIZE_Y), -1, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI：選択肢
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int nLine = 0, nRow = 0;
	for (int nCntUI = 0; nCntUI < MAX_STAGESELECT_UI; nCntUI++)
	{
		if (nCntUI % 2 == 0)
		{
			nLine = 1;

			if (nCntUI != 0)
			{
				nRow++;
			}
		}
		else
		{
			nLine = 2;
		}

		m_pUI[nCntUI] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH / 3.0f * nLine, SELECT_POS_Y + 300.0f * nRow), D3DXVECTOR2(SELECT_SIZE_X, SELECT_SIZE_Y), -1, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	}

	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStageSelect::Uninit()
{
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	if (m_pGamePad != NULL)
	{
		m_pGamePad = NULL;
	}

	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CStageSelect::Update()
{
	// フェードしていない時のみ
	if (CFade::GetFade() == CFade::FADE_NONE)
	{
		if (m_pKeyboard != NULL)
		{
			if (m_pKeyboard->GetKey(DIK_SPACE) == true || m_pKeyboard->GetKey(DIK_RETURN) == true)
			{
				CFade::SetFade(CManager::MODE_ENTRY);
			}

			if (m_pKeyboard->GetKey(DIK_A) == true)
			{
				SelectChange(-1, 0);
			}
			if (m_pKeyboard->GetKey(DIK_D) == true)
			{
				SelectChange(1, 0);
			}
			if (m_pKeyboard->GetKey(DIK_W) == true)
			{
				SelectChange(0, -1);
			}
			if (m_pKeyboard->GetKey(DIK_S) == true)
			{
				SelectChange(0, 1);
			}
		}

		if (m_pGamePad != NULL)
		{
			for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
			{
				if (m_pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_RIGHT, nCntPlayer) == true)
				{
					CFade::SetFade(CManager::MODE_ENTRY);
				}
			}
		}
	}

	// UIの処理
	for (int nCntUI = 0; nCntUI < MAX_STAGESELECT_UI; nCntUI++)
	{
		if (m_pUI[nCntUI] != NULL)
		{
			if (nCntUI == m_nSelect)
			{
				m_pUI[nCntUI]->ColorChange(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

				// サイズを少し大きくする
				m_pUI[nCntUI]->SetSize(D3DXVECTOR2(SELECT_SIZE_X * 1.2f, SELECT_SIZE_Y * 1.2f));
			}
			else
			{
				m_pUI[nCntUI]->ColorChange(D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.4f));

				m_pUI[nCntUI]->SetSize(D3DXVECTOR2(SELECT_SIZE_X, SELECT_SIZE_Y));
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CStageSelect::Draw()
{

}

//=============================================================================
// 作成処理
//=============================================================================
CStageSelect *CStageSelect::Create()
{
	CStageSelect *pEntry = NULL;
	pEntry = new CStageSelect(PRIORITY_PLANE);		//メモリ確保
												//NULLチェック
	if (pEntry != NULL)
	{
		pEntry->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	return pEntry;
}

//=============================================================================
// 選択肢の変更処理
//=============================================================================
void CStageSelect::SelectChange(int nLine, int nRow)
{
	// 行の値を変更
	m_nLine += nLine;

	// 行の範囲制限
	if (m_nLine > 1)
	{
		m_nLine = 0;
	}
	else if (m_nLine < 0)
	{
		m_nLine = 1;
	}

	// 列の値を変更
	m_nRow += nRow;

	// 列の範囲制限
	if (m_nRow > 1)
	{
		m_nRow = 0;
	}
	else if (m_nRow < 0)
	{
		m_nRow = 1;
	}

	// 行と列の値から選択肢を決定
	m_nSelect = m_nLine + (m_nRow * 2);
}