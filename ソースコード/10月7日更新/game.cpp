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

//#include "field.h"
//#include "wall.h"
#include "light.h"
//#include "object.h"
#include "load.h"
#include "mesh_field.h"
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

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CGame::CGame(PRIORITY Priority) : CScene::CScene(Priority)
{

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
	//UI作成
	//CUI::Create(D3DXVECTOR3(1200.0f, 620.0f, 0.0), 25.0f, 60.0f, 1, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));	//HP
	//CUI::Create(D3DXVECTOR3(1037.5f, 620.0f, 0.0), 300.0f, 60.0f, -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));	//HPゲージ下地
	//if (CManager::GetGamepad() != NULL)
	//{
	//	CUI::Create(D3DXVECTOR3(120.0f, 550.0f, 0.0), 200.0f, 300.0f, 4, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//操作方法ゲームパッド
	//}
	//else
	//{
	//	CUI::Create(D3DXVECTOR3(120.0f, 550.0f, 0.0), 200.0f, 300.0f, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//操作方法キーボード
	//}
	//CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));
	//CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 280.0f, 400.0f, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//CLoad::Load(GAME_FILE);
	//CSound::Play(1);
	CBomb::Load(0, "data/MODEL/bomb_proto2.x");
	CBomb::Load(1, "data/MODEL/bomb_ice.x");
	CBomb::Load(2, "data/MODEL/bomb_proto.x");
	CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.2f, 0.5f, -0.6f), 0);
	CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(-0.6f, -0.3f, 0.3f), 1);
	CNormalBomb::Create(D3DXVECTOR3(-40.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CIceBomb::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CFireBomb::Create(D3DXVECTOR3(40.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CManager::SetCountdown(true);
	CManager::SetGameClear(false);
	CManager::SetGameEnd(false);
	CManager::SetEnd(false);

	//+------------------+
	//| プレイヤーの生成 |
	//+------------------+
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_1P);
	CPlayer::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_2P);

	//+--------------------------+
	//| メッシュフィールドの生成 |
	//+--------------------------+
	CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4, 4);

	CCollisionSphere::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(150.0f, 0.0f, 150.0f), 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_ATTACK, -1.0f);

	return S_OK;
}

//*****************************************************************************
// 終了
//*****************************************************************************
void CGame::Uninit()
{
	CBomb::UnLoad();
	Release();
}

//*****************************************************************************
// 更新
//***************************************************************************** 
void CGame::Update()
{
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();
	if (pKeyboard != NULL)
	{
		if (pKeyboard->GetKey(DIK_RETURN) == true)
		{
			CFade::SetFade(CManager::MODE_RESULT);
		}

		if (pKeyboard->GetKey(DIK_F1) == true)
		{
			CCollisionSphere::SetVisual(false);
		}
		else if(pKeyboard->GetKey(DIK_F2) == true)
		{
			CCollisionSphere::SetVisual(true);
		}
	}
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