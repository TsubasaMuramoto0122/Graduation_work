//=============================================================================
// ���̃R���W�������� [collision_sphere.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "collision_sphere.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "model.h"
#include "sound.h"
#include "keyboard.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
bool CCollisionSphere::m_bMngVisual = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCollisionSphere::CCollisionSphere(PRIORITY Priority) : CScene3D::CScene3D(Priority)
{
	// �ϐ��̃N���A
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = NULL;
	m_col = D3DCOLOR_RGBA(0, 0, 0, 153);
	m_collisionType = COLLISION_S_TYPE_MAX;
	m_nVertical = 0;
	m_nSide = 0;
	m_nNumPlayer = 0;
	m_fSize = 0.0f;
	m_fTime = 0.0f;
	m_fDamage = 0.0f;
	m_fObjectiveRot = 0.0f;
	m_bContact = false;
	m_bTouchAttack = false;
	m_bTouchExplosion = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCollisionSphere::~CCollisionSphere()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCollisionSphere::Init(D3DXVECTOR3 pos, float fSize)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �ϐ��̏�����
	m_pos = pos;
	m_fSize = fSize;
	m_nNumPlayer = -1;
	m_fObjectiveRot = 0.0f;
	m_bContact = false;
	m_bTouchAttack = false;
	m_bTouchExplosion = false;

	// ���_�o�b�t�@�̐���
	//��(�c�̕������{�P)�~(���̕������{�P)�̒l�̒��_�𐶐�����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((m_nVertical + 1) * (m_nSide + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntVtx = 0;

	// ���_���W�̐ݒ�
	for (int nCntSide = m_nSide + 1; nCntSide > 0; nCntSide--)
	{
		for (int nCntVertical = 0; nCntVertical < m_nVertical + 1; nCntVertical++, nCntVtx++)
		{
			pVtx[nCntVtx].pos = D3DXVECTOR3(cosf((D3DX_PI * 2.0f / m_nVertical) * nCntVertical) * (sinf(((D3DX_PI * 2.0f / m_nVertical) * nCntSide) + ((D3DX_PI * 2.0f / m_nVertical) * m_nSide)) * (m_fSize / 2.0f)),
								  m_pos.y + cosf((D3DX_PI * 2.0f / m_nVertical) * nCntSide) * (m_fSize / 2.0f),
											sinf((D3DX_PI * 2.0f / m_nVertical) * nCntVertical) * (sinf(((D3DX_PI * 2.0f / m_nVertical) * nCntSide) + ((D3DX_PI * 2.0f / m_nVertical) * m_nSide)) * (m_fSize / 2.0f)));

			// �@��
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// �J���[
			pVtx[nCntVtx].col = m_col;

			// �e�N�X�`��
			pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f + -(1.0f / m_nVertical * nCntVertical), 0.0f + -(1.0f / m_nSide * nCntSide));
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((m_nSide - 1) * (m_nVertical + 3) + (m_nVertical + 1) * (m_nSide + 1)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// �C���f�b�N�X���ւ̃|�C���^
	WORD *pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �ԍ��f�[�^�̐ݒ�
	for (int nCntSide = 0; nCntSide < m_nSide; nCntSide++)
	{
		for (int nCntVertical = 0; nCntVertical < m_nVertical + 1; nCntVertical++)
		{
			pIdx[(nCntVertical * 2) + 0 + (m_nVertical + 2) * 2 * nCntSide] = (WORD)((m_nVertical + 1) + nCntVertical + (m_nVertical + 1) * nCntSide);
			pIdx[(nCntVertical * 2) + 1 + (m_nVertical + 2) * 2 * nCntSide] = (WORD)(0 + nCntVertical + (m_nVertical + 1) * nCntSide);
		}
	}

	for (int nCntSide = 0; nCntSide < m_nSide - 1; nCntSide++)
	{
		pIdx[((m_nVertical + 1) * 2 + 0) * (nCntSide + 1) + (2 * nCntSide)] = (WORD)(m_nVertical + (m_nVertical + 1) * nCntSide);
		pIdx[((m_nVertical + 1) * 2 + 1) * (nCntSide + 1) + (1 * nCntSide)] = (WORD)(m_nVertical * 2 + 2 + (m_nVertical + 1) * nCntSide);
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCollisionSphere::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCollisionSphere::Update(void)
{
	if (this != NULL)
	{
		m_bContact = false;

		// �����m�̓����蔻��
		Collision(this);

#ifdef _DEBUG
		// ����̉�������
		VisualOn(m_bMngVisual);
#endif

		// ���������炷
		if (m_fTime > -1.0f)
		{
			m_fTime -= 1.0f;

			// ���Ԍo�߂ŏ���
			if (m_fTime <= 0.0f)
			{
				Uninit();
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCollisionSphere::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxParent;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_WORLD, &mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

#ifdef _DEBUG
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,
		0,
		((m_nVertical + 1) * (m_nSide + 1)),				//���_�̐�
		0,													//�J�n���钸�_�̃C���f�b�N�X
		(m_nSide * m_nVertical * 2) + (m_nSide * 4) - 4);	//�`�悷��v���~�e�B�u��
#endif

	//���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// ��������
//=============================================================================
CCollisionSphere* CCollisionSphere::Create(D3DXVECTOR3 pos, float fSize, int nVertical, int nSide,
	COLLISION_S_TYPE type, float fTime)
{
	// �C���X�^���X�̐���
	CCollisionSphere *pCollisionS = NULL;

	// �k���`�F�b�N
	if (pCollisionS == NULL)
	{
		// �N���X�̐���
		pCollisionS = new CCollisionSphere;
		if (pCollisionS != NULL)
		{
			// �ϐ��̏�����
			pCollisionS->m_nVertical = nVertical;
			pCollisionS->m_nSide = nSide;
			pCollisionS->m_fTime = fTime;
			pCollisionS->m_collisionType = type;

			// ���[���h�}�g���b�N�X�ݒ�O�ɏՓ˔�����s�����߁A��Ɏw��ʒu�����[���h�}�g���b�N�X�ɐݒ肵�Ă���
			pCollisionS->m_mtxWorld._41 = pos.x;
			pCollisionS->m_mtxWorld._42 = pos.y;
			pCollisionS->m_mtxWorld._43 = pos.z;

			switch (type)
			{
				// �v���C���[�F��
			case COLLISION_S_TYPE_PLAYER:
				pCollisionS->m_col = D3DCOLOR_RGBA(255, 255, 255, 0);
				break;
				// �U���F��
			case COLLISION_S_TYPE_ATTACK:
				pCollisionS->m_col = D3DCOLOR_RGBA(0, 255, 0, 0);
				break;
				// �����F��
			case COLLISION_S_TYPE_EXPLOSION:
				pCollisionS->m_col = D3DCOLOR_RGBA(255, 0, 0, 0);
				break;
				// �X�F���F
			case COLLISION_S_TYPE_ICE:
				pCollisionS->m_col = D3DCOLOR_RGBA(0, 210, 255, 0);
				break;
				// �ŁF��
			case COLLISION_S_TYPE_POISON:
				pCollisionS->m_col = D3DCOLOR_RGBA(200, 100, 225, 0);
				break;
				// �����F���F
			case COLLISION_S_TYPE_PANIC:
				pCollisionS->m_col = D3DCOLOR_RGBA(255, 255, 0, 0);
				break;
			default:
				break;
			}

			// ����������
			pCollisionS->Init(pos, fSize);
		}
	}

	return pCollisionS;
}

//=============================================================================
// �Փˏ���
//=============================================================================
void CCollisionSphere::Collision(CScene *pScene)
{
	m_bContact = false;
	m_bTouchAttack = false;
	m_bTouchExplosion = false;

	//�I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CScene *pSaveObject = NULL;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CScene::PRIORITY_EFFECT);

	while (pObject != NULL)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECTTYPE_NONE)
		{
			CCollisionSphere *pCollisionS = NULL;
			pCollisionS = (CCollisionSphere*)pObject;

			// �����ȊO�̋��̃R���W��������������
			if (pObject != this)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);	//���g�̈ʒu
				float fSize = pScene->GetRadius();												//���g�̔��a�̑傫��
				D3DXVECTOR3 posColl = pCollisionS->GetMtxPos();									//�Ώۂ̃R���W�����̈ʒu
				float fSizeColl = pCollisionS->GetRadius();										//�Ώۂ̃R���W�����̃T�C�Y
				COLLISION_S_TYPE typeColl = pCollisionS->GetCollisionType();					//�Ώۂ̃R���W�����̎��
				int nNumPlayerColl = pCollisionS->GetNumPlayer();								//�Ώۂ̔ԍ�

				// �R���W�������m�̋����Ɣ��a�����߂�
				float fDistance = sqrtf((posColl.x - pos.x) * (posColl.x - pos.x) + (posColl.y - pos.y) * (posColl.y - pos.y) + (posColl.z - pos.z) * (posColl.z - pos.z));
				float fRadius = sqrtf((fSizeColl + fSize) * (fSizeColl + fSize));

				// �ړI�̌�����ݒ�
				m_fObjectiveRot = (float)atan2((posColl.x - pos.x), (posColl.z - pos.z)) - D3DX_PI;

				// ���������a��菬�����Ȃ������A���g�̍U������Ȃ��Ȃ�
				if (fDistance < fRadius && m_nNumPlayer != nNumPlayerColl)
				{
					m_bContact = true;

					if (typeColl == COLLISION_S_TYPE_ATTACK)
					{
						m_bTouchAttack = true;
					}

					if (typeColl == COLLISION_S_TYPE_EXPLOSION)
					{
						m_bTouchExplosion = true;
					}
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//=============================================================================
// �ʒu�ݒ菈��
//=============================================================================
void CCollisionSphere::SetPosCollision(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �R���W�����̎�ނ̎擾����
//=============================================================================
CCollisionSphere::COLLISION_S_TYPE CCollisionSphere::GetCollisionType(void)
{
	return m_collisionType;
}

//=============================================================================
// �e���f���ݒ菈��
//=============================================================================
void CCollisionSphere::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//=============================================================================
// ���[���h�}�g���b�N�X���W�擾����
//=============================================================================
D3DXVECTOR3 CCollisionSphere::GetMtxPos(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

	return pos;
}

//=============================================================================
// ���a�擾����
//=============================================================================
float CCollisionSphere::GetRadius(void)
{
	return m_fSize / 2;
}

//=============================================================================
// �R���W�����̎�ސݒ菈��
//=============================================================================
void CCollisionSphere::SetCollisionType(COLLISION_S_TYPE type)
{
	m_collisionType = type;

	switch (type)
	{
		// �v���C���[�F��
	case COLLISION_S_TYPE_PLAYER:
		m_col = D3DCOLOR_RGBA(255, 255, 255, 0);
		break;
		// �U���F��
	case COLLISION_S_TYPE_ATTACK:
		m_col = D3DCOLOR_RGBA(0, 255, 0, 0);
		break;
		// �����F��
	case COLLISION_S_TYPE_EXPLOSION:
		m_col = D3DCOLOR_RGBA(255, 0, 0, 0);
		break;
		// �X�F���F
	case COLLISION_S_TYPE_ICE:
		m_col = D3DCOLOR_RGBA(0, 210, 255, 0);
		break;
		// �ŁF��
	case COLLISION_S_TYPE_POISON:
		m_col = D3DCOLOR_RGBA(200, 100, 225, 0);
		break;
		// �����F���F
	case COLLISION_S_TYPE_PANIC:
		m_col = D3DCOLOR_RGBA(255, 255, 0, 0);
		break;
	default:
		break;
	}
}

//=============================================================================
// �w��̃I�u�W�F�N�g�ɓ����������ǂ���
//=============================================================================
bool CCollisionSphere::GetTouchCollision(COLLISION_S_TYPE type)
{
	switch (type)
	{
	case COLLISION_S_TYPE_PLAYER:
		return false;
		break;
	case COLLISION_S_TYPE_ATTACK:
 		return m_bTouchAttack;
		break;
	case COLLISION_S_TYPE_EXPLOSION:
		return m_bTouchExplosion;
		break;
	case COLLISION_S_TYPE_ICE:
		return false;
		break;
	case COLLISION_S_TYPE_POISON:
		return false;
		break;
	case COLLISION_S_TYPE_PANIC:
		return false;
		break;
	default:
		return false;
		break;
	}
}

//=============================================================================
// �ԍ��ݒ菈��
//=============================================================================
void CCollisionSphere::SetNumPlayer(int nNum)
{
	m_nNumPlayer = nNum;
}

//=============================================================================
// �ԍ��擾����
//=============================================================================
int CCollisionSphere::GetNumPlayer(void)
{
	return m_nNumPlayer;
}

//=============================================================================
// �ԍ��擾����
//=============================================================================
float CCollisionSphere::GetObjectiveRot(void)
{
	return m_fObjectiveRot;
}

#ifdef _DEBUG
//=============================================================================
// ����̉����ݒ菈��
//=============================================================================
void CCollisionSphere::SetVisual(bool bVisual)
{
	m_bMngVisual = bVisual;
}

//=============================================================================
// ����̉�������
//=============================================================================
void CCollisionSphere::VisualOn(bool bVisual)
{
	D3DXCOLOR col = m_col;

	// ����OFF
	if (bVisual == false)
	{
		col = D3DXCOLOR(col.r, col.g, col.b, 0);
	}
	// ����ON
	else
	{
		col = D3DXCOLOR(col.r, col.g, col.b, 0.6f);
	}

	// ���_�o�b�t�@��NULL����Ȃ�������
	//�����ꂪ�Ȃ��ƃ��f���{�̂��������ہA���̂��c�葱���Ă��܂�
	if (m_pVtxBuff != NULL)
	{
		// ���_�o�b�t�@�ւ̃|�C���^
		VERTEX_3D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		int nCntVtx = 0;

		for (int nCntSide = m_nSide + 1; nCntSide > 0; nCntSide--)
		{
			for (int nCntVertical = 0; nCntVertical < m_nVertical + 1; nCntVertical++, nCntVtx++)
			{
				// �J���[
				pVtx[nCntVtx].col = col;
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}
#endif