//=============================================================================
//
// リザルトランキング処理 [resultrank.cpp]
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
#include "player.h"

#include "sound.h"
#endif
//*****************************************************************************
// 静的メンバ変数
//***************************************************************************** 

//*****************************************************************************
//マクロ
//*****************************************************************************
#define MAX_FADE_TIME (60)
#define MAX_PLAYER_NUM (4)
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
	m_pGamePad = CManager::GetGamepad();

	m_nTime = 0;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI：(上から)背景、枠、文字
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 60, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, 430.0f), D3DXVECTOR2(800.0f, 530.0f), 36, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, 80.0f), D3DXVECTOR2(500.0f, 100.0f), 18, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// プレイヤーの番号、生存時間、王冠の数、プレイヤーの順位
	int  nPlayerNum[MAX_PLAYER_NUM], nSurviveTime[MAX_PLAYER_NUM], nCrown = 1, nPlayerRank = 0;

	// それぞれのプレイヤーの番号の設定と、生存時間を取得
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_NUM; nCntPlayer++)
	{
		nPlayerNum[nCntPlayer] = nCntPlayer;
		nSurviveTime[nCntPlayer] = CPlayer::GetSurviveTime(nCntPlayer);
	}

	//-------------------------------------------------------
	// バブルソート
	//-------------------------------------------------------
	for (int nCnt = 0; nCnt < MAX_PLAYER_NUM; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 < MAX_PLAYER_NUM - 1; nCnt2++)
		{
			// 生存時間とプレイヤーの番号を降順に並べ替える
			if (nSurviveTime[nCnt2 + 1] > nSurviveTime[nCnt2])
			{
				int nSort = nSurviveTime[nCnt2 + 1];
				int nPlayer = nPlayerNum[nCnt2 + 1];

				nSurviveTime[nCnt2 + 1] = nSurviveTime[nCnt2];
				nPlayerNum[nCnt2 + 1] = nPlayerNum[nCnt2];

				nSurviveTime[nCnt2] = nSort;
				nPlayerNum[nCnt2] = nPlayer;
			}
		}
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI：王冠
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// 生存時間の一番長いプレイヤーの人数を算出
	for (int nCntCrown = 0; nCntCrown < MAX_PLAYER_NUM - 1; nCntCrown++)
	{
		// 現在のプレイヤーの生存時間が次のプレイヤーの生存時間と同じなら
		if (nSurviveTime[nCntCrown] == nSurviveTime[nCntCrown + 1])
		{
			// 表示させる王冠の数を増やす
			nCrown++;
		}
		// 現在のプレイヤーの生存時間が次のプレイヤーの生存時間と同じじゃなかったら終了
		else
		{
			break;
		}
	}

	// 上で算出したプレイヤーの人数ぶん、王冠のUIを生成
	for (int nCntRank = 0; nCntRank < nCrown; nCntRank++)
	{
		CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f - 270.0f, 240.0f + 125.0f * nCntRank), D3DXVECTOR2(160.0f, 140.0f), 12, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI：順位
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int nCntRank = 0; nCntRank < MAX_PLAYER_NUM; nCntRank++)
	{
		// nPlayerRankの値を使用し、順位のUIを生成
		CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f - 100.0f, 240.0f + 125.0f * nCntRank), D3DXVECTOR2(160.0f, 108.0f), 4 + nPlayerRank, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		if (nCntRank < MAX_PLAYER_NUM - 1)
		{
			// 今のプレイヤーと次のプレイヤーの生存時間が同じだったら
			if (nSurviveTime[nCntRank] != nSurviveTime[nCntRank + 1])
			{
				// 順位を進ませる
				nPlayerRank++;
			}
		}
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI：nP
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_NUM; nCntPlayer++)
	{
		CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 60.0f, 240.0f + 125.0f * nCntPlayer), D3DXVECTOR2(120.0f, 90.0f), 8 + nPlayerNum[nCntPlayer], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI：生存時間
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int nCntRank = 0; nCntRank < MAX_PLAYER_NUM; nCntRank++)
	{
		for (int nCntUI = 0; nCntUI < MAX_PLAYER_NUM - 1; nCntUI++)
		{
			// 数字のテクスチャ座標の計算
			int nRank = (int)(pow(10, 3 - nCntUI));
			int nNumber = nSurviveTime[nCntRank] % nRank / (nRank / 10);

			// 数字のUIの生成
			m_pUI[nCntRank * 3 + nCntUI] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 180.0f + 60.0f * nCntUI, 240.0f + 125.0f * nCntRank), D3DXVECTOR2(54.0f, 90.0f), 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pUI[nCntRank * 3 + nCntUI]->SetTex(nNumber, 0.1f);
		}
	}

	int nCnt;
	for (nCnt = 0; nCnt < 7; nCnt++)
	{
		m_fFade[nCnt] = 0.0f;
	}

	m_bSelect = false;
	m_nSelect = 0;
	m_nFadeTime = 0;
	m_fClear = 1.0f;

	//選択肢背景
	m_pSelectUI[0] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	//選択肢
	m_pSelectUI[1] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 180.0f), D3DXVECTOR2(750.0f, 150.0f), 24, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pSelectUI[2] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 180.0f), D3DXVECTOR2(650.0f, 100.0f), 20, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pSelectUI[3] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f)			, D3DXVECTOR2(750.0f, 150.0f), 24, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pSelectUI[4] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f)			, D3DXVECTOR2(650.0f, 100.0f), 21, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pSelectUI[5] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 180.0f), D3DXVECTOR2(750.0f, 150.0f), 24, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pSelectUI[6] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 180.0f), D3DXVECTOR2(650.0f, 100.0f), 22, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	CSound::Play(3);

	return S_OK;
}

