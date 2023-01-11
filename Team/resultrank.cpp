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
#define MAX_RESULT_TIME (600)

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
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
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
	m_nTime++;
	if (150 < m_nTime)
	{
#ifdef _DEBUG
		if (m_pKeyboard != NULL)
		{
			if (m_pKeyboard->GetAnyKey() == true)
			{
				CFade::SetFade(CManager::MODE_RESULTSELECT);
				CSound::Play(13);
			}
		}
#endif
		if (m_pGamePad != NULL)
		{
			if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_B, 0) == true)
			{
				CFade::SetFade(CManager::MODE_RESULTSELECT);
				CSound::Play(13);
			}
		}
	}
	if (MAX_RESULT_TIME <= m_nTime)
	{
		CFade::SetFade(CManager::MODE_RESULTSELECT);
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