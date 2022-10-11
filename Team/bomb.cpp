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
#define REFLECT (-0.4f)		//����
#define GRAVITY (0.3f)		//�d��

CBomb::CBomb(PRIORITY Priority) : CScene3D::CScene3D(Priority)
{

}

CBomb::~CBomb()
{

}

//����������
HRESULT CBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, BOMBTYPE BombType)
{
	D3DXVECTOR3 VtxMax, VtxMin;
	m_pModel = new CModel;
	m_pModel->Copy(m_paModel[BombType]);
	VtxMax = m_pModel->GetMaxSize();
	VtxMin = m_pModel->GetMinSize();
	float fRadius = (VtxMax.x - VtxMin.x) / 2.0f;
	if (fRadius < (VtxMax.y - VtxMin.y) / 2.0f)
	{
		fRadius = (VtxMax.y - VtxMin.y) / 2.0f;
	}
	if (fRadius < (VtxMax.z - VtxMin.z) / 2.0f)
	{
		fRadius = (VtxMax.z - VtxMin.z) / 2.0f;
	}
	m_move = move;
	m_nTime = 250;
	m_pDanger = CDanger::Create(D3DXVECTOR3(fRadius * 3.0f, 0.0f, fRadius * 3.0f), pos);
	SetRot(rot);
	SetPos(pos);
	m_bBound = false;
	m_bLand = false;
	return S_OK;
}

//�I������
void CBomb::Uninit()
{
	if (m_pModel != NULL)
	{
		//m_pModel->Uninit();
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
	if (CManager::GetPause() == false)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();
		if (m_bLand == false)
		{
			pos += m_move;
			m_move.y -= GRAVITY;
		}
		else
		{
			pos += m_move;
			m_move *= 0.97f;
		}
		if (pos.y < 0.0f)
		{
			if (m_bBound == true)
			{
				pos.y = 0.0f;
				m_move.y = 0.0f;
				m_bLand = true;
			}
			else
			{
				pos.y = 0.0f;
				m_move.y *= REFLECT;
				m_bBound = true;
			}
		}
		SetPos(pos);
		m_pDanger->Move(pos);
		if (m_nTime > 0)
		{
			m_nTime--;
		}
		else
		{
			//Explosion();
			SetDeath(true);
		}
	}
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