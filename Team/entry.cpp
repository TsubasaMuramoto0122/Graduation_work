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
#include "pauseui.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//***************************************************************************** 
bool CEntry::m_bStandby[4] = {};
int CEntry::m_nStage = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEntry::CEntry(PRIORITY Priority) :CScene(Priority)
{
	
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
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_bStandby[nCnt] = false;
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI�F�w�i
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 41, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI�FnP
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
	{
		D3DXVECTOR2 nPPos;
		switch (nCntPlayer)
		{
		case 0:
			nPPos = D3DXVECTOR2(90.0f, 70.0f);
			break;
		case 1:
			nPPos = D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 90.0f, 70.0f);
			break;
		case 2:
			nPPos = D3DXVECTOR2(90.0f, SCREEN_HEIGHT * 0.5f + 80.0f);
			break;
		case 3:
			nPPos = D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 90.0f, SCREEN_HEIGHT * 0.5f + 80.0f);
			break;
		default:
			break;
		}
		CUI::Create(nPPos, D3DXVECTOR2(140.0f, 100.0f), 8 + nCntPlayer, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		switch (nCntPlayer)
		{
		case 0:
			nPPos = D3DXVECTOR2(SCREEN_WIDTH * 0.25f, 300.0f);
			break;
		case 1:
			nPPos = D3DXVECTOR2(SCREEN_WIDTH * 0.75f, 300.0f);
			break;
		case 2:
			nPPos = D3DXVECTOR2(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.5f + 300.0f);
			break;
		case 3:
			nPPos = D3DXVECTOR2(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.5f + 300.0f);
			break;
		default:
			break;
		}

		m_pStandbyUI[nCntPlayer] = CStandbyUI::Create(nPPos, D3DXVECTOR2(160.0f, 70.0f));
		m_pStandbyUI[nCntPlayer]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();

	m_nTime = 0;
	m_nStage = 0;
	m_nLine[0] = 0;
	m_nLine[1] = 0;

	CManager::SetPause(true);

	//�w�i
	m_pBg = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, -SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 54, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	//�X�X�e�[�W
	m_pStage[0] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.25f, -SCREEN_HEIGHT * 0.75f), D3DXVECTOR2(500.0f, 310.0f), 36, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pStage[1] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.25f, -SCREEN_HEIGHT * (0.75f + 0.05f)), D3DXVECTOR2(280.0f, 160.0f), 46, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pStage[2] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.25f, -SCREEN_HEIGHT * (0.75f - 0.13f)), D3DXVECTOR2(300.0f, 60.0f), 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	//�X�X�e�[�W
	m_pStage[3] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.75f, -SCREEN_HEIGHT * 0.75f), D3DXVECTOR2(500.0f, 310.0f), 36, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
	m_pStage[4] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.75f, -SCREEN_HEIGHT * (0.75f + 0.05f)), D3DXVECTOR2(280.0f, 160.0f), 47, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
	m_pStage[5] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.75f, -SCREEN_HEIGHT * (0.75f - 0.13f)), D3DXVECTOR2(300.0f, 60.0f), 51, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));

	//�_�X�e�[�W
	m_pStage[6] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.25f, -SCREEN_HEIGHT * 0.25f), D3DXVECTOR2(500.0f, 310.0f), 36, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
	m_pStage[7] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.25f, -SCREEN_HEIGHT * (0.25f + 0.05f)), D3DXVECTOR2(280.0f, 160.0f), 48, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
	m_pStage[8] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.25f, -SCREEN_HEIGHT * (0.25f - 0.13f)), D3DXVECTOR2(300.0f, 60.0f), 52, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));

	//�����X�e�[�W
	m_pStage[9] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.75f, -SCREEN_HEIGHT * 0.25f), D3DXVECTOR2(500.0f, 310.0f), 36, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
	m_pStage[10] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.75f, -SCREEN_HEIGHT * (0.25f + 0.05f)), D3DXVECTOR2(280.0f, 160.0f), 49, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
	m_pStage[11] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.75f, -SCREEN_HEIGHT * (0.25f - 0.13f)), D3DXVECTOR2(300.0f, 60.0f), 53, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
	CSound::Play(2);

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
			m_pStandbyUI[nCntUI] = NULL;
		}
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEntry::Update()
{
	if (m_nTime <= 0)
	{
		//�L�����I��
		if (m_bStageSelect == false)
		{
#ifdef _DEBUG
			if (m_pKeyboard != NULL)
			{
				if (m_pKeyboard->GetKey(DIK_RETURN) == true)
				{
					if (ReadyGo() == true)
					{
						Stage();
					}
				}

				if (m_pKeyboard->GetKey(DIK_SPACE) == true)
				{
					DisplayOkUI(0, m_bStandby[0]);
				}
				if (m_pKeyboard->GetKey(DIK_B) == true)
				{
					DisplayOkUI(1, m_bStandby[1]);
				}
				if (m_pKeyboard->GetKey(DIK_N) == true)
				{
					DisplayOkUI(2, m_bStandby[2]);
				}
				if (m_pKeyboard->GetKey(DIK_M) == true)
				{
					DisplayOkUI(3, m_bStandby[3]);
				}
			}
#endif
			if (m_pGamePad != NULL)
			{
				for (int nCnt = 0; nCnt < 4; nCnt++)
				{
					if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START, nCnt) == true)
					{
						if (ReadyGo() == true)
						{
							CFade::SetFade(CManager::MODE_GAME);
							CSound::Play(10);
						}
					}

					if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A, nCnt) == true)
					{
						DisplayOkUI(nCnt, m_bStandby[nCnt]);
					}
				}
			}
		}
		else //�X�e�[�W�I��
		{
#ifdef _DEBUG
			if (m_pKeyboard != NULL)
			{
				if (m_pKeyboard->GetKey(DIK_RETURN) == true)
				{
					GameStart();
				}

				if (m_pKeyboard->GetKey(DIK_DELETE) == true)
				{
					Stage();
				}

				if (m_pKeyboard->GetKey(DIK_UP) == true)
				{
					StageChange(1, -1);
				}
				if (m_pKeyboard->GetKey(DIK_DOWN) == true)
				{
					StageChange(1, 1);
				}
				if (m_pKeyboard->GetKey(DIK_LEFT) == true)
				{
					StageChange(0, -1);
				}
				if (m_pKeyboard->GetKey(DIK_RIGHT) == true)
				{
					StageChange(0, 1);
				}
			}
#endif
			if (m_pGamePad != NULL)
			{
				for (int nCnt = 0; nCnt < 4; nCnt++)
				{
					if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_B, nCnt) == true)
					{
						GameStart();
					}

					if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A, nCnt) == true)
					{
						Stage();
					}
					if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP, nCnt) == true)
					{
						StageChange(1, -1);
					}
					if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN, nCnt) == true)
					{
						StageChange(1, 1);
					}
					if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_LEFT, nCnt) == true)
					{
						StageChange(0, -1);
					}
					if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_RIGHT, nCnt) == true)
					{
						StageChange(0, 1);
					}
				}
			}
		}
	}
	else
	{
		StageUIMove();
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
		m_pStandbyUI[nNum]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		m_pStandbyUI[nNum]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	// false�܂���true�����݂Ƃ͋t�̏�Ԃɂ���
	m_bStandby[nNum] = !m_bStandby[nNum];
}

