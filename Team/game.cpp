//=============================================================================
//ゲーム管理[Game.cpp]
// Author : 三上航世
//=============================================================================
//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#if 1
#include "game.h"
//#include "pauseui.h"
#include "player.h"
#include "ui.h"
#include "keyboard.h"
#include "gamepad.h"
#include "sky.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "bomb.h"
#include "object.h"
#include "pauseui.h"

#include "light.h"
#include "load.h"
#include "mesh_field.h"
#include "mesh_wall.h"
#include "collision_sphere.h"
#include "countdownUI.h"
#include "readyui.h"
#include "finish.h"
#include "battery.h"
#include "entry.h"

#include "sound.h"

#endif
//*****************************************************************************
//静的
//*****************************************************************************
bool CGame::m_bCountFlag = false;
int CGame::m_SelectNum = 1;

//*****************************************************************************
//マクロ
//*****************************************************************************
#define GAME_FILE "data/FILES/stage.txt"
#define BOMBS_FILE "data/FILES/bombs.txt"
#define PLAYER_NUM (4)
#define TIME (100)

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CGame::CGame(PRIORITY Priority) : CScene::CScene(Priority)
{
	memset(&m_pTimeUI, NULL, sizeof(m_pTimeUI));
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CGame::~CGame()
{

}
#endif

//*****************************************************************************
// 初期化
//***************************************************************************** 
HRESULT CGame::Init(D3DXVECTOR3 /*pos*/)
{
	// 変数の初期化
	m_nDefeatNum = 0;
	m_bAnnihilation = false;
	m_nGamePad = 0;
	m_nSelect = 0;

	//爆弾、オブジェクトの読み込み
	CLoad::BombsLoad(BOMBS_FILE);

	//砲台の読み込み
	CBattery::BatteryLoad();

	CManager::SetCountdown(true);
	CManager::SetGameClear(false);
	CManager::SetGameEnd(false);
	CManager::SetEnd(false);

	m_nTime = TIME * 60;

	//タイマー関連。上から枠、時計マーク、数字
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, 44.0f), D3DXVECTOR2(170.0f, 84.0f), 14, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f - 40.0f, 50.0f), D3DXVECTOR2(75.0f, 54.0f), 23, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTimeUI[0] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 5.0f, 50.0f), D3DXVECTOR2(20.0f, 50.0f), 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTimeUI[1] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 30.0f, 50.0f), D3DXVECTOR2(20.0f, 50.0f), 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTimeUI[2] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 55.0f, 50.0f), D3DXVECTOR2(20.0f, 50.0f), 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	/*m_pTimeUI[0]->SetTex(0, 0.1f);
	m_pTimeUI[1]->SetTex(0, 0.1f);
	m_pTimeUI[2]->SetTex(0, 0.1f);*/

	int nRank;
	int nNumber;
	int nCntUI;
	for (nCntUI = 0; nCntUI < 3; nCntUI++)
	{
		nRank = int(pow(10, 3 - nCntUI));
		nNumber = (m_nTime / 60) % nRank / (nRank / 10);
		m_pTimeUI[nCntUI]->SetTex(nNumber, 0.1f);
	}

	m_pUI[0] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 100.0f, 0.0f), D3DXVECTOR2(160.0f, 80.0f), 33, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pUI[1] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f			, 0.0f), D3DXVECTOR2(200.0f, 80.0f), 34, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_pUI[2] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 100.0f, 0.0f), D3DXVECTOR2(160.0f, 80.0f), 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));

	for (nCntUI = 0; nCntUI < 4; nCntUI++)
	{
		m_bDeath[nCntUI] = false;
	}

	//ポーズ時の背景及び枠
	CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f));
	CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 30.0f, 0.0f), D3DXVECTOR2(260.0f, 430.0f), 14, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//+------------------+
	//| プレイヤーの生成 |
	//+------------------+
	D3DXVECTOR3 posStart[PLAYER_NUM] = { D3DXVECTOR3(-100.0f, 0.0f, 100.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f), D3DXVECTOR3(-100.0f, 0.0f, -100.0f), D3DXVECTOR3(100.0f, 0.0f, -100.0f), };
	bool bEntry[4] = { false };

	// プレイヤーのスタート位置をランダムで設定
	for (int nCntPlayer = 0; nCntPlayer < PLAYER_NUM; nCntPlayer++)
	{
		int nRandom = rand() % PLAYER_NUM;
		D3DXVECTOR3 posSave = posStart[nCntPlayer];
		posStart[nCntPlayer] = posStart[nRandom];
		posStart[nRandom] = posSave;
	}

	// 変数のクリア
	memset(&m_pPlayer, NULL, sizeof(m_pPlayer));
	for (int nCntPlayer = 0; nCntPlayer < PLAYER_NUM; nCntPlayer++)
	{
		// エントリー画面でのプレイヤーのエントリー状況を取得
		bEntry[nCntPlayer] = CEntry::GetStandby(nCntPlayer);
#ifdef _DEBUG
		// デバッグ用にプレイヤー1は操作可能にしておく
		bEntry[0] = true;
#endif
		// プレイヤーを生成
		m_pPlayer[nCntPlayer] = CPlayer::Create(posStart[nCntPlayer], D3DXVECTOR3(0.0f, 0.0f, 0.0f), (CPlayer::PLAYER_TYPE)nCntPlayer, bEntry[nCntPlayer]);
	}

	for (int nPlayer = 0; nPlayer < PLAYER_NUM; nPlayer++)
	{
		// プレイヤーの生存時間をリセット	
		CPlayer::SetSurviveTime(0, nPlayer);
	}

	//ステージの読み込み
	CLoad::StageLoad(GAME_FILE, &m_pPlayer[0]);

	//ReadyGoのUI
	CReadyUI::Create();

	m_pGamePad = CManager::GetGamepad();

	return S_OK;
}

