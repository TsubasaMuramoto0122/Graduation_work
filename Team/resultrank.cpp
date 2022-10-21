//=============================================================================
//
// ���U���g�����L���O���� [result.h]
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

	//�w�i�A�����A�g
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), -1, D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 80.0f, 0.0f), D3DXVECTOR2(500.0f, 100.0f), 18, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 380.0f, 0.0f), D3DXVECTOR2(880.0f, 680.0f), 14, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	int nCntRank;
	int nSurviveTime[MAX_PLAYER_NUM], nPlayerNum[MAX_PLAYER_NUM], nRank, nNumber;

	// ���ꂼ��̃v���C���[�̔ԍ��Ɛ������Ԃ��擾
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_NUM; nCntPlayer++)
	{
		nPlayerNum[nCntPlayer] = nCntPlayer;
		nSurviveTime[nCntPlayer] = CPlayer::GetSurviveTime(nCntPlayer);
	}

	for (int nCnt = 0; nCnt < MAX_PLAYER_NUM; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 < MAX_PLAYER_NUM - 1; nCnt2++)
		{
			// �������Ԃƃv���C���[�̔ԍ����~���ɕ��בւ�
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

	// ��ʂɉ���������
	for (nCntRank = 0; nCntRank < 1; nCntRank++)
	{
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 270.0f, 240.0f + 125.0f * nCntRank, 0.0f), D3DXVECTOR2(160.0f, 140.0f), 12, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// ���ʂ̕\��
	for (nCntRank = 0; nCntRank < MAX_PLAYER_NUM; nCntRank++)
	{
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 100.0f, 240.0f + 125.0f * nCntRank, 0.0f), D3DXVECTOR2(160.0f, 108.0f), 4 + nCntRank, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// nP�̕\��
	for (nCntRank = 0; nCntRank < MAX_PLAYER_NUM; nCntRank++)
	{
		CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 60.0f, 240.0f + 125.0f * nCntRank, 0.0f), D3DXVECTOR2(120.0f, 90.0f), 8 + nPlayerNum[nCntRank], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// �����̃e�N�X�`�����W�̐ݒ�
	for (nCntRank = 0; nCntRank < MAX_PLAYER_NUM; nCntRank++)
	{
		for (int nCntUI = 0; nCntUI < 3; nCntUI++)
		{
			nRank = (int)(pow(10, 3 - nCntUI));
			nNumber = nSurviveTime[nCntRank] % nRank / (nRank / 10);
			m_pUI[nCntRank * 3 + nCntUI] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 180.0f + 60.0f * nCntUI, 240.0f + 125.0f * nCntRank, 0.0f), D3DXVECTOR2(54.0f, 90.0f), 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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
	CScene::Release();
}

//*****************************************************************************
// �X�V
//***************************************************************************** 
void CResultRank::Update()
{
	if (m_pKeyboard != NULL)
	{
		if (m_pKeyboard->GetAnyKey() == true)
		{
			CFade::SetFade(CManager::MODE_RESULTSELECT);
			CSound::Play(10);
		}
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

//*****************************************************************************
//�쐬
//***************************************************************************** 
CResultRank *CResultRank::Create()
{
	CResultRank *pResultRank = NULL;
	pResultRank = new CResultRank(PRIORITY_ORBIT);		//�������m��
														//NULL�`�F�b�N
	if (pResultRank != NULL)
	{
		pResultRank->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pResultRank;
}
#endif