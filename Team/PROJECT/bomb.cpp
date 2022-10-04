//---------------------------
// Author:�O��q��
// �{��(bomb.cpp)
//---------------------------
#include "bomb.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "danger.h"
#include "sound.h"
#include "ui.h"

//=============================================================================
//�ÓI
//=============================================================================
CModel *CBomb::m_paModel[MAX_BOMB] = {};

//=============================================================================
//�}�N��
//=============================================================================

CBomb::CBomb(PRIORITY Priority) : CScene3D::CScene3D(Priority)
{

}

CBomb::~CBomb()
{

}

//����������
HRESULT CBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, BOMBTYPE BombType)
{
	D3DXVECTOR3 VtxMax, VtxMin;
	m_pModel = new CModel;
	m_pModel->Copy(m_paModel[BombType]);
	VtxMax = m_pModel->GetMaxSize();
	VtxMin = m_pModel->GetMinSize();
	float fRadius = (VtxMax.x - VtxMin.x) / 2;
	if (fRadius < (VtxMax.y - VtxMin.y) / 2)
	{
		fRadius = (VtxMax.y - VtxMin.y) / 2;
	}
	if (fRadius < (VtxMax.z - VtxMin.z) / 2)
	{
		fRadius = (VtxMax.z - VtxMin.z) / 2;
	}
	//m_pDanger = CDanger::Create(D3DXVECTOR3(fRadius * 3.0f, 0.0f, fRadius * 3.0f), pos);
	SetRot(rot);
	SetPos(pos);
	return S_OK;
}

//�I������
void CBomb::Uninit()
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		m_pModel = NULL;
	}
	if (m_pDanger != NULL)
	{
		m_pDanger->SetDeath(true);
		m_pDanger = NULL;
	}
	CScene3D::Uninit();
}

//�X�V����
void CBomb::Update()
{

}

//�`�揈��
void CBomb::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxPlayer, mtxRot, mtxTrans;
	pDevice = CManager::GetRenderer()->GetDevice();		 //�f�o�C�X���擾����

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxPlayer);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxPlayer);
	SetMatrix(mtxPlayer);
	m_pModel->Draw();
}

void CBomb::Load(int nCnt, const char *aModelName)
{
	m_paModel[nCnt] = CModel::Create(aModelName);
}

void CBomb::UnLoad()
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < MAX_BOMB; nCntModel++)
	{
		if (m_paModel[nCntModel] != NULL)
		{
			m_paModel[nCntModel]->Uninit();
			m_paModel[nCntModel] = NULL;
		}
	}
}