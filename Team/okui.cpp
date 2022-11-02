//=============================================================================
// �G���g���[OK����(okUI.h)
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "okui.h"
#include "fade.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COUNT_TIME		(35)
#define SHRINK_SIZE_X	(2.2f)
#define SHRINK_SIZE_Y	(1.4f)

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
COkUI::COkUI(CScene::PRIORITY Priority) : CUI(Priority)
{
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_nTime = 0;
	m_bShrink = false;
	m_pUI = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
COkUI::~COkUI()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT COkUI::Init(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	m_size = size;
	m_nTime = 0;
	m_bShrink = false;
	m_pUI = CUI::Create(D3DXVECTOR3(pos.x, pos.y, 0.0f), m_size, 19, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void COkUI::Uninit()
{
	if (m_pUI != NULL)
	{
		m_pUI->SetDeath(true);
		m_pUI = NULL;
	}
	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void COkUI::Update()
{
	m_nTime++;

	if (m_bShrink == false)
	{
		m_size.x += SHRINK_SIZE_X;
		m_size.y += SHRINK_SIZE_Y;
	}
	else
	{
		m_size.x -= SHRINK_SIZE_X;
		m_size.y -= SHRINK_SIZE_Y;
	}

	m_pUI->SetSize(m_size);

	if (m_nTime > COUNT_TIME)
	{
		m_bShrink = !m_bShrink;
		m_nTime = 0;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void COkUI::Draw()
{

}

//=============================================================================
// ��������
//=============================================================================
COkUI *COkUI::Create(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	COkUI *pReadyUI = NULL;
	pReadyUI = new COkUI(PRIORITY_UI);
	if (pReadyUI != NULL)
	{
		pReadyUI->Init(pos, size);
	}
	return pReadyUI;
}