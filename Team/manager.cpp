//=============================================================================
//
// �}�l�[�W�� [manager.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

#include "keyboard.h"
#include "gamepad.h"
#include "plane.h"

#include "title.h"
#include "game.h"
#include "resultrank.h"
#include "resultselect.h"
#include "tutorial.h"
#include "entry.h"

//�ÓI�����o�ϐ�
CRenderer *CManager::m_pRenderer = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CMouse *CManager::m_pMouse = NULL;
CGamePad *CManager::m_pGamepad = NULL;

CManager::MODE CManager::m_aMode = CManager::MODE_TITLE;

CTitle *CManager::m_pTitle = NULL;
CGame *CManager::m_pGame = NULL;
CResultSelect *CManager::m_pResultSelect = NULL;
CResultRank *CManager::m_pResultRank = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CEntry *CManager::m_pEntry = NULL;
//CTutorial *CManager::m_pTutorial = NULL;
//CGameOver *CManager::m_pGameOver = NULL;

int CManager::m_nTime = 0;
bool CManager::m_bGameEnd = false;
bool CManager::m_bGameClear = false;
bool CManager::m_bPause = false;
bool CManager::m_bCountdown = false;
bool CManager::m_bEnd = false;

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CManager::CManager()
{

}

//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CManager::~CManager()
{

}

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	m_pKeyboard = new CKeyboard;
	m_pKeyboard->Init(hInstance, hWnd);
	m_pGamepad = new CGamePad;
	m_pGamepad->Init(hInstance, hWnd);
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//�e�N�X�`���ǂݍ���	
	CScene2D::CreateTexture();
	CPlane::CreateTextureFiled();

	SetMode(m_aMode);

	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CManager::Uninit()
{
	CScene2D::UninitTexture();
	CPlane::UninitTexture();

	CScene::ReleaseAll();
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Uninit();
		delete m_pGamepad;
		m_pGamepad = NULL;
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pTitle != NULL)
	{
		m_pTitle = NULL;
	}
	if (m_pGame != NULL)
	{
		m_pGame = NULL;
	}
	/*if (m_pGameOver != NULL)
	{
	m_pGameOver = NULL;
	}*/
	if (m_pResultRank != NULL)
	{
		m_pResultRank = NULL;
	}
	if (m_pResultSelect != NULL)
	{
		m_pResultSelect = NULL;
	}
	if (m_pTutorial != NULL)
	{
		m_pTutorial = NULL;
	}
	if (m_pEntry != NULL)
	{
		m_pEntry = NULL;
	}
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CManager::Update()
{
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Update();
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

//*****************************************************************************
//�`��
//*****************************************************************************
void CManager::Draw()
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
//	�����_���[�擾
//=============================================================================
CRenderer *CManager::GetRenderer()
{
	return m_pRenderer;
}

//=============================================================================
//	�L�[�{�[�h�擾
//=============================================================================
CKeyboard *CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//=============================================================================
//	�Q�[���p�b�h�擾
//=============================================================================
CGamePad *CManager::GetGamepad()
{
	return m_pGamepad;
}

//=============================================================================
//	�}�E�X�擾
//=============================================================================
CMouse *CManager::GetMouse()
{
	return m_pMouse;
}

//=============================================================================
//���[�h�Z�b�g
//=============================================================================
void CManager::SetMode(CManager::MODE mode)
{
	CScene::ReleaseAll();
	switch (m_aMode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle = NULL;
		}
		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame = NULL;
		}
		break;

	case MODE_RESULTRANK:
		if (m_pResultRank != NULL)
		{
			m_pResultRank = NULL;
		}
		break;

	case MODE_RESULTSELECT:
		if (m_pResultSelect != NULL)
		{
			m_pResultSelect = NULL;
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial = NULL;
		}
		break;

	case MODE_ENTRY:
		if (m_pEntry != NULL)
		{
			m_pEntry = NULL;
		}
		break;

	default:
		break;
	}
	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create();
		break;

	case MODE_GAME:
		m_pGame = CGame::Create();
		break;

	case MODE_RESULTRANK:
		m_pResultRank = CResultRank::Create();
		break;

	case MODE_RESULTSELECT:
		m_pResultSelect = CResultSelect::Create();
		break;

	case MODE_TUTORIAL:
		m_pTutorial = CTutorial::Create();
		break;

	case MODE_ENTRY:
		m_pEntry = CEntry::Create();
		break;

	default:
		break;
	}
	SetPause(false);
	m_aMode = mode;
}