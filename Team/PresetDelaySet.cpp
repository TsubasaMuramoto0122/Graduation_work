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
<<<<<<< HEAD
#include "scene.h"
=======
<<<<<<< HEAD
#include "scene.h"
=======
#include "manager.h"
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a

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
<<<<<<< HEAD
	// �v���Z�b�g�Ăяo������ۑ�
	CLoadEffect::CALL_PRESET CallPreset = CLoadEffect::GetCallPreset(m_nArray);

	//-----------------------------------------------------------------
	// �v���Z�b�g�Ăяo��
	//-----------------------------------------------------------------
	// �R�[�������ő吔�𒴂���܂Œʂ�
	if (m_nCallCnt < CallPreset.m_CallMax)
=======
	if (CManager::GetPause() == false && CManager::GetCountdown() == false)
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a
	{
		// �G�t�F�N�g���Ăяo��
		if (m_nDelay >= CallPreset.m_nDelay[m_nCallCnt])
		{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a
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
<<<<<<< HEAD
=======
=======
			// �G�t�F�N�g���Ăяo��
			if (m_nDelay >= CallPreset.m_nDelay[m_nCallCnt])
			{
				// �v���Z�b�g�̃��[�J���N���X
				CPresetEffect *pPreset = nullptr;

				// ���W���e�L�X�g�œǂݍ��܂�Ă�����
				auto itr = CallPreset.m_Sftpos.find(m_nCallCnt);
				if (itr != CallPreset.m_Sftpos.end())
				{
					// �o���ʒu�Ƀe�L�X�g�œǂݍ��񂾍��W���v���X����
					D3DXVECTOR3 pos = CallPreset.m_Sftpos[m_nCallCnt] + m_pos;
					for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
					{
						// �v���Z�b�g�̐���
						pPreset = CPresetEffect::Create();
						pPreset->SetEffect3D(CallPreset.m_nType[m_nCallCnt].at(nCnt), pos, {}, {});
						m_vPreset.emplace_back(pPreset);
					}
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a
				}
			}

			// ���W�������ꍇ
			else
			{
				// �o���ʒu�ɃG�t�F�N�g���o��(m_pos�̂܂�)
				for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
				{
<<<<<<< HEAD
					// �v���Z�b�g�̐���
					CPresetEffect::Create(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, {}, m_pPlayer);
=======
<<<<<<< HEAD
					// �v���Z�b�g�̐���
					CPresetEffect::Create(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, {}, m_pPlayer);
=======
					// �o���ʒu�ɃG�t�F�N�g���o��(m_pos�̂܂�)
					for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
					{
						// �v���Z�b�g�̐���
						pPreset = CPresetEffect::Create();
						pPreset->SetEffect3D(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, {}, {});
						m_vPreset.emplace_back(pPreset);
					}
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a
				}
			}

<<<<<<< HEAD
			// �R�[�������J�E���g
			m_nCallCnt++;
		}

		// �f�B���C��i�߂�
		m_nDelay++;
	}

	else
	{
		SetDeath(true);
=======
<<<<<<< HEAD
		// �f�B���C��i�߂�
		m_nDelay++;
	}

	else
	{
		SetDeath(true);
=======
		//-----------------------------------------------------------------
		// �v���Z�b�g���Ăяo���I�������̏���
		//-----------------------------------------------------------------
		else
		{
			SetDeath(true);
			if (!m_bMove)
			{
				m_bMove = true;
			}
		}
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a
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
<<<<<<< HEAD
CPresetDelaySet* CPresetDelaySet::Create(string sName, D3DXVECTOR3 pos, CPlayer *pPlayer)
=======
<<<<<<< HEAD
CPresetDelaySet* CPresetDelaySet::Create(string sName, D3DXVECTOR3 pos, CPlayer *pPlayer)
=======
CPresetDelaySet* CPresetDelaySet::Create(string sName, D3DXVECTOR3 pos)
{
	return Create(CLoadEffect::GetPresetName(sName), pos);
}

//=============================================================================
// ����(���������)
//=============================================================================
void CPresetDelaySet::Move(D3DXVECTOR3 move)
>>>>>>> edf369e2fe44aed194aa4aed39d2958e583283af
>>>>>>> e1265ec22361454c26360ce27e721e0a1665dc3a
{
	return Create(CLoadEffect::GetPresetName(sName), pos, pPlayer);
}