//=============================================================================
// ���b�V��(�E�H�[��)���� [mesh_wall.cpp]
// Author : Kusakari Kakeru
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "mesh_wall.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshWall::CMeshWall(PRIORITY nPriority) :CScene3D(nPriority)
{
	// �ϐ��̃N���A
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nRow = 0;
	m_nLine = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshWall::~CMeshWall()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshWall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �ϐ��̏�����
	m_pos = pos;
	m_size = size;

	// �ʒu�̐ݒ�
	SetPos(m_pos);

	// ���_�o�b�t�@�̐���
	//��(�c�̕������{�P)�~(���̕������{�P)�̒l�̒��_�𐶐�����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nLine + 1) * (m_nRow + 1),
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
	for (int nCntVertical = 0; nCntVertical < m_nLine + 1; nCntVertical++)
	{
		for (int nCntRow = 0; nCntRow < m_nRow + 1; nCntRow++, nCntVtx++)
		{
			pVtx[nCntVtx].pos = D3DXVECTOR3((-m_size.x / 2.0f) + (nCntRow * (m_size.x / m_nRow)),
				(m_size.y / 2.0f) + (m_size.y / 2.0f) - (nCntVertical * (m_size.y / m_nLine)),
				m_size.z);

			// �@��
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// �J���[�̐ݒ�
			pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// �e�N�X�`��
			pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f + (nCntRow * 1.0f), 0.0f + (nCntVertical * 1.0f));
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	//��(���_�̍��v)+(�d�����Ēu���ꂽ���_)�̒l�𐶐�
	pDevice->CreateIndexBuffer(sizeof(WORD) * (((m_nRow + 1) * (m_nLine + 1)) + ((m_nRow + 3) * (m_nLine - 1))),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// �C���f�b�N�X���ւ̃|�C���^
	WORD *pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void **)&pIdx, 0);

	// �ԍ��f�[�^�̐ݒ�
	for (int nCntVertical = 0; nCntVertical < m_nLine; nCntVertical++)
	{
		for (int nCntRow = 0; nCntRow < m_nRow + 1; nCntRow++)
		{
			// ���̗��2���ݒ肷��
			// pIdx[(��̈ʒu)�~(���݂̉��̕�����)�{(���炷��)] = (���炷��)�{(��̈ʒu)�{(���̕�����+1�~���݂̏c�̕�����)
			pIdx[(m_nRow * 2 + 4) * nCntVertical + 0 + (nCntRow * 2)] = (WORD)(nCntRow + (m_nRow + 1) + (m_nRow + 1) * nCntVertical);
			pIdx[(m_nRow * 2 + 4) * nCntVertical + 1 + (nCntRow * 2)] = (WORD)(nCntRow + 0 + (m_nRow + 1) * nCntVertical);
		}
	}
	// �|���S����`�悳���Ȃ������̔ԍ��f�[�^�̐ݒ�
	for (int nCntVertical = 0; nCntVertical < m_nLine - 1; nCntVertical++)
	{
		// pIdx[(��̈ʒu)�{(���炷��)] = (���̕�����)/(���̕�����+2�{���炷��)�{(���̕�����+1�~���݂̏c�̕�����)
		pIdx[(m_nRow * 2 + 2) + 0 + nCntVertical * (m_nRow * 2 + 4)] = (WORD)(m_nRow + (m_nRow + 1) * nCntVertical);
		pIdx[(m_nRow * 2 + 2) + 1 + nCntVertical * (m_nRow * 2 + 4)] = (WORD)((m_nRow * 2 + 2) + (m_nRow + 1) * nCntVertical);
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;
}

//================================================
// �I������
//================================================
void CMeshWall::Uninit(void)
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
void CMeshWall::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshWall::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//�A���t�@�l�̎Q�ƒl
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �J�����O���s��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	if (m_pTexture != NULL)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);
	}
	else
	{
		pDevice->SetTexture(0, NULL);
	}

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,
		0,
		((m_nRow + 1) * (m_nLine + 1)),					// ���_�̐�
		0,												// �J�n���钸�_�̃C���f�b�N�X
		(m_nRow * m_nLine * 2) + (m_nLine * 4) - 4);	// �`�悷��v���~�e�B�u��

														//�A���t�@�e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//�A���t�@�l�̎Q�ƒl
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//=============================================================================
// ��������
//=============================================================================
CMeshWall* CMeshWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nRow, int nLine, int nTex)
{
	// �C���X�^���X�̐���
	CMeshWall *pMeshWall = NULL;

	// �k���`�F�b�N
	if (pMeshWall == NULL)
	{
		// �N���X�̐���
		pMeshWall = new CMeshWall;
		if (pMeshWall != NULL)
		{
			// �ϐ��̏�����
			pMeshWall->m_rot = rot;
			pMeshWall->m_nRow = nRow;
			pMeshWall->m_nLine = nLine;

			pMeshWall->m_pTexture = *CScene3D::GetTexture(nTex);

			// ����������
			pMeshWall->Init(pos, size);
		}
	}

	return pMeshWall;
}

