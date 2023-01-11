//=============================================================================
//
// ���U���g�����L���O���� [resultrank.cpp]
// Author : �O��q��
//
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************** 
#if 1
#include "fade.h"
#include "resultrank.h"
#include "keyboard.h"
#include "gamepad.h"
#include "ui.h"
#include "player.h"

#include "sound.h"
#endif
//*****************************************************************************
// �ÓI�����o�ϐ�
//***************************************************************************** 

//*****************************************************************************
//�}�N��
//*****************************************************************************
#define MAX_FADE_TIME (60)
#define MAX_PLAYER_NUM (4)
#define MAX_RESULT_TIME (600)

#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CResultRank::CResultRank(PRIORITY Priority) :CScene(Priority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CResultRank::~CResultRank()
{

}
#endif
//*****************************************************************************
// ������
//***************************************************************************** 
HRESULT CResultRank::Init(D3DXVECTOR3 /*pos*/)
{
	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();

	m_nTime = 0;

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI�F(�ォ��)�w�i�A�g�A����
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, 430.0f), D3DXVECTOR2(800.0f, 530.0f), 36, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f, 80.0f), D3DXVECTOR2(500.0f, 100.0f), 18, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �v���C���[�̔ԍ��A�������ԁA�����̐��A�v���C���[�̏���
	int  nPlayerNum[MAX_PLAYER_NUM], nSurviveTime[MAX_PLAYER_NUM], nCrown = 1, nPlayerRank = 0;

	// ���ꂼ��̃v���C���[�̔ԍ��̐ݒ�ƁA�������Ԃ��擾
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_NUM; nCntPlayer++)
	{
		nPlayerNum[nCntPlayer] = nCntPlayer;
		nSurviveTime[nCntPlayer] = CPlayer::GetSurviveTime(nCntPlayer);
	}

	//-------------------------------------------------------
	// �o�u���\�[�g
	//-------------------------------------------------------
	for (int nCnt = 0; nCnt < MAX_PLAYER_NUM; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 < MAX_PLAYER_NUM - 1; nCnt2++)
		{
			// �������Ԃƃv���C���[�̔ԍ����~���ɕ��בւ���
			if (nSurviveTime[nCnt2 + 1] > nSurviveTime[nCnt2])
			{
				int nSort = nSurviveTime[nCnt2 + 1];
				int nPlayer = nPlayerNum[nCnt2 + 1];

				nSurviveTime[nCnt2 + 1] = nSurviveTime[nCnt2];
				nPlayerNum[nCnt2 + 1] = nPlayerNum[nCnt2];

				nSurviveTime[nCnt2] = nSort;
				nPlayerNum[nCnt2] = nPlayer;
			}
		}
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI�F����
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// �������Ԃ̈�Ԓ����v���C���[�̐l�����Z�o
	for (int nCntCrown = 0; nCntCrown < MAX_PLAYER_NUM - 1; nCntCrown++)
	{
		// ���݂̃v���C���[�̐������Ԃ����̃v���C���[�̐������ԂƓ����Ȃ�
		if (nSurviveTime[nCntCrown] == nSurviveTime[nCntCrown + 1])
		{
			// �\�������鉤���̐��𑝂₷
			nCrown++;
		}
		// ���݂̃v���C���[�̐������Ԃ����̃v���C���[�̐������ԂƓ�������Ȃ�������I��
		else
		{
			break;
		}
	}

	// ��ŎZ�o�����v���C���[�̐l���Ԃ�A������UI�𐶐�
	for (int nCntRank = 0; nCntRank < nCrown; nCntRank++)
	{
		CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f - 270.0f, 240.0f + 125.0f * nCntRank), D3DXVECTOR2(160.0f, 140.0f), 12, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI�F����
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int nCntRank = 0; nCntRank < MAX_PLAYER_NUM; nCntRank++)
	{
		// nPlayerRank�̒l���g�p���A���ʂ�UI�𐶐�
		CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f - 100.0f, 240.0f + 125.0f * nCntRank), D3DXVECTOR2(160.0f, 108.0f), 4 + nPlayerRank, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		if (nCntRank < MAX_PLAYER_NUM - 1)
		{
			// ���̃v���C���[�Ǝ��̃v���C���[�̐������Ԃ�������������
			if (nSurviveTime[nCntRank] != nSurviveTime[nCntRank + 1])
			{
				// ���ʂ�i�܂���
				nPlayerRank++;
			}
		}
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI�FnP
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_NUM; nCntPlayer++)
	{
		CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 60.0f, 240.0f + 125.0f * nCntPlayer), D3DXVECTOR2(120.0f, 90.0f), 8 + nPlayerNum[nCntPlayer], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// UI�F��������
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int nCntRank = 0; nCntRank < MAX_PLAYER_NUM; nCntRank++)
	{
		for (int nCntUI = 0; nCntUI < MAX_PLAYER_NUM - 1; nCntUI++)
		{
			// �����̃e�N�X�`�����W�̌v�Z
			int nRank = (int)(pow(10, 3 - nCntUI));
			int nNumber = nSurviveTime[nCntRank] % nRank / (nRank / 10);

			// ������UI�̐���
			m_pUI[nCntRank * 3 + nCntUI] = CUI::Create(D3DXVECTOR2(SCREEN_WIDTH * 0.5f + 180.0f + 60.0f * nCntUI, 240.0f + 125.0f * nCntRank), D3DXVECTOR2(54.0f, 90.0f), 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pUI[nCntRank * 3 + nCntUI]->SetTex(nNumber, 0.1f);
		}
	}

	CSound::Play(3);

	return S_OK;
}

//*****************************************************************************
// �I��
//***************************************************************************** 
void CResultRank::Uninit()
{
	for (int nCnt = 0; nCnt < 12; nCnt++)
	{
		if (m_pUI[nCnt] != NULL)
		{
			m_pUI[nCnt] = NULL;
		}
	}
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
// �X�V
//***************************************************************************** 
void CResultRank::Update()
{
	m_nTime++;
	if (150 < m_nTime)
	{
#ifdef _DEBUG
		if (m_pKeyboard != NULL)
		{
			if (m_pKeyboard->GetAnyKey() == true)
			{
				CFade::SetFade(CManager::MODE_RESULTSELECT);
				CSound::Play(13);
			}
		}
#endif
		if (m_pGamePad != NULL)
		{
			if (m_pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_B, 0) == true)
			{
				CFade::SetFade(CManager::MODE_RESULTSELECT);
				CSound::Play(13);
			}
		}
	}
	if (MAX_RESULT_TIME <= m_nTime)
	{
		CFade::SetFade(CManager::MODE_RESULTSELECT);
	}
}

//�`��E�쐬
#if 1
//*****************************************************************************
//�`��
//***************************************************************************** 
void CResultRank::Draw()
{

}

void CResultRank::ZTexDraw()
{

}

//*****************************************************************************
//�쐬
//***************************************************************************** 
CResultRank *CResultRank::Create()
{
	CResultRank *pResultRank = NULL;
	pResultRank = new CResultRank(PRIORITY_PLANE);		//�������m��
														//NULL�`�F�b�N
	if (pResultRank != NULL)
	{
		pResultRank->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pResultRank;
}
#endif