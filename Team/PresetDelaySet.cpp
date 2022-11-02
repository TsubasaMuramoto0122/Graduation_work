//=============================================================================
// �x���t���v���Z�b�g�Ăяo���N���X
// Author : ������
//=============================================================================
#include "PresetDelaySet.h"
#include "presetseteffect.h"
#include "straight3d.h"
#include "fieldeffect.h"
#include "loadeffect.h"
#include "player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPresetDelaySet::CPresetDelaySet(PRIORITY nPriority) : CScene3D(nPriority)
{
	m_pos = {};			// �ʒu
	m_nDelay = 0;		// �f�B���C
	m_nCallCnt = 0;		// �Ăяo���J�E���g 
	m_nArray = 0;		// �ԍ�
	m_bMove = false;	// �I�����肷�邩
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPresetDelaySet::~CPresetDelaySet()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CPresetDelaySet::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;	// �ʒu

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CPresetDelaySet::Uninit()
{
	if (!m_vPreset.empty())
	{
		m_vPreset.clear();
		m_vPreset.shrink_to_fit();
	}

	Release();
}

//=============================================================================
// �X�V
//=============================================================================
void CPresetDelaySet::Update()
{
	// �v���Z�b�g�Ăяo������ۑ�
	CLoadEffect::CALL_PRESET CallPreset = CLoadEffect::GetCallPreset(m_nArray);

	//-----------------------------------------------------------------
	// �v���Z�b�g�Ăяo��
	//-----------------------------------------------------------------
	// �R�[�������ő吔�𒴂���܂Œʂ�
	if (m_nCallCnt < CallPreset.m_CallMax)
	{
		// �G�t�F�N�g���Ăяo��
		if (m_nDelay >= CallPreset.m_nDelay[m_nCallCnt])
		{
			// �v���Z�b�g�̃��[�J���N���X
			CPresetEffect *pPreset = nullptr;

			// ���W���e�L�X�g�œǂݍ��܂�Ă�����
			auto itr = CallPreset.m_Offset.find(m_nCallCnt);
			if (itr != CallPreset.m_Offset.end())
			{
				// �o���ʒu�Ƀe�L�X�g�œǂݍ��񂾍��W���v���X����
			D3DXVECTOR3 pos = CallPreset.m_Offset[m_nCallCnt] + m_pos;
				for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
				{
					// �v���Z�b�g�̐���
					pPreset = CPresetEffect::Create();
					pPreset->SetEffect3D(CallPreset.m_nType[m_nCallCnt].at(nCnt), pos, {}, {});
					m_vPreset.emplace_back(pPreset);
				}
			}

			// ���W�������ꍇ
			else
			{
				// �o���ʒu�ɃG�t�F�N�g���o��(m_pos�̂܂�)
				for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
				{
					// �v���Z�b�g�̐���
					pPreset = CPresetEffect::Create();
					pPreset->SetEffect3D(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, {}, {});
					m_vPreset.emplace_back(pPreset);
				}
			}

			// �R�[�������J�E���g
			m_nCallCnt++;
		}

		//SetDeath(true)
		// �f�B���C��i�߂�
		m_nDelay++;
	}

	//-----------------------------------------------------------------
	// �v���Z�b�g���Ăяo���I�������̏���
	//-----------------------------------------------------------------
	else
	{
		if (!m_bMove)
		{
			m_bMove = true;
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CPresetDelaySet::Draw()
{

}

//=============================================================================
// ����
//=============================================================================
CPresetDelaySet* CPresetDelaySet::Create(int nArray, D3DXVECTOR3 pos)
{
	// �������m��
	CPresetDelaySet *pPresetDelay = nullptr;
	pPresetDelay = new CPresetDelaySet(PRIORITY_EFFECT);

	if (pPresetDelay)
	{
		pPresetDelay->m_nArray = nArray;
		pPresetDelay->Init(pos);
	}

	return pPresetDelay;
}

//=============================================================================
// ����(���������)
//=============================================================================
CPresetDelaySet* CPresetDelaySet::Create(string sName, D3DXVECTOR3 pos)
{
	return Create(CLoadEffect::GetPresetName(sName), pos);
}

//=============================================================================
// �G�t�F�N�g�̈ړ�
//=============================================================================
void CPresetDelaySet::Move(D3DXVECTOR3 move)
{
	if (m_bMove)
	{
		if (!m_vPreset.empty())
		{
			for (CPresetEffect *pPreset : m_vPreset)
			{
				pPreset->Move(move);
			}
		}
	}
}