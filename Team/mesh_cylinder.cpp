//=============================================================================
// ���b�V��(�~��)���� [mesh_cylinder.cpp]
// Authore : ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "mesh_cylinder.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshCylinder::CMeshCylinder(PRIORITY  nPriority) :CScene3D(nPriority)
{
	// �ϐ��̃N���A
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSide = 0;
	m_nVertical = 0;
	m_bOutSide = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshCylinder::~CMeshCylinder()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshCylinder::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �ϐ��̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = pos;
	m_size = size;

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
	float fAngle = 0;

	for (int nCntVertical = 0; nCntVertical < m_nVertical + 1; nCntVertical++)
	{
		for (int nCntSide = 0; nCntSide < m_nSide + 1; nCntSide++, nCntVtx++)
		{
			// ���_���W�̐ݒ�
			pVtx[nCntVtx].pos = D3DXVECTOR3(-m_size.x * cosf(fAngle),
				m_size.y - (nCntVertical * (m_size.y / m_nVertical)),
				-m_size.z * sinf(fAngle));

			// ���_���d������ꍇ�A�p�x�͉����Ȃ�
			if (nCntSide != m_nSide)
			{
				if (m_bOutSide == false)
				{
					// �V�����_�[�̓����ɕ`��
					fAngle -= (D3DX_PI / (m_nSide / 2.0f));
				}
				else
				{
					// �V�����_�[�̊O���ɕ`��
					fAngle += (D3DX_PI / (m_nSide / 2.0f));
				}
			}

			// �@��
			pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

			// �J���[
			pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`��
			pVtx[nCntVtx].tex = D3DXVECTOR2(0.0f + (1.0f / m_nSide * nCntSide), 0.0f + (1.0f / m_nVertical * nCntVertical));
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (((m_nSide + 1) * (m_nVertical + 1)) + ((m_nSide + 3) * (m_nVertical - 1))),
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
	for (int nCntVertical = 0; nCntVertical < m_nVertical; nCntVertical++)
	{
		for (int nCntSide = 0; nCntSide < m_nSide + 1; nCntSide++)
		{
			// ���̗��2���ݒ肷��
			pIdx[(m_nSide * 2 + 4) * nCntVertical + 0 + (nCntSide * 2)] = (WORD)(nCntSide + (m_nSide + 1) + (m_nSide + 1) * nCntVertical);
			pIdx[(m_nSide * 2 + 4) * nCntVertical + 1 + (nCntSide * 2)] = (WORD)(nCntSide + 0 + (m_nSide + 1) * nCntVertical);
		}
	}
	// �|���S����`�悳���Ȃ������̔ԍ��f�[�^�̐ݒ�
	for (int nCntVertical = 0; nCntVertical < m_nVertical - 1; nCntVertical++)
	{
		// pIdx[(��̈ʒu)�{(���炷��)] = (���̕�����)/(���̕�����+2�{���炷��)�{(���̕�����+1�~���݂̉��̕�����)
		pIdx[(m_nSide * 2 + 2) + 0 + nCntVertical * (m_nSide * 2 + 4)] = (WORD)(m_nSide + (m_nSide + 1) * nCntVertical);
		pIdx[(m_nSide * 2 + 2) + 1 + nCntVertical * (m_nSide * 2 + 4)] = (WORD)((m_nSide * 2 + 2) + (m_nSide + 1) * nCntVertical);
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshCylinder::Uninit(void)
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

	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshCylinder::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshCylinder::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

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

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,
		0,
		((m_nSide + 1) * (m_nVertical + 1)),					// ���_�̐�
		0,														// �J�n���钸�_�̃C���f�b�N�X
		(m_nSide * m_nVertical * 2) + (m_nVertical * 4) - 4);	// �`�悷��v���~�e�B�u��

	//���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// ��������
//=============================================================================
CMeshCylinder* CMeshCylinder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nVertical, int nSide, bool bOutSide, int nTex)
{
	// �C���X�^���X�̐���
	CMeshCylinder *pMeshCylinder = NULL;

	// �k���`�F�b�N
	if (pMeshCylinder == NULL)
	{
		// �N���X�̐���
		pMeshCylinder = new CMeshCylinder;
		if (pMeshCylinder != NULL)
		{
			// �ϐ��̏�����
			pMeshCylinder->m_nVertical = nVertical;
			pMeshCylinder->m_nSide = nSide;
			pMeshCylinder->m_bOutSide = bOutSide;

			if (0 <= nTex)
			{
				pMeshCylinder->m_pTexture = *CScene3D::GetTexture(nTex);
			}

			// ����������
			pMeshCylinder->Init(pos, size);
		}
	}

	return pMeshCylinder;
}