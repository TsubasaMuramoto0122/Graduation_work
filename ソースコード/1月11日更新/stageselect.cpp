//=============================================================================
// �v���C���[�G���g���[�Ǘ� [entry.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************** 
#include "stageselect.h"
#include "fade.h"
#include "keyboard.h"
#include "gamepad.h"
#include "ui.h"
#include "sound.h"

//*****************************************************************************
// �}�N��
//*****************************************************************************
#define TOP_POS_Y	(60)
#define TOP_SIZE_X	(500)
#define TOP_SIZE_Y	(90)
#define SELECT_POS_Y	(250)
#define SELECT_SIZE_X	(300)
#define SELECT_SIZE_Y	(200)

//*****************************************************************************
//�ÓI
//*****************************************************************************
int CStageSelect::m_nSelect = 0;
int CStageSelect::m_nLine = 0;
int CStageSelect::m_nRow = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStageSelect::CStageSelect(PRIORITY Priority) :CScene(Priority)
{
	// �ϐ��̃N���A
	m_pKeyboard = NULL;
	m_pGamePad = NULL;
	for (int nCntUI = 0; nCntUI < MAX_STAGESELECT_UI; nCntUI++)
	{
		m_pUI[nCntUI] = NULL;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStageSelect::~CStageSelect()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CStageSelect::Init(D3DXVECTOR3)
{
	// �ϐ��̏�����
	m_nSelect = 0;
	m_nLine = 0;
	m_nRow = 0;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI�F�w�i
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, TOP_POS_Y), D3DXVECTOR2(TOP_SIZE_X, TOP_SIZE_Y), -1, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI�F�I����
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int nLine = 0, nRow = 0;
	for (int nCntUI = 0; nCntUI < MAX_STAGESELECT_UI; nCntUI++)
	{
		if (nCntUI % 2 == 0)
		{
			nLine = 1;

			if (nCntUI != 0)
			{
				nRow++;
			}
		}
		else
		{
			nLine = 2;
		}

		m_pUI[nCntUI] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH / 3.0f * nLine, SELECT_POS_Y + 300.0f * nRow), D3DXVECTOR2(SELECT_SIZE_X, SELECT_SIZE_Y), -1, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	}

	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CStageSelect::Uninit()
{
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	if (m_pGamePad != NULL)
	{
		m_pGamePad = NULL;
	}

	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CStageSelect::Update()
{
	// �t�F�[�h���Ă��Ȃ����̂�
	if (CFade::GetFade() == CFade::FADE_NONE)
	{
		if (m_pKeyboard != NULL)
		{
			if (m_pKeyboard->GetKey(DIK_SPACE) == true || m_pKeyboard->GetKey(DIK_RETURN) == true)
			{
				CFade::SetFade(CManager::MODE_ENTRY);
			}

			if (m_pKeyboard->GetKey(DIK_A) == true)
			{
				SelectChange(-1, 0);
			}
			if (m_pKeyboard->GetKey(DIK_D) == true)
			{
				SelectChange(1, 0);
			}
			if (m_pKeyboard->GetKey(DIK_W) == true)
			{
				SelectChange(0, -1);
			}
			if (m_pKeyboard->GetKey(DIK_S) == true)
			{
				SelectChange(0, 1);
			}
		}

		if (m_pGamePad != NULL)
		{
			for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
			{
				if (m_pGamePad->GetPress(CGamePad::PAD_INPUTTYPE_LSTICK_RIGHT, nCntPlayer) == true)
				{
					CFade::SetFade(CManager::MODE_ENTRY);
				}
			}
		}
	}

	// UI�̏���
	for (int nCntUI = 0; nCntUI < MAX_STAGESELECT_UI; nCntUI++)
	{
		if (m_pUI[nCntUI] != NULL)
		{
			if (nCntUI == m_nSelect)
			{
				m_pUI[nCntUI]->ColorChange(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

				// �T�C�Y�������傫������
				m_pUI[nCntUI]->SetSize(D3DXVECTOR2(SELECT_SIZE_X * 1.2f, SELECT_SIZE_Y * 1.2f));
			}
			else
			{
				m_pUI[nCntUI]->ColorChange(D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.4f));

				m_pUI[nCntUI]->SetSize(D3DXVECTOR2(SELECT_SIZE_X, SELECT_SIZE_Y));
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CStageSelect::Draw()
{

}

//=============================================================================
// �쐬����
//=============================================================================
CStageSelect *CStageSelect::Create()
{
	CStageSelect *pEntry = NULL;
	pEntry = new CStageSelect(PRIORITY_PLANE);		//�������m��
												//NULL�`�F�b�N
	if (pEntry != NULL)
	{
		pEntry->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	return pEntry;
}

//=============================================================================
// �I�����̕ύX����
//=============================================================================
void CStageSelect::SelectChange(int nLine, int nRow)
{
	// �s�̒l��ύX
	m_nLine += nLine;

	// �s�͈̔͐���
	if (m_nLine > 1)
	{
		m_nLine = 0;
	}
	else if (m_nLine < 0)
	{
		m_nLine = 1;
	}

	// ��̒l��ύX
	m_nRow += nRow;

	// ��͈̔͐���
	if (m_nRow > 1)
	{
		m_nRow = 0;
	}
	else if (m_nRow < 0)
	{
		m_nRow = 1;
	}

	// �s�Ɨ�̒l����I����������
	m_nSelect = m_nLine + (m_nRow * 2);
}