//=============================================================================
// �N��GO�T�C�����o���Ă邩
//=============================================================================
bool CEntry::ReadyGo()
{
	for (int nCntUI = 0; nCntUI < 4; nCntUI++)
	{
		//�N��1�l�ł�GO���Ă���
		if (m_bStandby[nCntUI] == true)
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// �X�e�[�W�I��
//=============================================================================
void CEntry::Stage()
{
	m_nTime = 20;

	m_bStageSelect = !m_bStageSelect;
}

//=============================================================================
// �X�e�[�W�I��
//=============================================================================
void CEntry::StageChange(int nLine, int nAdd)
{
	int nCnt;
	for (nCnt = 0; nCnt < 3; nCnt++)
	{
		m_pStage[(m_nLine[0] + m_nLine[1] * 2) * 3 + nCnt]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
	}

	m_nLine[nLine] += nAdd;
	if (m_nLine[nLine] < 0)
	{
		m_nLine[nLine] = 1;
	}
	else if (1 < m_nLine[nLine])
	{
		m_nLine[nLine] = 0;
	}

	for (nCnt = 0; nCnt < 3; nCnt++)
	{
		m_pStage[(m_nLine[0] + m_nLine[1] * 2) * 3 + nCnt]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//=============================================================================
// �X�e�[�W�I��UI�̈ړ�
//=============================================================================
void CEntry::StageUIMove()
{
	m_nTime--;
	int nCntUI;
	D3DXVECTOR3 pos;

	pos = m_pBg->GetPos();
	if (m_bStageSelect == true)
	{
		pos.y += SCREEN_HEIGHT * 0.05f;
	}
	else
	{
		pos.y -= SCREEN_HEIGHT * 0.05f;
	}
	m_pBg->SetPos(pos);

	for (nCntUI = 0; nCntUI < 12; nCntUI++)
	{
		pos = m_pStage[nCntUI]->GetPos();
		if (m_bStageSelect == true)
		{
			pos.y += SCREEN_HEIGHT * 0.05f;
		}
		else
		{
			pos.y -= SCREEN_HEIGHT * 0.05f;
		}
		m_pStage[nCntUI]->SetPos(pos);
	}
}

//=============================================================================
// �Q�[���ɑJ��
//=============================================================================
void CEntry::GameStart()
{
	m_nStage = m_nLine[0] + m_nLine[1] * 2;
	CFade::SetFade(CManager::MODE_GAME);
	CSound::Play(10);
}