//=============================================================================
// �J���[�ݒ菈��
//=============================================================================
void CMeshWall::SetColor(D3DXCOLOR col)
{
	// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int nCntVtx = 0;

	// ���_���W�̐ݒ�
	for (int nCntVertical = 0; nCntVertical < m_nLine + 1; nCntVertical++)
	{
		for (int nCntRow = 0; nCntRow < m_nRow + 1; nCntRow++, nCntVtx++)
		{
			// �J���[�̐ݒ�
			pVtx[nCntVtx].col = col;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`���ݒ菈��
//=============================================================================
//void CMeshWall::BindTexture(const char *aTextureName)
//{
//	// ���_����ݒ�
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̎擾
//
//	D3DXCreateTextureFromFile(pDevice, aTextureName, &m_pTexture);
//}

//================================================
// �����蔻�菈��
//================================================
D3DXVECTOR3 CMeshWall::Collision(CScene *pScene)
{
	D3DXVECTOR3 Vec = D3DXVECTOR3(99.0f, 99.0f, 99.0f);

	//�I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CScene *pSaveObject = NULL;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CScene::PRIORITY_OBJECT);

	while (pObject != NULL)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECTTYPE_WALL)
		{
			// ���b�V���E�H�[���ɃL���X�g
			CMeshWall *pMeshWall = NULL;
			pMeshWall = (CMeshWall*)pObject;

			D3DXVECTOR3 posWall = pMeshWall->GetPos();		//�ǂ̈ʒu
			D3DXVECTOR3 sizeWall = pMeshWall->GetSize();	//�ǂ̃T�C�Y
			D3DXVECTOR3 rotWall = pMeshWall->m_rot;			//�ǂ̌���
			D3DXVECTOR3 pos = pScene->GetPos();				//�Ώۂ̈ʒu
			float fSize = pScene->GetRadius();				//�Ώۂ̔��a�̃T�C�Y
			D3DXVECTOR3 posOld = pScene->GetPosOld();		//�Ώۂ�1�t���[���O�̈ʒu

			////����]�����ǂ̓����蔻��̏������ł��Ă��Ȃ����߁A����̌����̎��ɓ����蔻��������Ă���(������)
			//if (rotWall.y <= 1.58f && rotWall.y >= 1.56f)
			//{
			//	//�ǂɉE���瓖��������
			//	if (pos.y + fSize	> posWall.y &&
			//		posOld.y		< posWall.y + sizeWall.y &&
			//		pos.z + fSize	> posWall.z - sizeWall.x / 2.0f &&
			//		pos.z - fSize	< posWall.z + sizeWall.x / 2.0f &&
			//		pos.x >= posWall.x - fSize &&
			//		posOld.x <= posWall.x - fSize)
			//	{
			//		//�ʒu��ݒ�
			//		pos.x = posWall.x - fSize;
			//		pScene->SetPos(pos);
			//		bContact = true;
			//	}
			//}

			//if (rotWall.y >= -1.58f && rotWall.y <= -1.56f)
			//{
			//	//�ǂɍ����瓖��������
			//	if (pos.y + fSize	> posWall.y &&
			//		posOld.y		< posWall.y + sizeWall.y &&
			//		pos.z + fSize	> posWall.z - sizeWall.x / 2.0f &&
			//		pos.z - fSize	< posWall.z + sizeWall.x / 2.0f &&
			//		pos.x <= posWall.x + fSize &&
			//		posOld.x >= posWall.x + fSize)
			//	{
			//		//�ʒu��ݒ�
			//		pos.x = posWall.x + fSize;
			//		pScene->SetPos(pos);
			//		bContact = true;
			//	}
			//}

			//if ((rotWall.y <= 0.1f && rotWall.y >= -0.1f) ||
			//	(rotWall.y >= -3.15f && rotWall.y <= -3.13f))
			//{
			//	//�ǂɎ�O���瓖��������
			//	if (pos.y + fSize	> posWall.y &&
			//		posOld.y		< posWall.y + sizeWall.y &&
			//		pos.x + fSize	> posWall.x - sizeWall.x / 2.0f &&
			//		pos.x - fSize	< posWall.x + sizeWall.x / 2.0f &&
			//		pos.z >= posWall.z - fSize &&
			//		posOld.z <= posWall.z - fSize)
			//	{
			//		//�ʒu��ݒ�
			//		pos.z = posWall.z - fSize;
			//		pScene->SetPos(pos);
			//		bContact = true;
			//	}
			//}

			//if (rotWall.y <= 3.15f && rotWall.y >= 3.13f)
			//{
			//	//�ǂɉ����瓖��������
			//	if (pos.y + fSize	> posWall.y &&
			//		posOld.y		< posWall.y + sizeWall.y &&
			//		pos.x + fSize	> posWall.x - sizeWall.x / 2.0f &&
			//		pos.x - fSize	< posWall.x + sizeWall.x / 2.0f &&
			//		pos.z <= posWall.z + fSize &&
			//		posOld.z >= posWall.z + fSize)
			//	{
			//		//�ʒu��ݒ�
			//		pos.z = posWall.z + fSize;
			//		pScene->SetPos(pos);
			//		bContact = true;
			//	}
			//}

			//�V���������B���ʕ��������g���������B�ǂ̊p�x�ł��g����(����)
			//�ǂ�4���_
			D3DXVECTOR3 aPoint[4];
			aPoint[0] = D3DXVECTOR3(posWall.x - (sizeWall.x * 0.5f) * cosf(rotWall.y), posWall.y + sizeWall.y	, posWall.z - (sizeWall.x * 0.5f) * sinf(-rotWall.y));
			aPoint[1] = D3DXVECTOR3(posWall.x + (sizeWall.x * 0.5f) * cosf(rotWall.y), posWall.y + sizeWall.y	, posWall.z + (sizeWall.x * 0.5f) * sinf(-rotWall.y));
			aPoint[2] = D3DXVECTOR3(posWall.x - (sizeWall.x * 0.5f) * cosf(rotWall.y), posWall.y				, posWall.z - (sizeWall.x * 0.5f) * sinf(-rotWall.y));
			aPoint[3] = D3DXVECTOR3(posWall.x + (sizeWall.x * 0.5f) * cosf(rotWall.y), posWall.y				, posWall.z + (sizeWall.x * 0.5f) * sinf(-rotWall.y));

			D3DXVECTOR3 Cross[3];
			D3DXVec3Cross(&Cross[0], &(aPoint[2] - aPoint[1]), &(aPoint[1] - aPoint[0]));									//�ǂ̊O�σx�N�g��
			float fLength = powf((Cross[0].x * Cross[0].x) + (Cross[0].y * Cross[0].y) + (Cross[0].z * Cross[0].z), 0.5f);	//����
			Cross[0].x /= fLength;
			Cross[0].y /= fLength;
			Cross[0].z /= fLength; //�����܂Ŗ@���x�N�g��

			Cross[1] = pos - aPoint[0];		//�v���C���[��pos�ƕǂ̔C�ӂ̓_�̃x�N�g��
			Cross[2] = posOld - aPoint[0];	//�v���C���[��Oldpos�ƕǂ̔C�ӂ̓_�̃x�N�g��

			float fDistance = Cross[0].x * Cross[1].x + Cross[0].y * Cross[1].y + Cross[0].z * Cross[1].z;		//�ǖʂƂ̋��� �}�C�i�X�̎��A�\���ɂ���
			float fOldDistance = Cross[0].x * Cross[2].x + Cross[0].y * Cross[2].y + Cross[0].z * Cross[2].z;	//�ǖʂƂ̋����@�}�C�i�X�̎��A�\���ɂ���
			D3DXVECTOR3 Point = D3DXVECTOR3(pos.x - (Cross[0].x * fDistance), pos.y - (Cross[0].y * fDistance), pos.z - (Cross[0].z * fDistance));						//�ǖʏ�̃v���C���[�̈ʒu
			D3DXVECTOR3 OldPoint = D3DXVECTOR3(posOld.x - (Cross[0].x * fOldDistance), posOld.y - (Cross[0].y * fOldDistance), posOld.z - (Cross[0].z * fOldDistance));	//�ǖʏ��1�t���[���O�̃v���C���[�̈ʒu

			if (aPoint[2].y < Point.y + fSize && Point.y < aPoint[0].y || aPoint[2].y < OldPoint.y + fSize && OldPoint.y < aPoint[0].y)
			{
				if ((aPoint[0].x < Point.x + fSize && Point.x - fSize < aPoint[1].x || aPoint[1].x < Point.x + fSize && Point.x - fSize < aPoint[0].x) ||
					(aPoint[0].x < OldPoint.x + fSize && OldPoint.x - fSize < aPoint[1].x || aPoint[1].x < OldPoint.x + fSize && OldPoint.x - fSize < aPoint[0].x))
				{
					if ((aPoint[0].z < Point.z + fSize && Point.z - fSize < aPoint[1].z || aPoint[1].z < Point.z + fSize && Point.z - fSize < aPoint[0].z) ||
						(aPoint[0].z < OldPoint.z + fSize && OldPoint.z - fSize < aPoint[1].z || aPoint[1].z < OldPoint.z + fSize && OldPoint.z - fSize < aPoint[0].z))
					{
						if (fabsf(fDistance) <= fSize || fOldDistance <= -fSize && fDistance >= -fSize)
						{
							pos.x -= sinf(rotWall.y) * (fSize - fabsf(fDistance));
							pos.z -= cosf(rotWall.y) * (fSize - fabsf(fDistance));
							pScene->SetPos(pos);
							Vec = Cross[0];
						}
					}
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	return Vec;
}