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
#define BOMBS_FILE "data/FILES/bombs.txt"
#define PLAYER_NUM (4)
#define TIME (100)
#define STAGE_SIZE (600.0f)

#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CGame::CGame(PRIORITY Priority) : CScene::CScene(Priority)
{
	memset(&m_pTimeUI, NULL, sizeof(m_pTimeUI));
	memset(&m_pMeshField, NULL, sizeof(m_pMeshField));
	memset(&m_pMeshWall, NULL, sizeof(m_pMeshWall));
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
	// �ϐ��̏�����
	m_nDefeatNum = 0;
	m_bAnnihilation = false;

	//���e�A�I�u�W�F�N�g�̓ǂݍ���
	CLoad::BombsLoad(BOMBS_FILE);
	//CObject::Load(0, "data/MODEL/Bombs/bomb_proto2.x");

	//�X�e�[�W�̓ǂݍ���
	CLoad::Load(GAME_FILE);

	/*CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.2f, 0.5f, -0.6f), 0);
	CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(-0.6f, -0.3f, 0.3f), 1);*/

	CManager::SetCountdown(true);
	CManager::SetGameClear(false);
	CManager::SetGameEnd(false);
	CManager::SetEnd(false);

	m_nTime = TIME * 60;

	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 50.0f, 0.0f), D3DXVECTOR2(150.0f, 65.0f), 14, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 40.0f, 50.0f, 0.0f), D3DXVECTOR2(75.0f, 54.0f), 23, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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

	//�|�[�Y���̔w�i�y�јg
	CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f));
	CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(300.0f, 460.0f), 14, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	//+------------------+
	//| �v���C���[�̐��� |
	//+------------------+
	// �ϐ��̃N���A
	memset(&m_pPlayer, NULL, sizeof(m_pPlayer));
	m_pPlayer[0] = CPlayer::Create(D3DXVECTOR3(-100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_1P);
	m_pPlayer[1] = CPlayer::Create(D3DXVECTOR3(100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_2P);
	m_pPlayer[2] = CPlayer::Create(D3DXVECTOR3(-100.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_3P);
	m_pPlayer[3] = CPlayer::Create(D3DXVECTOR3(100.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CPlayer::PLAYER_TYPE_4P);

	//+--------------------------+
	//| ���b�V���t�B�[���h�̐��� |
	//+--------------------------+
	//m_pMeshField[0] = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4, 4);
	//m_pMeshField[0]->SetColor(D3DCOLOR_RGBA(120, 240, 255, 255));
	//m_pMeshField[1] = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(STAGE_SIZE, 0.0f, STAGE_SIZE), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4, 4);
	//m_pMeshField[1]->SetColor(D3DCOLOR_RGBA(255, 160, 50, 255));

	//m_pMeshWall[0] = CMeshWall::Create(D3DXVECTOR3(0.0f, 0.0f, STAGE_SIZE / 2), D3DXVECTOR3(STAGE_SIZE, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 1);
	//m_pMeshWall[0]->SetColor(D3DCOLOR_RGBA(255, 155, 130, 0));
	//m_pMeshWall[1] = CMeshWall::Create(D3DXVECTOR3(0.0f, 0.0f, -STAGE_SIZE / 2), D3DXVECTOR3(STAGE_SIZE, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 1, 1);
	//m_pMeshWall[1]->SetColor(D3DCOLOR_RGBA(255, 155, 130, 0));
	//m_pMeshWall[2] = CMeshWall::Create(D3DXVECTOR3(STAGE_SIZE / 2, 0.0f, 0.0f), D3DXVECTOR3(STAGE_SIZE, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 1, 1);
	//m_pMeshWall[2]->SetColor(D3DCOLOR_RGBA(255, 155, 130, 0));
	//m_pMeshWall[3] = CMeshWall::Create(D3DXVECTOR3(-STAGE_SIZE / 2, 0.0f, 0.0f), D3DXVECTOR3(STAGE_SIZE, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), 1, 1);
	//m_pMeshWall[3]->SetColor(D3DCOLOR_RGBA(255, 155, 130, 0));

	//�C�䐶��
	//CBattery::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 35);

	//��
	//CSound::Play(1);

	//ReadyGo��UI
	CReadyUI::Create();

	return S_OK;
}

//*****************************************************************************
// �I��
//*****************************************************************************
void CGame::Uninit()
{
	CBomb::UnLoad();
	CObject::UnLoad();
	Release();
}

//*****************************************************************************
// �X�V
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
		// �S�ŏ���
		Annihilation();

		//�^�C�}�[�֘A
		TimerUI();
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

// �S�ŏ���
void CGame::Annihilation()
{
	m_nDefeatNum = 0;

	// �v���C���[�̐l������
	for (int nPlayer = 0; nPlayer < PLAYER_NUM; nPlayer++)
	{
		// �v���C���[������Ă�����
		if (m_pPlayer[nPlayer]->GetState() == CPlayer::PLAYER_STATE_DEFEAT)
		{
			// �J�E���g�����Z
			m_nDefeatNum++;
		}
	}

	// 4�l�S�������ꂽ��
	if (m_nDefeatNum >= PLAYER_NUM)
	{
		// �S�ł����t���O���I���ɂ���
		m_bAnnihilation = true;

		CFinish::Create();
	}
}

//�^�C�}�[����
void CGame::TimerUI()
{
	// �S�ł��ĂȂ�������
	if (m_bAnnihilation == false)
	{
		//�������Ԍ��炷
		m_nTime--;
	}
	//60�t���[���o�����Ƃ�(��1�b��)
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
		if (m_nTime == 180)
		{
			CCountdownUI::Create();
		}
	}
}

int CGame::GetSurviveTime(void)
{
	// ���݂̎��Ԃ��擾������A�����_�ȉ���؂�グ��
	float fSurviveTime = (float)m_nTime / 60;
	fSurviveTime = (float)(ceil(fSurviveTime));

	// <�������� - ��������>��Ԃ�
	return TIME - (int)fSurviveTime;
}