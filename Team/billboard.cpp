//=============================================================================
// �r���{�[�h���� [Billboard.cpp]
// Author : �O��q��
//=============================================================================
#include "billboard.h"
#include "manager.h"
#include "renderer.h"
//=============================================================================
// �}�N��
//=============================================================================


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBillboard::CBillboard(PRIORITY nPriority) : CScene3D::CScene3D(nPriority)
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBillboard::~CBillboard()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CBillboard::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nTex, D3DXCOLOR col, int nLife)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	m_pTexture = *GetTexture(nTex);
	m_move = move;

	// �ϐ��̏�����
	SetPos(pos);

	m_nLife = nLife;

	// ���_�o�b�t�@�̐���
	//��(�c�̕������{�P)�~(���̕������{�P)�̒l�̒��_�𐶐�����
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-Size.x / 2.0f , Size.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Size.x / 2.0f, Size.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-Size.x / 2.0f, -Size.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Size.x / 2.0f, -Size.y / 2.0f, 0.0f);
	// �@��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	// �J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	// �e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CBillboard::Uninit()
{
	CScene3D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CBillboard::Update()
{
	if (CManager::GetPause() == false)
	{
		D3DXVECTOR3 pos = GetPos();
		pos += m_move;
		SetPos(pos);
		m_nLife--;

		if (pos.y <= -10.0f || m_nLife <= 0)
		{
			SetDeath(true);
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CBillboard::Draw()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans, mtxWorld; //�v�Z�p�}�g���b�N�X
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����


	//Z�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//�A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&mtxWorld, NULL, &mtxView); //�t�s������߂�

	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	SetMatrix(mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, m_pTexture);    //�e�N�X�`���̐ݒ�

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //�J�n����n�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��

	//Z�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�ʒu�ɂ���Ă͉f��Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//=============================================================================
// �`��
//=============================================================================
void CBillboard::ZTexDraw()
{

}

//=============================================================================
// �쐬
//=============================================================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nTex, D3DXCOLOR col, int nLife)
{
	CBillboard *pBillboard;
	pBillboard = new CBillboard(PRIORITY_EFFECT);
	if (pBillboard != NULL)
	{
		pBillboard->Init(pos, move, Size, nTex, col, nLife);
	}
	return pBillboard;
}