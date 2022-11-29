//=============================================================================
// �v���C���[�G���g���[�Ǘ� [entry.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************** 
#include "entry.h"
#include "fade.h"
#include "keyboard.h"
#include "gamepad.h"
#include "ui.h"
#include "standbyui.h"
#include "sound.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//***************************************************************************** 
bool CEntry::m_bStandby[4] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEntry::CEntry(PRIORITY Priority) :CScene(Priority)
{
	// �ϐ��̃N���A
	m_pKeyboard = NULL;
	m_pGamePad = NULL;
	m_pStandbyUI[4] = {};
	m_bCanStart = false;
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_bStandby[nCnt] = false;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEntry::~CEntry()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEntry::Init(D3DXVECTOR3)
{
	// �ϐ��̏�����
	m_bCanStart = false;
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_bStandby[nCnt] = false;
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI�F�w�i
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI�FnP
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
	{
		CUI::Create(D3DXVECTOR2(SCREEN_WIDTH / 5.0f + (SCREEN_WIDTH / 5.0f * nCntPlayer), 300.0f), D3DXVECTOR2(130.0f, 80.0f), 8 + nCntPlayer, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}

	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();

	//CSound::Play(2);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEntry::Uninit()
{
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	if (m_pGamePad != NULL)
	{
		m_pGamePad = NULL;
	}
	for (int nCntUI = 0; nCntUI < 4; nCntUI++)
	{
		if (m_pStandbyUI[nCntUI] != NULL)
		{
			//m_pStandbyUI[nCntUI]->Uninit();
			m_pStandbyUI[nCntUI] = NULL;
		}
	}

	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEntry::Update()
{
	if (m_pKeyboard != NULL)
	{
		if (m_bCanStart == true && m_pKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			CFade::SetFade(CManager::MODE_GAME);
			CSound::Play(10);
		}

		if (m_pKeyboard->GetTrigger(DIK_SPACE) == true)
		{
			DisplayOkUI(0, m_bStandby[0]);
		}
		if (m_pKeyboard->GetTrigger(DIK_B) == true)
		{
			DisplayOkUI(1, m_bStandby[1]);
		}
		if (m_pKeyboard->GetTrigger(DIK_N) == true)
		{
			DisplayOkUI(2, m_bStandby[2]);
		}
		if (m_pKeyboard->GetTrigger(DIK_M) == true)
		{
			DisplayOkUI(3, m_bStandby[3]);
		}
	}
	if (m_pGamePad != NULL)
	{
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_bCanStart == true && m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START, nCnt) == true)
			{
				CFade::SetFade(CManager::MODE_GAME);
				CSound::Play(10);
			}

			if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A, nCnt) == true)
			{
				DisplayOkUI(nCnt, m_bStandby[nCnt]);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEntry::Draw()
{

}

void CEntry::ZTexDraw()
{

}

//=============================================================================
// �쐬����
//=============================================================================
CEntry *CEntry::Create()
{
	CEntry *pEntry = NULL;
	pEntry = new CEntry(PRIORITY_PLANE);		//�������m��
												//NULL�`�F�b�N
	if (pEntry != NULL)
	{
		pEntry->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	return pEntry;
}

//=============================================================================
// UI�\������
//=============================================================================
void CEntry::DisplayOkUI(int nNum, bool bEntry)
{
	if (bEntry == false)
	{
		// UI�𐶐�
		if (m_pStandbyUI[nNum] == NULL)
		{
			m_pStandbyUI[nNum] = CStandbyUI::Create(D3DXVECTOR2(SCREEN_WIDTH / 5.0f + (SCREEN_WIDTH / 5.0f * nNum), 300.0f), D3DXVECTOR2(160.0f, 90.0f));
		}
	}
	else
	{
		// UI������
		if (m_pStandbyUI[nNum] != NULL)
		{
			m_pStandbyUI[nNum]->Uninit();
			m_pStandbyUI[nNum] = NULL;
		}
	}

	// false�܂���true�����݂Ƃ͋t�̏�Ԃɂ���
	m_bStandby[nNum] = !m_bStandby[nNum];

	int nCntStart = 0;
	for (int nCntUI = 0; nCntUI < 4; nCntUI++)
	{
		if (m_pStandbyUI[nNum] != NULL)
		{
			m_bCanStart = true;
			nCntStart++;
		}
	}

	if (nCntStart == 0)
	{
		m_bCanStart = false;
	}
}

//=============================================================================
// �ҋ@�擾����
//=============================================================================
bool CEntry::GetStandby(int nNum)
{
	return m_bStandby[nNum];
}