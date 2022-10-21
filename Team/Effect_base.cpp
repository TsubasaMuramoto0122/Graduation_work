//---------------------------
// �G�t�F�N�g�̃x�[�X���� [Effect_base.cpp]
// Author : �����G��
//---------------------------
#include "Effect_base.h"
#include "manager.h"
#include "renderer.h"

//�}�N����`
#define TEXTURE_FILENAME_3D "data/FILES/EffectTexNameRead.txt"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CEffect_base::m_pTexture[MAX_TEXTURE_3D] = {};
int CEffect_base::m_nMaxTex = 0;

CEffect_base::CEffect_base(PRIORITY nPriority) : CScene3D::CScene3D(nPriority)
{

}

CEffect_base::~CEffect_base()
{

}

//����������
HRESULT CEffect_base::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����

	SetPos(pos);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	m_TexNum = Tex;

	m_size = size;

	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, -size.z);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(Tex.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, Tex.y);
	pVtx[3].tex = D3DXVECTOR2(Tex.x, Tex.y);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return S_OK;
}

//�I������
void CEffect_base::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CScene3D::Uninit();
}

//�X�V����
void CEffect_base::Update()
{

}

//�`�揈��
void CEffect_base::Draw()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld; //�v�Z�p�}�g���b�N�X
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
														//���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�����ȕ�����`�悵�Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

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
	if (m_nTexType != -1)
	{
		pDevice->SetTexture(0, m_pTexture[m_nTexType]);    //�e�N�X�`���̐ݒ�
	}
	else
	{
		pDevice->SetTexture(0, NULL);    //�e�N�X�`���̐ݒ�
	}
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //�J�n����n�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
			//���C���e�B���O��L���ɂ���

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//�f�t�H���g�ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}
//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CEffect_base::UninitTexture()
{
	//�e�N�X�`���j��
	for (int nCnt = 0; nCnt < m_nMaxTex; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
//���Ԃ񂢂�Ȃ�
////�쐬
//CEffect_base *CEffect_base::Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex)
//{
//	CEffect_base *pPlane;
//	pPlane = new CEffect_base(CManager::PRIORITY_SET);
//	if (pPlane != NULL)
//	{
//		pPlane->Init(size, pos, Tex);
//	}
//	return pPlane;
//}
//=============================================================================

//=============================================================================
// �T�C�Y�Z�b�g
//=============================================================================
void CEffect_base::SetSize(D3DXVECTOR3 size)
{
	//m_size = size;
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, -size.z);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �F�Z�b�g
//=============================================================================
void CEffect_base::ChangeColor(D3DXCOLOR col)
{
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`������
//=============================================================================
void CEffect_base::CreateTextureEffect()
{
	// ���_����ݒ�
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̎擾

	//�t�@�C���ǂݍ���
	char aFile[256];
	FILE *pFile = fopen(TEXTURE_FILENAME_3D, "r");

	int nCntTex = 0;

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);

			if (strcmp(&aFile[0], "NUM_TEXTURE") == 0)	//NUM_TEXTURE�̕�����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nMaxTex);//�g�p����e�N�X�`������ǂݍ���
			}

			if (strcmp(&aFile[0], "TEXTURE_FILENAME") == 0) //TEXTURE_FILENAME�̕�����
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				D3DXCreateTextureFromFile(pDevice, &aFile[0], &m_pTexture[nCntTex]);
				nCntTex++;
			}

			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPT�̕��������������
			{
				break;
			}

		}
	}
	fclose(pFile);
}

//=============================================================================
//�J���[�ύX
//=============================================================================
void CEffect_base::ColorChange(D3DCOLORVALUE color)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

				   //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐F
	pVtx[0].col = D3DCOLOR_RGBA((int)color.r, (int)color.g, (int)color.b, (int)color.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)color.r, (int)color.g, (int)color.b, (int)color.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)color.r, (int)color.g, (int)color.b, (int)color.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)color.r, (int)color.g, (int)color.b, (int)color.a);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
//�T�C�Y�ύX
//=============================================================================
void CEffect_base::ChangeSize(D3DXVECTOR3 size)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

				   //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
	pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, -size.z);
	pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, -size.z);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
//���ʃG�t�F�N�g
//=============================================================================
void CEffect_base::SetPosField(D3DXVECTOR3 pos, D3DXVECTOR3 Size, float Rotate, float Rotate2)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

				   //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x + (cosf(Rotate2)) * Size.x, Size.y, pos.z + (sinf(Rotate))* Size.x);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (sinf(Rotate))  * Size.x, Size.y, pos.z - (cosf(Rotate2))* Size.x);
	pVtx[2].pos = D3DXVECTOR3(pos.x - (sinf(Rotate))  * Size.x, Size.y, pos.z + (cosf(Rotate2))* Size.x);
	pVtx[3].pos = D3DXVECTOR3(pos.x - (cosf(Rotate2)) * Size.x, Size.y, pos.z - (sinf(Rotate))* Size.x);


	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}

//=============================================================================
//�T�C�Y�ύX
//=============================================================================
void CEffect_base::BillboardSize(float size)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

				   //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size, size, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(size, size, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size, -size, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(size, -size, 0.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
//�e�N�X�`���ړ�
//=============================================================================
void CEffect_base::TexturMove(D3DXVECTOR2 MoveTex)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^
	m_TexMove += MoveTex;

	if (m_TexMove.x >= 1.0f)
	{
		m_TexMove.x -= 1.0f;
	}
	else if (m_TexMove.x < 0.0f)
	{
		m_TexMove.x += 1.0f;
	}

	if (m_TexMove.y >= 1.0f)
	{
		m_TexMove.y -= 1.0f;
	}
	else if (m_TexMove.y < 0.0f)
	{
		m_TexMove.y += 1.0f;
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(m_TexMove.x, m_TexMove.y);
	pVtx[1].tex = D3DXVECTOR2(m_TexNum.x + m_TexMove.x, m_TexMove.y);
	pVtx[2].tex = D3DXVECTOR2(m_TexMove.x, m_TexNum.y + m_TexMove.y);
	pVtx[3].tex = D3DXVECTOR2(m_TexNum.x + m_TexMove.x, m_TexNum.y + m_TexMove.y);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
//�e�N�X�`���p�^�[��
//=============================================================================
void CEffect_base::SetTexAnim(D3DXVECTOR2 TexPattern, D3DXVECTOR2 TexAnimSize)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^

	m_nSplit = TexPattern;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + m_TexMove.x, m_TexNum.y + m_nSplit.y * TexAnimSize.y + m_TexMove.y);
	pVtx[1].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + TexAnimSize.x + m_TexMove.x, m_TexNum.y + m_nSplit.y * TexAnimSize.y + m_TexMove.y);
	pVtx[2].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + m_TexMove.x, m_TexNum.y + m_nSplit.y *  +TexAnimSize.y + TexAnimSize.y + m_TexMove.y);
	pVtx[3].tex = D3DXVECTOR2(m_TexNum.x + m_nSplit.x * TexAnimSize.x + TexAnimSize.x + m_TexMove.x, m_TexNum.y + m_nSplit.y *  +TexAnimSize.y + TexAnimSize.y + m_TexMove.y);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}

//=============================================================================
//���W
//=============================================================================
void CEffect_base::SetPosBill(D3DXVECTOR3 pos, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3, D3DXVECTOR3 pos4)
{
	VERTEX_3D*pVtx;//���_���ւ̃|�C���^
				   //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = pos;
	pVtx[1].pos = pos2;
	pVtx[2].pos = pos3;
	pVtx[3].pos = pos4;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}