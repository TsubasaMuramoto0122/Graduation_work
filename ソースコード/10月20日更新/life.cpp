//=============================================================================
// ���C�t�Ǘ� [life.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "life.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLifeUI::CLifeUI(PRIORITY Priority) : CUI::CUI(Priority)
{
	// �ϐ��̃N���A
	m_nLife = 0;
	m_fObjectiveSize = 0.0f;
	m_fMaxSize = 0.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_barPos = D3DXVECTOR2(0.0f, 0.0f);
	memset(&m_apUI, NULL, sizeof(m_apUI));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLifeUI::~CLifeUI()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLifeUI::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// �ϐ��̏�����
	m_nLife = 0;
	m_pos = pos;
	m_size = size;
	m_fObjectiveSize = m_size.x;
	m_fMaxSize = m_size.x;
	m_barPos = D3DXVECTOR2(m_pos.x - (m_size.x / 2), m_pos.y);

	// ���C�t�̔w�i����
	m_apUI[0] = CUI::Create(m_pos, m_size, -1, D3DCOLOR_RGBA(80, 80, 80, 255));

	// ���C�t�̃Q�[�W����
	m_apUI[1] = CUI::Create(D3DXVECTOR3(m_barPos.x, m_barPos.y , 0.0f), D3DXVECTOR2(m_size.x, m_size.y * 0.8f), -1, D3DCOLOR_RGBA(50, 255, 20, 255));
	m_apUI[1]->SetBesideGauge(m_size.x);

	// ���C�t�̘g����
	/*m_apUI[2] = CScene2D::Create(m_pos);
	m_apUI[2]->SetSize(m_size * 0.9f);
	m_apUI[2]->SetTexture(-1);
	m_apUI[2]->ColorChange(D3DCOLOR_RGBA(50, 255, 20, 255));*/


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLifeUI::Uninit()
{
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLifeUI::Update()
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CLifeUI::Draw()
{
	for (int nCnt2D = 0; nCnt2D < MAX_LIFE_IMAGE; nCnt2D++)
	{
		if (m_apUI[nCnt2D] != NULL)
		{
			m_apUI[nCnt2D]->Draw();
		}
	}
}

//=============================================================================
// ��������
//=============================================================================
CLifeUI *CLifeUI::Create(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	CLifeUI *pLifeUI = NULL;
	pLifeUI = new CLifeUI(PRIORITY_UI);		//�������m��
											//NULL�`�F�b�N
	if (pLifeUI != NULL)
	{
		pLifeUI->Init(D3DXVECTOR3(pos.x, pos.y, 0.0f), size);
	}

	return pLifeUI;
}

//=============================================================================
// ���C�t�o�[�̐ݒ菈��
//=============================================================================
void CLifeUI::SetLifeBar(int nNowLife, int nMaxLife)
{
	m_nLife = nNowLife;

	// �摜�̃T�C�Y�ƃ��C�t�̍ő�l���犄���̒l���o��
	float fRatio = m_fMaxSize / nMaxLife;

	// <�����~���݂̃��C�t>�ŖړI�̃T�C�Y���o��
	m_fObjectiveSize = fRatio * m_nLife;

	// ���C�t��0�ɂȂ�����
	if (nNowLife <= 0)
	{
		// �T�C�Y�������ɕύX���A�Q�[�W������
		m_size.x = m_fObjectiveSize;
		m_apUI[1]->SetBesideGauge(m_size.x);
	}

	// �ړI�̃T�C�Y�ƌ��݂̃T�C�Y���Ⴄ�Ȃ�
	if (m_fObjectiveSize != m_size.x)
	{
		// �ړI�̃T�C�Y�����݂̃T�C�Y��菬�����ꍇ
		if (m_fObjectiveSize < m_size.x)
		{
			m_size.x *= 0.99f;

			if (m_fObjectiveSize > m_size.x)
			{
				m_size.x = m_fObjectiveSize;
			}
		}
		// �ړI�̃T�C�Y�����݂̃T�C�Y���傫���ꍇ
		else if (m_fObjectiveSize > m_size.x)
		{
			m_size.x *= 1.01f;

			if (m_fObjectiveSize < m_size.x)
			{
				m_size.x = m_fObjectiveSize;
			}
		}

		// ������x�̒l�͈̔͂ɒB����܂ŃQ�[�W�̃T�C�Y��ύX
		if (m_size.x - m_fObjectiveSize > 0.01f || m_size.x - m_fObjectiveSize < -0.01f)
		{
			m_apUI[1]->SetBesideGauge(m_size.x);
		}
	}
}