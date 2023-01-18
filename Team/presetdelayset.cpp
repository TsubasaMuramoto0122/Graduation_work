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
#include "scene.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPresetDelaySet::CPresetDelaySet(PRIORITY nPriority) : CScene3D(nPriority)
{
	m_pos = {};			// �ʒu
	m_nDelay = 0;		// �f�B���C
	m_nCallCnt = 0;		// �Ăяo���J�E���g 
	m_nArray = 0;		// �ԍ�
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
			// �I�t�Z�b�g���e�L�X�g�œǂݍ��܂�Ă�����
			auto itr = CallPreset.m_Offset.find(m_nCallCnt);
			if (itr != CallPreset.m_Offset.end())
			{
				// �I�t�Z�b�g�̐ݒ�
				D3DXVECTOR3 offset = CallPreset.m_Offset[m_nCallCnt];
				for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
				{
					// �v���Z�b�g�̐���
					CPresetEffect::Create(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, offset, m_pPlayer);
				}
			}

			// ���W�������ꍇ
			else
			{
				// �o���ʒu�ɃG�t�F�N�g���o��(m_pos�̂܂�)
				for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
				{
					// �v���Z�b�g�̐���
					CPresetEffect::Create(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, {}, m_pPlayer);
				}
			}

			// �R�[�������J�E���g
			m_nCallCnt++;
		}

		// �f�B���C��i�߂�
		m_nDelay++;
	}

	else
	{
		SetDeath(true);
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
CPresetDelaySet* CPresetDelaySet::Create(int nArray, D3DXVECTOR3 pos, CPlayer *pPlayer)
{
	// �������m��
	CPresetDelaySet *pPresetDelay = nullptr;
	pPresetDelay = new CPresetDelaySet(PRIORITY_EFFECTSET);

	if (pPresetDelay)
	{
		pPresetDelay->m_pPlayer = pPlayer;
		pPresetDelay->m_nArray = nArray;
		pPresetDelay->Init(pos);
	}

	return pPresetDelay;
}

//=============================================================================
// ����(���������)
//=============================================================================
CPresetDelaySet* CPresetDelaySet::Create(string sName, D3DXVECTOR3 pos, CPlayer *pPlayer)
{
	return Create(CLoadEffect::GetPresetName(sName), pos, pPlayer);
}
