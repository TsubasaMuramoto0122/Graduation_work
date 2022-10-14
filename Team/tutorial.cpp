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
#include "collision_sphere.h"
#include "sound.h"
#include "fade.h"
#endif

#if 1
//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CTutorial::CTutorial(PRIORITY Priority) : CScene::CScene(Priority)
{
	// 変数のクリア
	m_pKeyboard = NULL;
	//m_pGamePad = NULL;

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
	CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.2f, 0.5f, -0.6f), 0);
	CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(-0.6f, -0.3f, 0.3f), 1);

	//+------------------+
	//| プレイヤーの生成 |
	//+------------------+
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_1P);
	CPlayer::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_2P);

	//+--------------------------+
	//| メッシュフィールドの生成 |
	//+--------------------------+
	CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4, 4);


	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CTutorial::Uninit()
{
	Release();
}

//*****************************************************************************
// 更新処理
//***************************************************************************** 
void CTutorial::Update()
{


#ifdef _DEBUG
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();

	if (pKeyboard != NULL)
	{
		if (pKeyboard->GetKey(DIK_RETURN) == true)
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
}

//*****************************************************************************
// 描画処理
//***************************************************************************** 
void CTutorial::Draw()
{

}

//*****************************************************************************
// 作成処理
//***************************************************************************** 
CTutorial *CTutorial::Create()
{
	CTutorial *pTutorial = NULL;
	pTutorial = new CTutorial(PRIORITY_ORBIT);		//メモリ確保
													//NULLチェック
	if (pTutorial != NULL)
	{
		pTutorial->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	return pTutorial;
}