//=============================================================================
//
// �J�E���g�_�E��UI���� [playerui.h]
// Author : �O��q��
//
//=============================================================================
//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "playerui.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
//�ÓI
//*****************************************************************************

//*****************************************************************************
//�}�N��
//*****************************************************************************

#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CPlayerUI::CPlayerUI(CScene::PRIORITY Priority) : CUI(Priority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CPlayerUI::~CPlayerUI()
{

}
#endif

//*****************************************************************************
//������
//*****************************************************************************
HRESULT CPlayerUI::Init(int nTex)
{
	m_pUI = CUI::Create(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(50.0f, 35.0f), nTex, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_fHeight = 90.0f;
	return S_OK;
}

//*****************************************************************************
//�I��
//*****************************************************************************
void CPlayerUI::Uninit()
{
	if (m_pUI != NULL)
	{
		m_pUI = NULL;
	}
	CUI::Uninit();
}

//*****************************************************************************
//�X�V
//*****************************************************************************
void CPlayerUI::Update()
{
	
}

//*****************************************************************************
//�`��
//*****************************************************************************
void CPlayerUI::Draw()
{

}

//*****************************************************************************
//�쐬
//*****************************************************************************
CPlayerUI *CPlayerUI::Create(int nTex)
{
	CPlayerUI *pPlayerUI = NULL;
	pPlayerUI = new CPlayerUI(PRIORITY_UI);
	if (pPlayerUI != NULL)
	{
		pPlayerUI->Init(nTex);
	}
	return pPlayerUI;
}

void CPlayerUI::SetPos(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView, mtxProjection, mtxEnemy, mtxTrans, mtxParent;
	D3DXMATRIX mtxViewport =
	{ SCREEN_WIDTH / 2, 0, 0, 0, 0, -SCREEN_HEIGHT / 2, 0, 0, 0, 0, 1, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 1 }; //�r���[�|�[�g�z��
	pDevice = CManager::GetRenderer()->GetDevice();		 //�f�o�C�X���擾����
	//�G�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxEnemy);
	//�G�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, 0.0f, m_fHeight, 0.0f);
	D3DXMatrixMultiply(&mtxEnemy, &mtxEnemy, &mtxTrans);
	//�G�̃p�[�c�}�g���b�N�X�̎擾�A���f
	D3DXMatrixTranslation(&mtxParent, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxEnemy, &mtxEnemy, &mtxParent);
	//�r���[�ϊ�
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixMultiply(&mtxEnemy, &mtxEnemy, &mtxView);
	//�ˉe�ϊ�
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);
	D3DXMatrixMultiply(&mtxEnemy, &mtxEnemy, &mtxProjection);
	//�r���[�|�[�g�ϊ�
	D3DXMatrixMultiply(&mtxEnemy, &mtxEnemy, &mtxViewport);
	mtxEnemy._41 /= mtxEnemy._44;
	mtxEnemy._42 /= mtxEnemy._44;

	if (mtxEnemy._41 <= 0.0f || SCREEN_WIDTH <= mtxEnemy._41 ||
		mtxEnemy._42 <= 0.0f || SCREEN_HEIGHT <= mtxEnemy._42 || mtxEnemy._43 < 0.0f)
	{
		m_pUI->SetDraw(false);
	}
	else
	{
		m_pUI->SetDraw(true);
		m_pUI->SetPos(D3DXVECTOR3(mtxEnemy._41, mtxEnemy._42, 0.0f));
	}
}