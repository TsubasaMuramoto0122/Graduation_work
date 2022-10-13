//=============================================================================
//
// ���e���� [bomb.h]
// Author : �O��q��
//
//=============================================================================
#include "bomb.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "danger.h"
#include "sound.h"
#include "ui.h"
#include "collision_sphere.h"

//=============================================================================
//�ÓI
//=============================================================================
CModel *CBomb::m_paModel[MAX_BOMB] = {};

//=============================================================================
//�}�N��
//=============================================================================
#define REFLECT (-0.4f)		//����
#define GRAVITY (0.3f)		//�d��
#define FLASH_TIME (150)	//�_�ł��n�߂̎���
#define CLEAR_TIME (5)		//���邭�Ȃ�����Â��Ȃ�܂ł̎���

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

	//�Ή��������f���ɂ���
	m_pModel = new CModel;
	m_pModel->Copy(m_paModel[BombType]);

	//���f���̂��ꂼ��̕����̍ő�l�A�ŏ��l�����߂�
	VtxMax = m_pModel->GetMaxSize();
	VtxMin = m_pModel->GetMinSize();

	//��ԑ傫�����a�����߂�
	m_fRadius = (VtxMax.x - VtxMin.x) / 2.0f;
	if (m_fRadius < (VtxMax.y - VtxMin.y) / 2.0f)
	{
		m_fRadius = (VtxMax.y - VtxMin.y) / 2.0f;
	}
	if (m_fRadius < (VtxMax.z - VtxMin.z) / 2.0f)
	{
		m_fRadius = (VtxMax.z - VtxMin.z) / 2.0f;
	}

	m_move = move;
	m_nTime = 250;
	m_nFlash = 10;
	m_fClear = 1.0f;
	m_pDanger = CDanger::Create(D3DXVECTOR3(m_fRadius * 3.0f, 0.0f, m_fRadius * 3.0f), pos);
	SetRot(rot);
	SetPos(pos);
	m_bBound = false;
	m_bLand = false;

	//�R���W��������������
	m_pCollision = CCollisionSphere::Create(pos, m_fRadius * 2.0f, 16, 16, CCollisionSphere::COLLISION_S_TYPE::COLLISION_S_TYPE_PLAYER, -1.0f);

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
	if (m_pCollision != NULL)
	{
		m_pCollision->SetDeath(true);
		m_pCollision = NULL;
	}
	CScene3D::Uninit();
}

//�X�V����
void CBomb::Update()
{
	//�|�[�Y���łȂ��Ȃ�
	if (CManager::GetPause() == false)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();
		MoveDown();
		pos += m_move;
		Bound(pos);
		SetPos(pos);
		m_pDanger->Move(pos);
		m_pCollision->SetPos(pos);
		TimeDec(pos);
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

//���f���̔j��
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

//�댯���̓_��
void CBomb::Flash()
{
	m_nFlash--;
	if (m_nFlash >= CLEAR_TIME)
	{
		m_fClear -= 1.0f / (float)CLEAR_TIME;
		m_pDanger->ChangeColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fClear));
	}
	else
	{
		if (m_nFlash <= 0)
		{
			m_nFlash = CLEAR_TIME * 2;
		}
		m_fClear += 1.0f / (float)CLEAR_TIME;
		m_pDanger->ChangeColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fClear));
	}
}

//���Ԍ���
void CBomb::TimeDec(D3DXVECTOR3 pos)
{
	//�������܂�����
	if (m_nTime > 0)
	{
		m_nTime--;
		if (m_nTime < FLASH_TIME)
		{
			Flash();
		}
	}
	//�����؂�
	else
	{
		Explosion(pos);
		SetDeath(true);
	}
}

//�n�ʂɒ��n
void CBomb::Bound(D3DXVECTOR3 pos)
{
	//�n�ʂ�艺�ɂ���
	if (pos.y < 0.0f)
	{
		//�P�񒵂˂Ă�
		if (m_bBound == true)
		{
			pos.y = 0.0f;
			m_move.y = 0.0f;
			m_bLand = true;
		}
		//�܂����˂ĂȂ�
		else
		{
			pos.y = 0.0f;
			m_move.y *= REFLECT;
			m_bBound = true;
		}
	}
}

//�d�͂܂��͒n�ʂƂ̖��C�ɂ��ړ��ʂ̒ቺ
void CBomb::MoveDown()
{
	//���n���ĂȂ����߁A�d�͂�����
	if (m_bLand == false)
	{
		m_move.y -= GRAVITY;
	}
	//���n���Ă邽�߁A���C������
	else
	{
		m_move.x *= 0.97f;
		m_move.z *= 0.97f;
	}
}