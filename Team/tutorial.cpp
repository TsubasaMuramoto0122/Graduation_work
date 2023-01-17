//=============================================================================
// チュートリアル管理 [tutorial.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#if 1
#include "tutorial.h"
#include "player.h"
#include "ui.h"
#include "keyboard.h"
#include "gamepad.h"
#include "sky.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "battery.h"
#include "light.h"
#include "load.h"
#include "mesh_field.h"
#include "mesh_wall.h"
#include "collision_sphere.h"
#include "sound.h"
#include "fade.h"
#include "playerice.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAME_FILE "data/FILES/Stages/stage_data_Tutorial.txt"	// ステージのテキストファイル
#define BOMBS_FILE "data/FILES/Models/bombs.txt"				// 爆弾のテキストファイル
#define ICE_FILE "data/MODEL/Objects/player_iced.x"				// プレイヤーの氷のモデルファイル
#define PLAYER_NUM (4)											// プレイヤーの数

#if 1
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CTutorial::CTutorial(PRIORITY Priority) : CScene::CScene(Priority)
{
	// 変数のクリア
	m_pKeyboard = NULL;

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CTutorial::~CTutorial()
{

}
#endif

//*****************************************************************************
// 初期化処理
//***************************************************************************** 
HRESULT CTutorial::Init(D3DXVECTOR3 /*pos*/)
{
	// 変数の初期化

	//爆弾、オブジェクトの読み込み
	CLoad::BombsLoad(BOMBS_FILE);
	CPlayerIce::Load(ICE_FILE);

	//砲台の読み込み
	CBattery::BatteryLoad();

	CManager::SetCountdown(false);
	CManager::SetGameClear(false);
	CManager::SetGameEnd(false);
	CManager::SetEnd(false);
	CManager::SetPause(false);

	// 変数のクリア
	memset(&m_pPlayer, NULL, sizeof(m_pPlayer));

	//ステージの読み込み
	CLoad::TutorialStageLoad(GAME_FILE, &m_pPlayer[0]);

	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, 645.0f), D3DXVECTOR2(SCREEN_WIDTH, 150.0f), 55, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pGamePad = CManager::GetGamepad();
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CTutorial::Uninit()
{
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
// 更新処理
//***************************************************************************** 
void CTutorial::Update()
{
#ifdef _DEBUG
	if (m_pKeyboard != NULL)
	{
		if (m_pKeyboard->GetKey(DIK_RETURN) == true)
		{
			CFade::SetFade(CManager::MODE_TITLE);
		}
		if (m_pKeyboard->GetKey(DIK_F1) == true)
		{
			CCollisionSphere::SetVisual(false);
		}
		else if (m_pKeyboard->GetKey(DIK_F2) == true)
		{
			CCollisionSphere::SetVisual(true);
		}
	}
#endif
	if (m_pGamePad != NULL)
	{
		if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START, 0) == true)
		{
			CFade::SetFade(CManager::MODE_TITLE);
		}
	}
}

//*****************************************************************************
// 描画処理
//***************************************************************************** 
void CTutorial::Draw()
{

}

void CTutorial::ZTexDraw()
{

}

//*****************************************************************************
// 作成処理
//*****************************************************************************
CTutorial *CTutorial::Create()
{
	CTutorial *pTutorial = NULL;
	pTutorial = new CTutorial(PRIORITY_PLANE);		//メモリ確保
	//NULLチェック
	if (pTutorial != NULL)
	{
		pTutorial->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	return pTutorial;
}