//*****************************************************************************
// 終了
//***************************************************************************** 
void CResultRank::Uninit()
{
	for (int nCnt = 0; nCnt < 12; nCnt++)
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
	if (m_pGamePad != NULL)
	{
		m_pGamePad = NULL;
	}
	Release();
}

//*****************************************************************************
// 更新
//***************************************************************************** 
void CResultRank::Update()
{
	if (m_bSelect == false)
	{
		if (90 < m_nTime)
		{
#ifdef _DEBUG
			if (m_pKeyboard != NULL)
			{
				if (m_pKeyboard->GetAnyKey() == true)
				{
					m_bSelect = true;
					m_nTime = 0;
					CSound::Play(13);
				}
			}
#endif
			if (m_pGamePad != NULL)
			{
				if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_B, 0) == true)
				{
					m_bSelect = true;
					m_nTime = 0;
					CSound::Play(13);
				}
			}
		}
		else
		{
			m_nTime++;
		}
	}
	else
	{
		if (10 <= m_nTime)
		{
#ifdef _DEBUG
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
#endif
			if (m_pGamePad != NULL)
			{
				for (int nCnt = 0; nCnt < 4; nCnt++)
				{
					//*******************************************
					// 左スティック・十字キーでステージ選択
					//*******************************************
					if (m_pGamePad->GetTrigger(CGamePad::PAD_INPUTTYPE_LSTICK_UP, nCnt) == true ||
						m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP, nCnt) == true)
					{
						SelectChange(-1);
					}
					if (m_pGamePad->GetTrigger(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, nCnt) == true ||
						m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN, nCnt) == true)
					{
						SelectChange(1);
					}
					if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_B, nCnt) == true)
					{
						Select();
					}
				}
			}
			ChooseFade();
		}
		else
		{
			m_nTime++;
			SelectFade();
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

void CResultRank::ZTexDraw()
{

}

//*****************************************************************************
//作成
//***************************************************************************** 
CResultRank *CResultRank::Create()
{
	CResultRank *pResultRank = NULL;
	pResultRank = new CResultRank(PRIORITY_PLANE);		//メモリ確保
														//NULLチェック
	if (pResultRank != NULL)
	{
		pResultRank->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pResultRank;
}
#endif

void CResultRank::SelectFade()
{
	m_fFade[0] += 0.04f;
	m_fFade[1] += 0.1f;
	m_fFade[2] += 0.1f;
	m_fFade[3] += 0.1f;
	m_fFade[4] += 0.1f;
	m_fFade[5] += 0.1f;
	m_fFade[6] += 0.1f;

	m_pSelectUI[0]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_fFade[0]));

	int nCnt;
	for (nCnt = 0; nCnt < 6; nCnt++)
	{
		m_pSelectUI[nCnt + 1]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFade[nCnt + 1]));
	}
}

void CResultRank::Select()
{
	switch (m_nSelect)
	{
	case 0:
		CFade::SetFade(CManager::MODE_GAME);
		break;
	case 1:
		CFade::SetFade(CManager::MODE_ENTRY);
		break;
	case 2:
		CFade::SetFade(CManager::MODE_TITLE);
		break;
	default:
		break;
	}
	CSound::Play(13);
}
void CResultRank::SelectChange(int nAdd)
{
	m_pSelectUI[m_nSelect * 2 + 1]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pSelectUI[m_nSelect * 2 + 2]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_nSelect += nAdd;
	if (m_nSelect < 0)
	{
		m_nSelect = MAX_SELECT - 1;
	}
	else if (MAX_SELECT <= m_nSelect)
	{
		m_nSelect = 0;
	}
	m_pSelectUI[m_nSelect * 2 + 1]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pSelectUI[m_nSelect * 2 + 2]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_nFadeTime = 0;
	m_fClear = 1.0f;
	CSound::Play(12);
}

void CResultRank::ChooseFade()
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
	m_pSelectUI[m_nSelect * 2 + 1]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fClear));
	m_pSelectUI[m_nSelect * 2 + 2]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fClear));
}