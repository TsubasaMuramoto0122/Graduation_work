//=============================================================================
// �`���[�g���A���Ǘ� [tutorial.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
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
// �}�N����`
//*****************************************************************************
#define GAME_FILE "data/FILES/Stages/stage_data_Tutorial.txt"	// �X�e�[�W�̃e�L�X�g�t�@�C��
#define BOMBS_FILE "data/FILES/Models/bombs.txt"				// ���e�̃e�L�X�g�t�@�C��
#define ICE_FILE "data/MODEL/Objects/player_iced.x"				// �v���C���[�̕X�̃��f���t�@�C��
#define PLAYER_NUM (4)											// �v���C���[�̐�

#if 1
//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CTutorial::CTutorial(PRIORITY Priority) : CScene::CScene(Priority)
{
	// �ϐ��̃N���A
	m_pKeyboard = NULL;

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CTutorial::~CTutorial()
{

}
#endif

//*****************************************************************************
// ����������
//***************************************************************************** 
HRESULT CTutorial::Init(D3DXVECTOR3 /*pos*/)
{
	// �ϐ��̏�����

	//���e�A�I�u�W�F�N�g�̓ǂݍ���
	CLoad::BombsLoad(BOMBS_FILE);
	CPlayerIce::Load(ICE_FILE);

	//�C��̓ǂݍ���
	CBattery::BatteryLoad();

	CManager::SetCountdown(false);
	CManager::SetGameClear(false);
	CManager::SetGameEnd(false);
	CManager::SetEnd(false);
	CManager::SetPause(false);

	// �ϐ��̃N���A
	memset(&m_pPlayer, NULL, sizeof(m_pPlayer));

	//�X�e�[�W�̓ǂݍ���
	CLoad::TutorialStageLoad(GAME_FILE, &m_pPlayer[0]);

	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, 645.0f), D3DXVECTOR2(SCREEN_WIDTH, 150.0f), 55, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_pGamePad = CManager::GetGamepad();
	return S_OK;
}

//*****************************************************************************
// �I������
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
// �X�V����
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
// �`�揈��
//***************************************************************************** 
void CTutorial::Draw()
{

}

void CTutorial::ZTexDraw()
{

}

//*****************************************************************************
// �쐬����
//*****************************************************************************
CTutorial *CTutorial::Create()
{
	CTutorial *pTutorial = NULL;
	pTutorial = new CTutorial(PRIORITY_PLANE);		//�������m��
	//NULL�`�F�b�N
	if (pTutorial != NULL)
	{
		pTutorial->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	return pTutorial;
}