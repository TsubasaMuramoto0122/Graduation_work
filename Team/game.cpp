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
#include "battery.h"
#include "entry.h"

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

#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CGame::CGame(PRIORITY Priority) : CScene::CScene(Priority)
{
	memset(&m_pTimeUI, NULL, sizeof(m_pTimeUI));
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

	//�C��̓ǂݍ���
	CBattery::BatteryLoad();

	CManager::SetCountdown(true);
	CManager::SetGameClear(false);
	CManager::SetGameEnd(false);
	CManager::SetEnd(false);

	m_nTime = TIME * 60;

	//�^�C�}�[�֘A�B�ォ��g�A���v�}�[�N�A����
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

	for (nCntUI = 0; nCntUI < 4; nCntUI++)
	{
		m_bDeath[nCntUI] = false;
	}

	//�|�[�Y���̔w�i�y�јg
	CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f));
	CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 30.0f, 0.0f), D3DXVECTOR2(260.0f, 430.0f), 14, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//+------------------+
	//| �v���C���[�̐��� |
	//+------------------+
	D3DXVECTOR3 posStart[PLAYER_NUM] = { D3DXVECTOR3(-100.0f, 0.0f, 100.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f), D3DXVECTOR3(-100.0f, 0.0f, -100.0f), D3DXVECTOR3(100.0f, 0.0f, -100.0f), };
	bool bEntry[4] = { false };

	// �v���C���[�̃X�^�[�g�ʒu�������_���Őݒ�
	for (int nCntPlayer = 0; nCntPlayer < PLAYER_NUM; nCntPlayer++)
	{
		int nRandom = rand() % PLAYER_NUM;
		D3DXVECTOR3 posSave = posStart[nCntPlayer];
		posStart[nCntPlayer] = posStart[nRandom];
		posStart[nRandom] = posSave;
	}

	// �ϐ��̃N���A
	memset(&m_pPlayer, NULL, sizeof(m_pPlayer));
	for (int nCntPlayer = 0; nCntPlayer < PLAYER_NUM; nCntPlayer++)
	{
		// �G���g���[��ʂł̃v���C���[�̃G���g���[�󋵂��擾
		bEntry[nCntPlayer] = CEntry::GetStandby(nCntPlayer);
#ifdef _DEBUG
		// �f�o�b�O�p�Ƀv���C���[1�͑���\�ɂ��Ă���
		//bEntry[0] = true;
#endif
		// �v���C���[�𐶐�
		m_pPlayer[nCntPlayer] = CPlayer::Create(posStart[nCntPlayer], D3DXVECTOR3(0.0f, 0.0f, 0.0f), (CPlayer::PLAYER_TYPE)nCntPlayer, bEntry[nCntPlayer]);
	}

	//�X�e�[�W�̓ǂݍ���
	CLoad::StageLoad(GAME_FILE, &m_pPlayer[0]);

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
	pGame = new CGame(PRIORITY_PLANE);	//�������m��
	
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
		//�v���C���[�̐������Ԃ̃Z�[�u
		SetPlayerSurviveTime();

		// �S�ł����t���O���I���ɂ���
		m_bAnnihilation = true;

		//�t�B�j�b�V��UI
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
			nRank = int(pow(10, 3 - nCntUI));
			nNumber = (m_nTime / 60) % nRank / (nRank / 10);
			m_pTimeUI[nCntUI]->SetTex(nNumber, 0.1f);
		}
		if (m_nTime == 180)
		{
			CCountdownUI::Create();
		}
		//�v���C���[�̐������Ԃ̃Z�[�u
		SetPlayerSurviveTime();
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

//�v���C���[�̐������Ԃ̃Z�[�u
void CGame::SetPlayerSurviveTime()
{
	// �v���C���[�̐l������
	for (int nPlayer = 0; nPlayer < PLAYER_NUM; nPlayer++)
	{
		if (m_pPlayer[nPlayer]->GetState() == CPlayer::PLAYER_STATE_DEFEAT && m_bDeath[nPlayer] == false)
		{
			m_pPlayer[nPlayer]->SetSurviveTime(GetSurviveTime(), (int)m_pPlayer[nPlayer]->GetType());
			m_bDeath[nPlayer] = true;
		}
	}
}