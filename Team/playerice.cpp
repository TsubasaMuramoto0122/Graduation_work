//=============================================================================
//
// �v���C���[�̕X���� [playerice.h]
// Author : �O��q��
//
//=============================================================================
#include "playerice.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"

//�ÓI�����o�ϐ�
CModel *CPlayerIce::m_paModel = NULL;

CPlayerIce::CPlayerIce(PRIORITY nPriority) : CObject(nPriority)
{

}

CPlayerIce::~CPlayerIce()
{

}

//����������
HRESULT CPlayerIce::Init(D3DXMATRIX mtx)
{
	int nRandom = rand() % 11;
	float fRot;
	if (nRandom == 5)
	{
		fRot = 0.0f;
	}
	else
	{
		fRot = D3DX_PI / (nRandom - 5);
	}

	m_mtxParent = mtx;
	SetRot(D3DXVECTOR3(0.0f, fRot, 0.0f));
	m_pModel = new CModel;
	m_pModel->Copy(m_paModel);
	return S_OK;
}

//�I������
void CPlayerIce::Uninit()
{
	if (m_pModel != NULL)
	{
		m_pModel = NULL;
	}
	CScene3D::Uninit();
}

//�X�V����
void CPlayerIce::Update()
{
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{

	}
}

//�`�揈��
void CPlayerIce::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	m_pModel->Draw();
}

void CPlayerIce::ZTexDraw()
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

	// �e���f���Ɖ��Z
	//D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	m_pModel->ZTexDraw();
}

CPlayerIce *CPlayerIce::Create(D3DXMATRIX mtx)
{
	CPlayerIce *pPlayerIce;
	pPlayerIce = new CPlayerIce(CScene::PRIORITY_OBJECT);
	if (pPlayerIce != NULL)
	{
		pPlayerIce->Init(mtx);
	}
	return pPlayerIce;
}

void CPlayerIce::Load(const char *aModelName)
{
	m_paModel = CModel::Create(aModelName);
}

void CPlayerIce::UnLoad()
{
	if (m_paModel != NULL)
	{
		m_paModel->Uninit();
		m_paModel = NULL;
	}
}