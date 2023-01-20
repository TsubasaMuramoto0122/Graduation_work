//=============================================================================
//
// �I�u�W�F�N�g���� [object.h]
// Author : �O��q��
//
//=============================================================================
#include "object.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"

//�ÓI�����o�ϐ�
CModel *CObject::m_paModel[8] = {};

CObject::CObject(PRIORITY nPriority) : CScene3D(nPriority)
{

}

CObject::~CObject()
{

}

//����������
HRESULT CObject::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, bool bShadow)
{
	SetPos(pos);
	SetRot(rot);
	ModelCopy(nType);
	m_pModel->SetShadow(bShadow);
	
	return S_OK;
}

//�I������
void CObject::Uninit()
{
	if (m_pModel != NULL)
	{
		m_pModel = NULL;
	}
	CScene3D::Uninit();
}

//�X�V����
void CObject::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		
	}
}

//�`�揈��
void CObject::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	m_pModel->Draw();
}

void CObject::ZTexDraw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//pos�Arot�̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	m_pModel->ZTexDraw();
}

CObject *CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, bool bShadow)
{
	CObject *pObject;
	pObject = new CObject(CScene::PRIORITY_OBJECT);
	if (pObject != NULL)
	{
		pObject->Init(pos, rot, nType, bShadow);
	}
	return pObject;
}

void CObject::Load(int nCnt, const char *aModelName)
{
	m_paModel[nCnt] = CModel::Create(aModelName);
}

void CObject::UnLoad()
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < MAX_OBJECTS; nCntModel++)
	{
		if (m_paModel[nCntModel] != NULL)
		{
			m_paModel[nCntModel]->Uninit();
			m_paModel[nCntModel] = NULL;
		}
	}
}

void CObject::ModelCopy(int nType)
{
	m_pModel = new CModel;
	m_pModel->Copy(m_paModel[nType]);
}