//*****************************************************************************
// 終了
//*****************************************************************************
void CGame::Uninit()
{
	CBomb::UnLoad();
	CObject::UnLoad();
	CBattery::BatteryUnLoad();

	int nCnt;
	for (nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_pTimeUI[nCnt] != NULL)
		{
			m_pTimeUI[nCnt] = NULL;
		}
	}

	for (nCnt = 0; nCnt < PLAYER_NUM; nCnt++)
	{
		if (m_pPlayer[nCnt] != NULL)
		{
			m_pPlayer[nCnt] = NULL;
		}
	}

	Release();
}

//*****************************************************************************
// 更新
//***************************************************************************** 
void CGame::Update()
{
#ifdef _DEBUG
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();
	if (pKeyboard != NULL)
	{
		if (pKeyboard->GetKey(DIK_RETURN) == true)
		{
			CFade::SetFade(CManager::MODE_RESULTRANK);
		}
		if (pKeyboard->GetKey(DIK_F3) == true)
		{
			CFade::SetFade(CManager::MODE_GAME);
		}
		if (pKeyboard->GetKey(DIK_F1) == true)
		{
			CCollisionSphere::SetVisual(false);
		}
		else if (pKeyboard->GetKey(DIK_F2) == true)
		{
			CCollisionSphere::SetVisual(true);
		}
	}
#endif

	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		// 全滅処理
		Annihilation();

		//タイマー関連
		TimerUI();
	}

	//ポーズ関連
	Pause();
}

//*****************************************************************************
//描画
//***************************************************************************** 
void CGame::Draw()
{

}

