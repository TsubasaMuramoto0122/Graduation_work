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
#include "playerice.h"
#include "billboard.h"

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
#define GAME_FILE1 "data/FILES/Stages/stage_data_gym.txt"		// �̈�كX�e�[�W�̃e�L�X�g�t�@�C��
#define GAME_FILE2 "data/FILES/Stages/stage_data_forest.txt"	// �X�X�e�[�W�̃e�L�X�g�t�@�C��
#define GAME_FILE3 "data/FILES/Stages/stage_data_cloud.txt"		// �_�X�e�[�W�̃e�L�X�g�t�@�C��
#define GAME_FILE4 "data/FILES/Stages/stage_data_sand.txt"		// �����X�e�[�W�̃e�L�X�g�t�@�C��
#define GAME_FILE5 "data/FILES/Stages/stage_data_ice.txt"		// �X�X�e�[�W�̃e�L�X�g�t�@�C��
#define BOMBS_FILE "data/FILES/Models/bombs.txt"				// ���e�̃e�L�X�g�t�@�C��
#define ICE_FILE "data/MODEL/Objects/player_iced.x"				// �v���C���[�̕X�̃��f���t�@�C��
#define PLAYER_NUM (4)											// �v���C���[�̐�

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
	m_nGamePad = 0;
	m_nSelect = 0;

	//���e�A�I�u�W�F�N�g�̓ǂݍ���
	CLoad::BombsLoad(BOMBS_FILE);
	CPlayerIce::Load(ICE_FILE);

	//�C��̓ǂݍ���
	CBattery::BatteryLoad();

	CManager::SetCountdown(true);
	CManager::SetGameClear(false);
	CManager::SetGameEnd(false);
	CManager::SetEnd(false);
	CManager::SetPause(false);

	int nCntUI;
	for (nCntUI = 0; nCntUI < 4; nCntUI++)
	{
		m_bDeath[nCntUI] = false;
	}

	//�|�[�Y���̔w�i�y�јg
	CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f));
	CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 30.0f, 0.0f), D3DXVECTOR2(270.0f, 450.0f), 14, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�|�[�YUI
	m_pUI[0] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 100.0f, 0.0f), D3DXVECTOR2(160.0f, 80.0f), 33, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pUI[1] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(200.0f, 80.0f), 34, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_pUI[2] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 100.0f, 0.0f), D3DXVECTOR2(160.0f, 80.0f), 35, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));

	// �ϐ��̃N���A
	memset(&m_pPlayer, NULL, sizeof(m_pPlayer));
	//for (int nCntPlayer = 0; nCntPlayer < PLAYER_NUM; nCntPlayer++)
