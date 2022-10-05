//=============================================================================
//�Q�[���Ǘ�[Game.cpp]
// Author : �O��q��
//=============================================================================
//*****************************************************************************
//�C���N���[�h�t�@�C��
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

//#include "field.h"
//#include "wall.h"
#include "light.h"
//#include "object.h"
#include "load.h"

#include "sound.h"

#endif
//*****************************************************************************
//�ÓI
//*****************************************************************************
bool CGame::m_bCountFlag = false;
int CGame::m_SelectNum = 1;

//*****************************************************************************
//�}�N��
//*****************************************************************************
#define GAME_FILE "data/FILES/stage.txt"

#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CGame::CGame(PRIORITY Priority) : CScene::CScene(Priority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CGame::~CGame()
{

}
#endif

//*****************************************************************************
// ������
//***************************************************************************** 
HRESULT CGame::Init(D3DXVECTOR3 /*pos*/)
{
	//UI�쐬
	//CUI::Create(D3DXVECTOR3(1200.0f, 620.0f, 0.0), 25.0f, 60.0f, 1, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));	//HP
	//CUI::Create(D3DXVECTOR3(1037.5f, 620.0f, 0.0), 300.0f, 60.0f, -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));	//HP�Q�[�W���n
	//if (CManager::GetGamepad() != NULL)
	//{
	//	CUI::Create(D3DXVECTOR3(120.0f, 550.0f, 0.0), 200.0f, 300.0f, 4, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//������@�Q�[���p�b�h
	//}
	//else
	//{
	//	CUI::Create(D3DXVECTOR3(120.0f, 550.0f, 0.0), 200.0f, 300.0f, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//������@�L�[�{�[�h
	//}
	//CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));
	//CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 280.0f, 400.0f, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//CLoad::Load(GAME_FILE);
	//CSound::Play(1);
	CBomb::Load(0, "data/MODEL/bomb_proto2.x");
	CBomb::Load(1, "data/MODEL/bomb_ice.x");
	CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.2f, 0.5f, -0.6f), 0);
	CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(-0.6f, -0.3f, 0.3f), 1);
	CNormalBomb::Create(D3DXVECTOR3(-40.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CNormalBomb::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CIceBomb::Create(D3DXVECTOR3(40.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CManager::SetCountdown(true);
	CManager::SetGameClear(false);
	CManager::SetGameEnd(false);
	CManager::SetEnd(false);

	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	return S_OK;
}

//*****************************************************************************
// �I��
//*****************************************************************************
void CGame::Uninit()
{
	//CBomb::UnLoad();
	Release();
}

//*****************************************************************************
// �X�V
//***************************************************************************** 
void CGame::Update()
{
	CKeyboard *pKeyboard;
	pKeyboard = CManager::GetKeyboard();
	if (pKeyboard != NULL)
	{
		if (pKeyboard->GetAnyKey() == true)
		{
			CFade::SetFade(CManager::MODE_RESULT);
		}
	}
}

//*****************************************************************************
//�`��
//***************************************************************************** 
void CGame::Draw()
{

}

//*****************************************************************************
//�쐬
//***************************************************************************** 
CGame *CGame::Create()
{
	CGame *pGame = NULL;
	pGame = new CGame(PRIORITY_ORBIT);		//�������m��
											//NULL�`�F�b�N
	if (pGame != NULL)
	{
		pGame->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pGame;
}