//*****************************************************************************
//作成
//***************************************************************************** 
CGame *CGame::Create()
{
	CGame *pGame = NULL;
	pGame = new CGame(PRIORITY_PLANE);	//メモリ確保
	
	//NULLチェック
	if (pGame != NULL)
	{
		pGame->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pGame;
}

// 全滅処理
void CGame::Annihilation()
{
	m_nDefeatNum = 0;

	// プレイヤーの人数分回す
	for (int nPlayer = 0; nPlayer < PLAYER_NUM; nPlayer++)
	{
		// プレイヤーがやられていたら
		if (m_pPlayer[nPlayer]->GetState() == CPlayer::PLAYER_STATE_DEFEAT)
		{
			// カウントを加算
			m_nDefeatNum++;
		}
	}

	// 4人全員がやられたら
	if (m_nDefeatNum >= PLAYER_NUM)
	{
		//プレイヤーの生存時間のセーブ
		SetPlayerSurviveTime();

		// 全滅したフラグをオンにする
		m_bAnnihilation = true;

		//フィニッシュUI
		CFinish::Create();
	}
}

//タイマー処理
void CGame::TimerUI()
{
	// 全滅してなかったら
	if (m_bAnnihilation == false)
	{
		//制限時間減らす
		m_nTime--;
	}
	//60フレーム経ったとき(＝1秒毎)
	if (m_nTime % 60 == 0)
	{
		int nRank;
		int nNumber;
		int nCntUI;
		for (nCntUI = 0; nCntUI < 3; nCntUI++)
		{
			nRank = int(pow(10, 3 - nCntUI));
			nNumber = (m_nTime / 60) % nRank / (nRank / 10);
			m_pTimeUI[nCntUI]->SetTex(nNumber, 0.1f);
		}
		if (m_nTime == 180)
		{
			CCountdownUI::Create();
		}
		//プレイヤーの生存時間のセーブ
		SetPlayerSurviveTime();
	}
}

int CGame::GetSurviveTime(void)
{
	// 現在の時間を取得した後、小数点以下を切り上げる
	float fSurviveTime = (float)m_nTime / 60;
	fSurviveTime = (float)(ceil(fSurviveTime));

	// <制限時間 - 生存時間>を返す
	return TIME - (int)fSurviveTime;
}

//プレイヤーの生存時間のセーブ
void CGame::SetPlayerSurviveTime()
{
	for (int nPlayer = 0; nPlayer < PLAYER_NUM; nPlayer++)
	{
		// 時間切れで生き残ったプレイヤーの生存時間を設定
		if (m_nTime <= 0)
		{
			if (m_bDeath[nPlayer] == false)
			{
				CPlayer::SetSurviveTime(GetSurviveTime(), nPlayer);
				m_bDeath[nPlayer] = true;
			}
		}
		// ライフが0になったプレイヤーの生存時間を設定
		else
		{
			if (m_pPlayer[nPlayer]->GetState() == CPlayer::PLAYER_STATE_DEFEAT && m_bDeath[nPlayer] == false)
			{
				CPlayer::SetSurviveTime(GetSurviveTime(), nPlayer);
				m_bDeath[nPlayer] = true;
			}
		}
	}
}

void CGame::Pause()
{
	if (CManager::GetPause() == false)
	{
		if (m_pGamePad != NULL)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START, nCnt) == true)
				{
					m_nGamePad = nCnt;
					CManager::SetPause(true);
					CSound::Play(15);
					break;
				}
			}
		}
	}
	else
	{
		if (m_pGamePad != NULL)
		{
			if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START, m_nGamePad) == true)
			{
				CManager::SetPause(false);
				CSound::Play(15);
			}
			if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_B, m_nGamePad) == true)
			{
				PauseSelect();
			}
			if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP, m_nGamePad) == true)
			{
				PauseChange(-1);
			}
			if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN, m_nGamePad) == true)
			{
				PauseChange(1);
			}
		}
	}
}

void CGame::PauseChange(int nAdd)
{
	m_pUI[m_nSelect]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_nSelect += nAdd;
	if (m_nSelect < 0)
	{
		m_nSelect = 2;
	}
	else if (2 < m_nSelect)
	{
		m_nSelect = 0;
	}
	m_pUI[m_nSelect]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CSound::Play(12);
}

void CGame::PauseSelect()
{
	switch (m_nSelect)
	{
	case 0:
		CManager::SetPause(false);
		break;
	case 1:
		CFade::SetFade(CManager::MODE_GAME);
		break;
	case 2:
		CFade::SetFade(CManager::MODE_TITLE);
	default:
		break;
	}
	CSound::Play(13);
}