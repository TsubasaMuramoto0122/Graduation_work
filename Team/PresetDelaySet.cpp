//=============================================================================
// �x���t���v���Z�b�g�Ăяo���N���X
// Author : ������
//=============================================================================
#include "PresetDelaySet.h"
#include "loadeffect.h"
#include "presetseteffect.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPresetDelaySet::CPresetDelaySet(PRIORITY nPriority) : CScene3D(nPriority)
{
	m_pos = {};			// �ʒu
	m_nDelay = 0;		// �f�B���C
	m_nCallCnt = 0;		// �Ăяo���J�E���g 
	m_nArray = 0;			// �ԍ�
	m_bUninit = false;	// �I�����肷�邩
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

	// �G�t�F�N�g���Ăяo��
	if (m_nDelay >= CallPreset.m_nDelay[m_nCallCnt])
	{
		for (int nCnt = 0; nCnt < CallPreset.m_nPresetNum[m_nCallCnt]; nCnt++)
		{
			CPresetEffect::SetEffect3D(CallPreset.m_nType[m_nCallCnt].at(nCnt), m_pos, {}, {});
		}
		m_nCallCnt++;
	}

	// �R�[�������ő吔�𒴂���
	if (m_nCallCnt >= CallPreset.m_CallMax)
	{
		SetDeath(true);
	}

	// �f�B���C��i�߂�
	m_nDelay++;
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
// ����
//=============================================================================
CPresetDelaySet* CPresetDelaySet::Create(std::string sName, D3DXVECTOR3 pos)
{
	return Create(CLoadEffect::GetPresetName(sName), pos);
}