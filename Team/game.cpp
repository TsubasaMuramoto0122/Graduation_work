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
#include "normalbomb.h"
#include "icebomb.h"
#include "firebomb.h"
#include "battery.h"

//#include "field.h"
//#include "wall.h"
#include "light.h"
//#include "object.h"
#include "load.h"
#include "mesh_field.h"
#include "mesh_wall.h"
#include "collision_sphere.h"

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
#define TIME (10)
#define STAGE_SIZE (600.0f)

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CGame::CGame(PRIORITY Priority) : CScene::CScene(Priority)
{
	memset(&m_pTimeUI, NULL, sizeof(m_pTimeUI));
	memset(&m_pMeshField, NULL, sizeof(m_pMeshField));
	memset(&m_pMeshWall, NULL, sizeof(m_pMeshWall));
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
	//爆弾、オブジェクトの読み込み
	CLoad::BombsLoad(BOMBS_FILE);
	CObject::Load(0, "data/MODEL/Bombs/bomb_proto2.x");

	CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.2f, 0.5f, -0.6f), 0);
	CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(-0.6f, -0.3f, 0.3f), 1);

	//CNormalBomb::Create(D3DXVECTOR3(-40.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//CIceBomb::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//CFireBomb::Create(D3DXVECTOR3(40.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	CManager::SetCountdown(true);
	CManager::SetGameClear(false);
	CManager::SetGameEnd(false);
	CManager::SetEnd(false);

	m_nTime = TIME * 60;

	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 44.0f, 0.0f), D3DXVECTOR2(160.0f, 80.0f), 14, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 40.0f, 48.0f, 0.0f), D3DXVECTOR2(75.0f, 54.0f), 23, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTimeUI[0] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 5.0f, 50.0f, 0.0f), D3DXVECTOR2(20.0f, 50.0f), 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTimeUI[1] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 30.0f, 50.0f, 0.0f), D3DXVECTOR2(20.0f, 50.0f), 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTimeUI[2] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 55.0f, 50.0f, 0.0f), D3DXVECTOR2(20.0f, 50.0f), 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	m_pTimeUI[0]->SetTex(0, 0.1f);
	m_pTimeUI[1]->SetTex(0, 0.1f);
	m_pTimeUI[2]->SetTex(0, 0.1f);

	int nRank;
	int nNumber;
	int nCntUI;
	for (nCntUI = 0; nCntUI < 3; nCntUI++)
	{
		nRank = pow(10, 3 - nCntUI);
		nNumber = (m_nTime / 60) % nRank / (nRank / 10);
		m_pTimeUI[nCntUI]->SetTex(nNumber, 0.1f);
	}

	//+------------------+
	//| プレイヤーの生成 |
	//+------------------+
	CPlayer::Create(D3DXVECTOR3(-100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_1P);
	CPlayer::Create(D3DXVECTOR3(100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_2P);
	CPlayer::Create(D3DXVECTOR3(-100.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_3P);
	CPlayer::Create(D3DXVECTOR3(100.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_4P);

	//+--------------------------+
	//| メッシュフィールドの生成 |
	//+--------------------------+
	m_pMeshField[0] = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4, 4);
	m_pMeshField[0]->SetColor(D3DCOLOR_RGBA(120, 240, 255, 255));
	m_pMeshField[1] = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(STAGE_SIZE, 0.0f, STAGE_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4, 4);
	m_pMeshField[1]->SetColor(D3DCOLOR_RGBA(255, 160, 50, 255));

	m_pMeshWall[0] = CMeshWall::Create(D3DXVECTOR3(0.0f, 0.0f, STAGE_SIZE / 2), D3DXVECTOR3(STAGE_SIZE, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 1);
	m_pMeshWall[0]->SetColor(D3DCOLOR_RGBA(255, 155, 130, 0));
	m_pMeshWall[1] = CMeshWall::Create(D3DXVECTOR3(0.0f, 0.0f, -STAGE_SIZE / 2), D3DXVECTOR3(STAGE_SIZE, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 1, 1);
	m_pMeshWall[1]->SetColor(D3DCOLOR_RGBA(255, 155, 130, 0));
	m_pMeshWall[2] = CMeshWall::Create(D3DXVECTOR3(STAGE_SIZE / 2, 0.0f, 0.0f), D3DXVECTOR3(STAGE_SIZE, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 1, 1);
	m_pMeshWall[2]->SetColor(D3DCOLOR_RGBA(255, 155, 130, 0));
	m_pMeshWall[3] = CMeshWall::Create(D3DXVECTOR3(-STAGE_SIZE / 2, 0.0f, 0.0f), D3DXVECTOR3(STAGE_SIZE, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), 1, 1);

	//+--------------------------+
	//| コリジョンスフィアの生成 |
	//+--------------------------+
	//CCollisionSphere::Create(D3DXVECTOR3(-150.0f, 0.0f, 0.0f), 150.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_EXPLOSION, -1.0f);

	//砲台生成
	CBattery::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 35);

	CSound::Play(1);
	return S_OK;
}

//*****************************************************************************
// 終了
//*****************************************************************************
void CGame::Uninit()
{
	CBomb::UnLoad();
	CObject::UnLoad();
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
	//TimerUI();
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
	pGame = new CGame(PRIORITY_ORBIT);		//メモリ確保
	//NULLチェック
	if (pGame != NULL)
	{
		pGame->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pGame;
}

//タイマー処理
void CGame::TimerUI()
{
	//制限時間減らす
	m_nTime--;
	//60フレーム経ったとき(＝1秒毎)
	if (m_nTime % 60 == 0)
	{
		int nRank;
		int nNumber;
		int nCntUI;
		for (nCntUI = 0; nCntUI < 3; nCntUI++)
		{
			nRank = pow(10, 3 - nCntUI);
			nNumber = (m_nTime / 60) % nRank / (nRank / 10);
			m_pTimeUI[nCntUI]->SetTex(nNumber, 0.1f);
		}
	}
	if (m_nTime <= 0)
	{
		CFade::SetFade(CManager::MODE_RESULTRANK);
	}
}