//	{
//		// �G���g���[��ʂł̃v���C���[�̃G���g���[�󋵂��擾
//		bEntry[nCntPlayer] = CEntry::GetStandby(nCntPlayer);
//#ifdef _DEBUG
//		// �f�o�b�O�p�Ƀv���C���[1�͑���\�ɂ��Ă���
//		//bEntry[0] = true;
//#endif
//		// �v���C���[�𐶐�
//		m_pPlayer[nCntPlayer] = CPlayer::Create(posStart[nCntPlayer], D3DXVECTOR3(0.0f, 0.0f, 0.0f), (CPlayer::PLAYER_TYPE)nCntPlayer, bEntry[nCntPlayer], 0.04f);
//	}

	for (int nPlayer = 0; nPlayer < PLAYER_NUM; nPlayer++)
	{
		// �v���C���[�̐������Ԃ����Z�b�g	
		CPlayer::SetSurviveTime(0, nPlayer);
	}

	switch (CEntry::SelectStage())
	{
	case 0:
		CLoad::StageLoad(GAME_FILE1, &m_pPlayer[0], &m_nMaxTime, &m_nSnowMaxTime);
		break;
	case 1:
		CLoad::StageLoad(GAME_FILE2, &m_pPlayer[0], &m_nMaxTime, &m_nSnowMaxTime);
		break;
	case 2:
		CLoad::StageLoad(GAME_FILE3, &m_pPlayer[0], &m_nMaxTime, &m_nSnowMaxTime);
		break;
	case 3:
		CLoad::StageLoad(GAME_FILE4, &m_pPlayer[0], &m_nMaxTime, &m_nSnowMaxTime);
		break;
	case 4:
		CLoad::StageLoad(GAME_FILE5, &m_pPlayer[0], &m_nMaxTime, &m_nSnowMaxTime);
		break;
	default:
		CLoad::StageLoad(GAME_FILE1, &m_pPlayer[0], &m_nMaxTime, &m_nSnowMaxTime);
		break;
	}

	m_nMaxTime *= 60;
	m_nTime = m_nMaxTime;
	m_nSnowTime = m_nSnowMaxTime;

	//�ŏ���~�点��
	if (0 < m_nSnowMaxTime)
	{
		int nSnow = (20 - m_nSnowMaxTime) * 3;
		int nCntSnow;
		for (nCntSnow = 0; nCntSnow < nSnow; nCntSnow++)
		{
			StartSnow();
		}
	}

	//�^�C�}�[�֘A�B�ォ��g�A���v�}�[�N�A����
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, 44.0f), D3DXVECTOR2(170.0f, 84.0f), 14, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f - 40.0f, 50.0f), D3DXVECTOR2(75.0f, 54.0f), 23, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTimeUI[0] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 5.0f, 50.0f), D3DXVECTOR2(20.0f, 50.0f), 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTimeUI[1] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 30.0f, 50.0f), D3DXVECTOR2(20.0f, 50.0f), 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTimeUI[2] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 55.0f, 50.0f), D3DXVECTOR2(20.0f, 50.0f), 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	int nRank;
	int nNumber;
	for (nCntUI = 0; nCntUI < 3; nCntUI++)
	{
		nRank = int(pow(10, 3 - nCntUI));
		nNumber = (m_nTime / 60) % nRank / (nRank / 10);
		m_pTimeUI[nCntUI]->SetTex(nNumber, 0.1f);
	}

	//ReadyGo��UI
	CReadyUI::Create();

	m_pGamePad = CManager::GetGamepad();

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
	if (m_nSnowMaxTime > 0)
	{
		m_nSnowTime--;
		if (m_nSnowTime <= 0)
		{
			Snow();
			m_nSnowTime = m_nSnowMaxTime;
		}
	}

	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		// �S�ŏ���
		Annihilation();

		//�^�C�}�[�֘A
		TimerUI();
	}

	if (CManager::GetGameEnd() == false)
	{
		//�|�[�Y�֘A
		Pause();
	}
}

//*****************************************************************************
//�`��
//***************************************************************************** 
void CGame::Draw()
{

}

void CGame::ZTexDraw()
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
	return (m_nMaxTime / 60) - (int)fSurviveTime;
}

//�v���C���[�̐������Ԃ̃Z�[�u
void CGame::SetPlayerSurviveTime()
{
	for (int nPlayer = 0; nPlayer < PLAYER_NUM; nPlayer++)
	{
		// ���Ԑ؂�Ő����c�����v���C���[�̐������Ԃ�ݒ�
		if (m_nTime <= 0)
		{
			if (m_bDeath[nPlayer] == false)
			{
				CPlayer::SetSurviveTime(GetSurviveTime(), nPlayer);
				m_bDeath[nPlayer] = true;
			}
		}
		// ���C�t��0�ɂȂ����v���C���[�̐������Ԃ�ݒ�
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
			if (m_pGamePad->GetTrigger(CGamePad::PAD_INPUTTYPE_LSTICK_UP, m_nGamePad) == true ||
				m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP, m_nGamePad) == true)
			{
				PauseChange(-1);
			}
			if (m_pGamePad->GetTrigger(CGamePad::PAD_INPUTTYPE_LSTICK_DOWN, m_nGamePad) == true || 
				m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN, m_nGamePad) == true)
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

void CGame::Snow()
{
	D3DXVECTOR3 pos;
	pos.x = ((rand() % 201) - 100) * 5.0f;
	pos.y = 350.0f;
	pos.z = ((rand() % 201) - 100) * 5.0f;

	D3DXVECTOR3 move;
	move.x = ((rand() % 11) - 5) * 0.1f;
	move.y = ((rand() % 6) + 1) * -0.1f - 0.5f;
	move.z = ((rand() % 11) - 5) * 0.1f;

	CBillboard::Create(pos, move, D3DXVECTOR3(6.0f, 6.0f, 0.0f), 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 9999999);
}

void CGame::StartSnow()
{
	D3DXVECTOR3 pos;
	pos.x = ((rand() % 201) - 100) * 5.0f;
	pos.y = (rand() % 101) * 3.5f;
	pos.z = ((rand() % 201) - 100) * 5.0f;

	D3DXVECTOR3 move;
	move.x = ((rand() % 11) - 5) * 0.1f;
	move.y = ((rand() % 6) + 1) * -0.1f - 0.5f;
	move.z = ((rand() % 11) - 5) * 0.1f;

	CBillboard::Create(pos, move, D3DXVECTOR3(6.0f, 6.0f, 0.0f), 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 9999999);
}